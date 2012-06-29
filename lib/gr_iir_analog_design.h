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

#ifndef INCLUDED_GR_IIR_ANALOG_DESIGN_H
#define INCLUDED_GR_IIR_ANALOG_DESIGN_H

#include <vector>
#include <gr_complex.h>
#include <stdexcept>

enum IIR_TYPE {IIR_TYPE_LOWPASS, IIR_TYPE_BANDPASS,
	       IIR_TYPE_HIGHPASS,IIR_TYPE_BANDSTOP};


void zp_pairing(std::vector<gr_complexd> &_z,
                unsigned int _n,
                double _tol,
                std::vector<gr_complexd> &_p);

void bilinear_zpk(std::vector<gr_complexd> &_za,
                  unsigned int _nza,
                  std::vector<gr_complexd> &_pa,
                  unsigned int _npa,
                  gr_complexd *_ka,
                  double _m,
                  std::vector<gr_complexd> &_zd,
                  std::vector<gr_complexd> &_pd,
                  gr_complexd *_kd);

double freqprewarp(IIR_TYPE type,
                   double _fc,
                   double _f0);


void butter_analog_zeros_poles_gain(const unsigned int order,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument);


void cheby1_analog_zeros_poles_gain(const unsigned int order,
				    const double eps,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument);

void cheby2_analog_zeros_poles_gain(const unsigned int order,
				    const double eps,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    gr_complex *gain) throw (std::invalid_argument);

void bessel_analog_zeros_poles_gain(const unsigned int order,
				    std::vector<gr_complexd> &zeros,
				    std::vector<gr_complexd> &poles,
				    double *gain) throw (std::invalid_argument);

void ellip_analog_zeros_poles_gain(const unsigned int order,
				   std::vector<gr_complexd> &zeros,
				   std::vector<gr_complexd> &poles,
				   gr_complex *gain) throw (std::invalid_argument);

#endif
