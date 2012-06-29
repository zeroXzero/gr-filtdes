/* -*- c++ -*- */
/*
 * Copyright 2010 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <gr_iir_analog_design.h>

double freqprewarp(IIR_TYPE type,
                   double _fc,
                   double _f0)
{
  double m = 0.0;
  if (type == IIR_TYPE_LOWPASS) {
    // low pass
    m = tan(M_PI * _fc);
  } else if (type == IIR_TYPE_HIGHPASS) {
    // high pass
    m = -cos(M_PI * _fc) / sin(M_PI * _fc);
  } else if (type == IIR_TYPE_BANDPASS) {
    // band pass
    m = (cos(2*M_PI*_fc) - cos(2*M_PI*_f0) )/ sin(2*M_PI*_fc);
  } else if (type == IIR_TYPE_BANDSTOP) {
    // band stop
    m = sin(2*M_PI*_fc)/(cos(2*M_PI*_fc) - cos(2*M_PI*_f0));
  }
  m = fabs(m);
  
  return m;
}

void zp_pairing(std::vector<gr_complexd> &_z,
                unsigned int _n,
                double _tol,
                std::vector<gr_complexd> &_p)
{
    // validate input
  //    if (_tol < 0) {
  //      fprintf(stderr,"error: liquid_cplxpair(), tolerance must be positive\n");
  //     exit(1);
  //  }

    // keep track of which elements have been paired
    bool paired[_n];
    

    unsigned int i,j,k=0;
    for (i=0;i<_n;i++) paired[i]=false;
    for (i=0; i<_n; i++) {
        // ignore value if already paired, or if imaginary
        // component is less than tolerance
      if (paired[i] || fabs(_z[i].imag()) < _tol)
            continue;

        for (j=0; j<_n; j++) {
            // ignore value if already paired, or if imaginary
            // component is less than tolerance
	  if (j==i || paired[j] || fabs(_z[j].imag()) < _tol)
                continue;

            if ( fabs(_z[i].imag()+_z[j].imag()) < _tol &&
                 fabs(_z[i].real()-_z[j].real()) < _tol )
            {
                // found complex conjugate pair
                _p[k++] = _z[i];
                _p[k++] = _z[j];
                paired[i] = true;
                paired[j] = true;
                break;
            }
        }
    }
    //    assert(k <= _n);

    // sort through remaining unpaired values and ensure
    // they are purely real
    for (i=0; i<_n; i++) {
        if (paired[i])
            continue;

        if (fabs(_z[i].imag()) > _tol) {
	  // cerr<<"warning, liquid_cplxpair(), complex numbers cannot be paired\n";
        } else {
            _p[k++] = _z[i];
            paired[i] = true;
        }
    }
}



void bilinear_zpk(std::vector<gr_complexd> &_za,
                  unsigned int _nza,
                  std::vector<gr_complexd> &_pa,
                  unsigned int _npa,
                  gr_complexd *_ka,
                  double _m,
                  std::vector<gr_complexd> &_zd,
                  std::vector<gr_complexd> &_pd,
                  gr_complexd *_kd)
{
    unsigned int i;

    // filter order is equal to number of analog poles
    unsigned int n = _npa;
    gr_complexd G = *_ka;  // nominal gain
    gr_complexd one = gr_complex(1,0);
    for (i=0; i<n; i++) {
        // compute digital zeros (pad with -1s)
        if (i < _nza) {
            gr_complexd zm = _za[i] * _m;
            _zd[i] = (one + zm)/(one - zm);
        } else {
	  _zd[i] = gr_complexd(-1,0);
        }

        // compute digital poles
        gr_complexd pm = _pa[i] * _m;
        _pd[i] = (one + pm)/(one - pm);

        // compute digital gain
        G *= (one - _pd[i])/(one - _zd[i]);
    }
    *_kd = G;

}

void dzpk2tff(std::vector<gr_complexd> &_zd,
              std::vector<gr_complexd> &_pd,
              unsigned int _n,
              gr_complexd _k,
              std::vector<double> &_b,
              std::vector<double> &_a)
{
    unsigned int i;
    std::vector<gr_complexd> q(_n+1);

    // negate poles
    std::vector<gr_complexd> pdm(_n);

    for(i=0; i<_n; i++)
      pdm[i]= _pd[i];
    
    // expand poles
    polycf_expandroots(pdm,_n,q);
    for (i=0; i<=_n; i++)
      _a[i] = q[_n-i].real();

    // negate zeros
    std::vector<gr_complexd> zdm[_n];
    for (i=0; i<_n; i++)
      zdm[i] = gr_complexd(-1,0)*_zd[i];

    // expand zeros
    polycf_expandroots(zdm,_n,q);
    for (i=0; i<=_n; i++)
      _b[i] = (q[_n-i]*_k).real();
}

void butter_analog_zeros_poles_gain(const unsigned int order,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument)
{
  unsigned int r = order%2;
  unsigned int length_iteration = (order - r)/2;

  unsigned int i;
  unsigned int k = 0;

  for (i=0; i<length_iteration; i++) {
    double theta = (double)(2*(i+1) + order - 1)*M_PI/(double)(2*order);
    poles[k++] = gr_complexd(cos(theta), sin(theta));
    poles[k++] = gr_complexd(cos(theta),-sin(theta));
  }

  if (r) poles[k++]= -1.0;

  *gain = 1.0;

}


void cheby1_analog_zeros_poles_gain(const unsigned int order,
				    const double eps,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument)
				    
{
  double orderd = (double) order;
  
  double t0 = sqrt(1.0 + 1.0/(eps*eps));
  double tp = powf(t0 + 1.0/eps, 1/orderd);
  double tm = powf(t0 - 1.0/eps, 1/orderd);

  double b = 0.5*(tp + tm);
  double a = 0.5*(tp - tm);

  unsigned int r = order%2;
  unsigned int L = (order - r)/2;

  unsigned int i;
  unsigned int k = 0;

  zeros[0]=0;
  for (i=0;i<L; i++) {
    double theta = (double)(2*(i+1) + order -1)*M_PI/(double)(2*order);
    poles[k++] = gr_complexd(a*cos(theta),-b*sin(theta));
    poles[k++] = gr_complexd(a*cos(theta), b*sin(theta));
  }
  if (r) poles[k++] = -a;
  *gain = r ? 1.0 : 1.0/sqrt(1.0 + eps*eps);
  for (i=0;i<order;i++)
    *gain *= poles[i];
}


void cheby2_analog_zeros_poles_gain(const unsigned int order,
				    const double eps,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument)
{
  double orderd = (double) order;
  
  double t0 = sqrt(1.0 + 1.0/(eps*eps));
  double tp = powf(t0 + 1.0/eps, 1/orderd);
  double tm = powf(t0 - 1.0/eps, 1/orderd);

  double b = 0.5*(tp + tm);
  double a = 0.5*(tp - tm);

  unsigned int r = order%2;
  unsigned int L = (order - r)/2;

  unsigned int i;
  unsigned int k = 0;

  for (i=0;i<L; i++) {
    double theta = (double)(2*(i+1) + order -1)*M_PI/(double)(2*order);
    poles[k++] = gr_complex(a*cos(theta),-b*sin(theta));
    poles[k++] = gr_complex(a*cos(theta), b*sin(theta));
  }


    // compute zeros
  k=0;
  for (i=0; i<L; i++) {
    double theta = (double)(0.5*M_PI*(2*(i+1)-1)/(double)(order));
    zeros[k++] = -1.0/ gr_complexd(0,cosf(theta));
    zeros[k++] =  1.0/ gr_complexd(0,cosf(theta));
  }


  *gain = 1.0;
  for (i=0;i<order;i++)
    *gain *= poles[i];
  for (i=0;i<2*L  ;i++)
    *gain /= zeros[i];

}


void bessel_analog_zeros_poles_gain(const unsigned int order,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument)
{}

/*  Elliptical filter design is based on "Lecture notes on
    Elliptic Filter Design". S. Orfanides, 2006
    
    code:  www.ece.rutgers.edu/~orfanidi/hpeq
*/

