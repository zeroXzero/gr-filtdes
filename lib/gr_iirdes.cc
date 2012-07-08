/* -*- c++ -*- */
/*
 * Copyright 2002,2007,2008 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gr_iirdes.h>
#include <gr_types.h>
#include <iostream>
#include <valarray>
#include <stdexcept>

using namespace std;


//Chebyshev1 filter order
vector < vector<double> >
gr_iirdes::cheb1ord(vector <double> wp, //normalized passband 
					vector <double> ws, //normalized stopband 
			        double gpass,	     //passband loss 
					double gstop,		 //stopband attenuation 
					bool analog = 0)

{
  unsigned int tband;
  vector <double> ord(1), retwp(2);
  double del_1, del_2, D_1, D_2, s_omega, p_omega;
  vector < vector<double> > ord_wp(2);
  valarray <double> opass(wp.size()), ostop(ws.size()), ointers(ws.size()), ointerp(ws.size());

  if (wp.size() != ws.size())
     throw std::out_of_range("wp and ws array length mismatch");
  else if (wp.size() > 2 |  ws.size() > 2)
     throw std::out_of_range("wp or ws array has length more than 2");

  for (int i=0; i < wp.size(); i++)
  {
      opass[i]=wp[i];
      ostop[i]=ws[i];
  }

  switch ((int) wp.size())
  {
      case 1: 
          {
            if (wp[0] < ws[0])
                tband = LOW;
            else
                tband = HIGH;
                
          }
          break;
      case 2: 
          {
            if (wp[0] < ws[0])
                tband = BSTOP;
            else
                tband = BPASS;
          }
          break;
      default:
          throw std::out_of_range("Unexpected array length");

  }

  //Bilinear Transformation
  if (analog)
  {
      opass=tan(opass * M_PI);
      ostop=tan(ostop * M_PI);
  }

  //Frequency Transformation
  if (tband == LOW)
      ointers = ostop/opass;  
  else if (tband == HIGH)
      ointers = opass/ostop;   
  else if (tband == BPASS)
  {
      ointers = ((pow(ostop, 2.0) - opass[0] * opass[1])/
                (ostop * (opass[0] - opass[1])));
      ointerp = ((pow(opass, 2.0) - opass[0] * opass[1])/
                (opass * (opass[0] - opass[1])));
      retwp[0]= abs(ointerp[1]);
      retwp[1]= abs(ointers[1]);
  }

  else if (tband == BSTOP)
  {
      ointers = ((ostop * (opass[0] - opass[1]))/
                (pow(ostop, 2.0) - opass[0] * opass[1]));
      ointerp = ((opass * (opass[0] - opass[1]))/
                (pow(opass, 2.0) - opass[0] * opass[1]));
      retwp[0]= abs(ointers[1]);
      retwp[1]= abs(ointerp[1]);
  }

  s_omega = abs(ointers).min() ;
  p_omega = abs(ointerp).max() ;
  
  //Using Chebyshev polynomials for design
  del_1 = pow(10, (0.1 * gpass));
  del_2 = pow(10, (0.1 * gstop));
  D_1 = (double) (1 / pow(1.0-del_1,2)) - 1.0;
  D_2 = (double) (1 / pow(del_2, 2)) - 1.0;
  ord[0] = ceil(acosh(sqrt(D_2) / sqrt(D_1))/
             acosh(s_omega / p_omega));

  ord_wp[0] = ord; 
  ord_wp[1] = retwp; 
 
  return ord_wp;
}

//Chebyshev 1 lpf prototype
void gr_iirdes::cheb1ap(unsigned int order,
				    double rp)
{
  vector< complex<double> > zeros;
  vector< complex<double> > poles(2*order);
  complex<double> gain;
  vector< vector< complex<double> > > zpk(3);
  

  valarray <double> A_k(2*order), poles_r(2*order), poles_i(2*order);
  double del_1, D_1, eps, B;

  del_1	= pow(10, (0.1 * rp));
  D_1 = (double) ((1 / pow(1.0-del_1,2)) - 1.0);
  eps = sqrt(D_1);

  for (int i=0; i< 2*order; i++)
  {
	  A_k[i] = (2*(i+1) * M_PI)/(2*order);
  }

  B=asinh(1.0/eps)/order;

  poles_r=sin(A_k) * sinh(B);
  poles_i=cos(A_k) * cosh(B);

  for (int i=0; i< 2*order; i++)
  {
	  poles[i]= complex<double>(poles_r[i], poles_i[i]);
	  cout << "pole: " << i << " " << poles[i].real() << " "<< poles[i].imag() << endl;
  }
  zpk[0] = zeros;
  zpk[1] = poles;
}

//Private functions

