/* -*- c++ -*- */
/*
 * Copyright 2002,2008 Free Software Foundation, Inc.
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

#ifndef _GR_IIRDES_H_
#define _GR_IIRDES_H_

#include <gr_core_api.h>
#include <vector>
#include <cmath>
#include <string>
#include <gr_complex.h>
#include <gr_types.h>

/*!
 * \brief Infinite Impulse Response (IIR) filter design functions.
 */

class GR_CORE_API gr_iirdes {
 public:
  enum filter_type {
    BUTTER = 0,	// Butterworth Design 
    CHEBY1 = 1,	// Chebyshev1 Design 
    CHEBY2 = 2,	// Chebyshev2 Design 
    ELLIP = 3,  // Elliptic filter
  };

  enum band_type {
    LOW = 0,	 
    HIGH = 1,	
    BPASS = 2, 
    BSTOP = 3,  
  };

/*
  static std::vector<gr_complexd>
   iirdesign(gr_vector_double wp, gr_vector_double ws,
		   	 double gpass, double gstop, filter_type ftype=CHEBY1,
			 bool analog=false, unsigned int output_zpk=0);

  static std::vector<gr_complexd>
   butter(unsigned int order, gr_vector_double wn,
		  string btype="low",bool analog=false, string output="ba");

  static std::vector<gr_vector_float>
   buttord(gr_vector_double wp, gr_vector_double ws,
		   	 double gpass, double gstop, bool analog=false);

  static std::vector<gr_complexd>
   cheby1(unsigned int order, gr_vector_double wn,
		  string btype="low",bool analog=false, string output="ba");
*/
/*
 * Chebyshev type I filter order.
 *
 * Return the order of the lowest order digital Chebyshev Type I filter that
 * loses no more than `gpass` dB in the passband and has at least `gstop` dB
 * attenuation in the stopband.
 */
   static std::vector< std::vector<double> >  
   cheb1ord(std::vector <double> wp, std::vector<double> ws,
		   	 double gpass, double gstop, bool analog);

   static void   
   cheb1ap(unsigned int order,
		    double rp);
/*
  static std::vector<gr_complexd>
   cheby2(unsigned int order, gr_vector_double wn,
		  string btype="low",bool analog=false, string output="ba");

  static std::vector<gr_vector_float>
   cheb2ord(gr_vector_double wp, gr_vector_double ws,
		   	 double gpass, double gstop, bool analog=false);
*/

};

#endif
