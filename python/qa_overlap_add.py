#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
from tcola_swig import overlap_add_f, overlap_add_c
import numpy as np

class qa_overlap_add (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None
    
    def test_basic_m2_r1 (self):
        M=2
        R=1
        src_data = (0,1,1,2,2,3,3,4,4)
        expected_result = [0,1,2,3]
        
        src = blocks.vector_source_f(src_data)
        op = overlap_add_f(M,R,np.ones(M))
        #op.debug = True
        # op.log("forecasted")
        dst = blocks.vector_sink_f()

        self.tb.connect(src,op)
        self.tb.connect(op,dst)
        self.tb.run()

        # check data
        result_data = dst.data()[:]
        # print result_data, expected_result
        self.assertFloatTuplesAlmostEqual(result_data,expected_result,4)

    def test_m4_r1 (self):
        M=4
        R=1
        src_data = [0,0,0,1,0,0,1,2,0,1,2,3,1,2,3,4,2,3,4,5,3,4,5,6,4,5,6,7,5,6,7,8,6,7,8,9,7,8]
        expected_result = (0,0,0,1,2,3,4,5,6)
        
        src = blocks.vector_source_f(src_data)
        op = overlap_add_f(M,R,np.ones(M))
        #op.debug = True
        dst = blocks.vector_sink_f()

        self.tb.connect(src,op)
        self.tb.connect(op,dst)
        self.tb.run()

        # check data
        result_data = dst.data()[:]
        # print result_data, expected_result
        self.assertFloatTuplesAlmostEqual(result_data,expected_result,4)

    def test_m4_r2 (self):
        M=4
        R=2
        src_data = [0,0,0,1,0,1,2,3,2,3,4,5,4,5,6,7,6,7]
        expected_result = (0,0,0,1,2,3,4,5,)
        
        src = blocks.vector_source_f(src_data)
        op = overlap_add_f(M,R,np.ones(M))

        dst = blocks.vector_sink_f()

        self.tb.connect(src,op)
        self.tb.connect(op,dst)
        self.tb.run()

        # check data
        result_data = dst.data()[:]
        # print result_data, expected_result
        self.assertFloatTuplesAlmostEqual(result_data,expected_result,4)

    def test_window_overlapping (self):
        M = 8
        R = M/2
        op = overlap_add_f(M,R,())
        window = op.window()
        src_data = np.concatenate((
            np.concatenate((np.zeros(R),np.ones(R)))*window,
            np.ones(M)*window
        ))

        expected_result = [0,0,0,0,1,1,1,1]
        
        src = blocks.vector_source_f(src_data)
        dst = blocks.vector_sink_f()

        self.tb.connect(src,op)
        self.tb.connect(op,dst)
        self.tb.run()

        # check data
        result_data = dst.data()[:]
        #print result_data,expected_result
        self.assertFloatTuplesAlmostEqual(result_data,expected_result,4)

class qa_overlap_add_complex(gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_basic_m2_r1 (self):
        M=2
        R=1
        src_data = (0,1+1j,1+1j,2+2j,2+2j,3+3j,3+3j,4+4j,4+4j)
        expected_result = [0,1+1j,2+2j,3+3j]
        
        src = blocks.vector_source_c(src_data)
        op = overlap_add_c(M,R,np.ones(M))
        #op.debug = True
        # op.log("forecasted")
        dst = blocks.vector_sink_c()

        self.tb.connect(src,op)
        self.tb.connect(op,dst)
        self.tb.run()

        # check data
        result_data = dst.data()[:]
        # print result_data, expected_result
        self.assertFloatTuplesAlmostEqual(result_data,expected_result,4)


if __name__ == '__main__':
    gr_unittest.run(qa_overlap_add, "qa_overlap_add.xml")
    gr_unittest.run(qa_overlap_add_complex, "qa_overlap_add_complex.xml")