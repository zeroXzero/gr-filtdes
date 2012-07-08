/* -*- C++ -*- */
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

/*!
 * \brief Infinite Impulse Response (IIR) filter design functions.
 */

%rename(iirdes) gr_iirdes;

class gr_iirdes {
 public:
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

};