static void landen(const double _modulus,
		   const unsigned int iterations,
		   double *moduli)
{
  unsigned int i;


  double modulus = _modulus;
  double mp;

  for(i=0; i<iterations;i++) {
    mp = sqrt(1.0 - modulus*modulus);
    modulus = (1.0 - mp)/(1 + mp);
    moduli[i] = modulus;
  }
}

static void ellipk(const double _modulus,
		   const unsigned int iterations,
		   double *modulus,
		   double *modulusp)
{
  double kmin = 4e-4;
  double kmax = sqrt(1.0 - kmin*kmin);
  
  double Modulus;
  double ModulusP;

  double mp = sqrt(1.0 - _modulus*_modulus);

  if (mp > kmax) {
    double L = -log(0.25*mp);
    Modulus = L + 0.25*(L-1.0)*ModulusP*ModulusP;
  } else {
    double moduli[iterations];
    landen (_modulus,iterations, moduli);
    ModulusP = M_PI*0.5;
    unsigned int i;
    for (i=0;i<iterations;i++)
      Modulus *= (1.0 + moduli[i]);
  }

    if (mp < kmin) {
        // input exceeds minimum extreme for this precision; use
        // approximation
        double L = -log(mp*0.25);
        ModulusP = L + 0.25*(L-1)*Modulus*Modulus;
    } else {
        double modulip[iterations];
        landen(ModulusP,iterations,modulip);
        ModulusP = M_PI * 0.5;
        unsigned int i;
        for (i=0; i<iterations; i++)
            ModulusP *= (1.0 + modulip[i]);
    }
    *modulus = Modulus;
    *modulusp = ModulusP;
  
}


