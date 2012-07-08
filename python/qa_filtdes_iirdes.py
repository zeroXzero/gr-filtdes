#!/usr/bin/env python
#
# Copyright 2011 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
import filtdes
import numpy as np 

class qa_filtdes_iirdes(gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test01 (self):
        a=filtdes.iirdes.cheb1ord([.09, 0.14555556], [0.07888889, 0.15666667],-10,-10,1)
        print a
        a=filtdes.iirdes.cheb1ord([0.08285714,0.15428571], [0.09714286,0.14],-10,-10,1)
        print a
        filtdes.iirdes.cheb1ap(5,-10)


if __name__ == '__main__':
    gr_unittest.run(qa_filtdes_iirdes, "qa_filtdes_iirdes.xml")
