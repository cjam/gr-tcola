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

import numpy as np
from gnuradio import gr
from TcolaBase import TcolaBase

class time_compression(TcolaBase,gr.interp_block):    
    """
    docstring for block time_compression
    """
    def __init__(self, windowSize=100,hopSize=50,windowType='hanning'):
        TcolaBase.__init__(self,windowSize,hopSize,windowType)
        gr.interp_block.__init__(self,
            name="time_compression",    # Block Name
            in_sig=[np.float32],        # Input Signal
            out_sig=[np.float32],       # Output Signal
            interp=self.ratio           # Interpolation
        )
        self.set_history(windowSize)
        self.set_output_multiple(windowSize)

    def work(self, input_items, output_items):
        inputSignal = input_items[0]
        out = output_items[0]
        M = self.windowSize
        R = self.hopSize

        outputSignal = np.asarray([])
        
        self.log("Input",inputSignal)
        for index in np.arange(0,len(inputSignal)-R,R):
            if index + M > len(inputSignal):
                break
            self.log("Index",index)
            windowed_input = inputSignal[index:index+M]*self.windowCoeffs
            self.log("Windowed Input",windowed_input)            
            outputSignal=np.concatenate([outputSignal[:], windowed_input[:]])

        # print "Output Signal",outputSignal
        out[:] = outputSignal
        return len(out)