// ellipdeg()
//
// Compute elliptic degree using _n iterations
//
//  _N      :   analog filter order
//  _k1     :   elliptic modulus for stop-band, ep/ep1
//  _n      :   number of Landen iterations

double ellipdeg(double _N,
                double  _k1,
                unsigned int _n)
{
    // compute K1, K1p from _k1
    double K1, K1p;
    ellipk(_k1,_n,&K1,&K1p);

    // compute q1 from K1, K1p
    double q1 = expf(-M_PI*K1p/K1);

    // compute q from q1
    double q = powf(q1,1.0f/_N);

    // expand numerator, denominator
    unsigned int m;
    double b = 0.0;
    for (m=0; m<_n; m++)
        b += powf(q,(double)(m*(m+1)));
    double a = 0.0f;
    for (m=1; m<_n; m++)
        a += powf(q,(double)(m*m));

    double g = b / (1.0 + 2.0*a);
    double k = 4.0*sqrt(q)*g*g;

    return k;
}

// ellip_cdf()
//
// complex elliptic cd() function (Jacobian elliptic cosine)
//
//  _u      :   vector in the complex u-plane
//  _k      :   elliptic modulus (0 <= _k < 1)
//  _n      :   number of Landen iterations (typically 5-6)

gr_complexd ellip_cd(gr_complexd _u,
                     double _k,
                     unsigned int _n)
{
    gr_complexd wn = cos(_u*M_PI*0.5);
    double v[_n];
    landen(_k,_n,v);
    unsigned int i;
    for (i=_n; i>0; i--) {
      wn = (gr_complexd(1,0) + v[i-1])*wn / (gr_complexd(1,0) + v[i-1]*wn*wn);
    }
    return wn;
}

// ellip_sn()
//
// complex elliptic sn() function (Jacobian elliptic sine)
//
//  _u      :   vector in the complex u-plane
//  _k      :   elliptic modulus (0 <= _k < 1)
//  _n      :   number of Landen iterations (typically 5-6)

gr_complexd ellip_sn(gr_complexd _u,
                     double _k,
                     unsigned int _n)
{
    gr_complexd wn = sin(_u*M_PI*0.5);
    double v[_n];
    landen(_k,_n,v);
    unsigned int i;
    for (i=_n; i>0; i--) {
      wn = (gr_complexd(1,0) + v[i-1])*wn / (gr_complexd(1,0) + v[i-1]*wn*wn);
    }
    return wn;
}

// ellip_acd()
//
// complex elliptic inverse cd() function (Jacobian elliptic
// arc cosine)
//
//  _w      :   vector in the complex u-plane
//  _k      :   elliptic modulus (0 <= _k < 1)
//  _n      :   number of Landen iterations (typically 5-6)
gr_complexd ellip_acd(gr_complexd _w,
                      double _k,
                      unsigned int _n)
{
    double v[_n];
    landen(_k,_n,v);
    double v1;

    gr_complexd w = _w;
    unsigned int i;
    for (i=0; i<_n; i++) {
        v1 = (i==0) ? _k : v[i-1];
        w = w / (gr_complexd(1,0) + sqrt(gr_complexd(1,0) - w*w*v1*v1)) * 2.0 / (gr_complexd(1,0)+v[i]);
    }

    gr_complexd u = gr_complexd(0,-1.0) * log(w + sqrt(w*w-gr_complexd(1,0))) * 2.0 / M_PI;
    //printf("  u = %12.8f + j*%12.8f\n", crealf(u), cimagf(u));

    return u;
}
#if 0
// ellip_asnf()
//
// complex elliptic inverse sn() function (Jacobian elliptic
// arc sine)
//
//  _w      :   vector in the complex u-plane
//  _k      :   elliptic modulus (0 <= _k < 1)
//  _n      :   number of Landen iterations (typically 5-6)
gr_complexd ellip_asn(gr_complexd _w,
                      double _k,
                      unsigned int _n)
{
    return 1.0 - ellip_acd(_w,_k,_n);
}

#endif

void ellip_analog_zeros_poles_gain(const unsigned int order,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument)
{
}
