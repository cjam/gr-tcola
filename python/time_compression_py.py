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
        
        self.set_output_multiple(windowSize)
        self.set_history(windowSize)        
    
    def forecast(self,noutput_items,ninput_items_required):
        n_required = int((noutput_items+1.0)*self.hopSize/self.windowSize)+self.history()-1
        for i in range(len(ninput_items_required)):
            ninput_items_required[i]= n_required

    def start(self):
        forecasted = [0]
        self.forecast(self.windowSize,forecasted)
        self.log("Forecast",forecasted)

        return True

    def work(self, input_items, output_items):
        inputSignal = input_items[0]
        out = output_items[0]
        M = self.windowSize
        R = self.hopSize

        outCount = 0
        # self.log("Input",inputSignal)
        for index in np.arange(0,len(inputSignal)-R,R):
            if index + M > len(inputSignal):
                break     
            out[outCount:outCount+M] = inputSignal[index:index+M]*self.windowCoeffs
            outCount = outCount + M   
        
        return outCount

