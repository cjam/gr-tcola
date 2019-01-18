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

class overlap_add(TcolaBase,gr.decim_block):
    """
    docstring for block overlap_add
    """
    def __init__(self, windowSize=100,hopSize=50,windowType='hanning'):
        TcolaBase.__init__(self,windowSize,hopSize,windowType)
        gr.decim_block.__init__(self,
            name="overlap_add",
            in_sig=[np.float32],
            out_sig=[np.float32], 
            decim=self.ratio
        )
        if windowType == 'hanning':
            self.normalizationGain = 2.0/self.ratio
        elif windowType == 'rect':
            self.normalizationGain = 1.0/self.ratio

        self.set_output_multiple(hopSize)

    def forecast(self,noutput_items,ninput_items_required):
        for i in range(len(ninput_items_required)):
            ninput_items_required[i]=noutput_items*self.ratio

    def start(self): 
        self.outputWindow = np.zeros(self.windowSize)
        self.log("Normalization Gain", self.normalizationGain)
        self.log("Window Size",self.windowSize,"Hop Size",self.hopSize,"Ratio",self.ratio)

        forecasted = [0]
        self.forecast(1,forecasted)
        self.log("Forecast",forecasted)

        return True

    def work(self, input_items, output_items):
        inputSignal = input_items[0]
        out = output_items[0]
        M = self.windowSize
        R = self.hopSize

        outCount = 0
        # self.log("Requested Output length",len(out))

        # self.log("Input",inputSignal)
        for index in np.arange(0,len(inputSignal),M):
            if index + M > len(inputSignal):
                break
            # self.log("Index",index)
            windowed_input = inputSignal[index:index+M]*self.windowCoeffs
            # self.log("Windowed Input",windowed_input)  
            self.outputWindow = np.add(self.outputWindow,windowed_input)
            # self.log("Output Window", self.outputWindow)
            out[outCount:outCount+R] = self.outputWindow[0:R]*self.normalizationGain
            outCount = outCount + R
            # self.log("Output Signal", out)
            self.outputWindow = np.concatenate((self.outputWindow[R:], np.zeros(R)))
            # self.log("Output Window", self.outputWindow)

        
        return outCount

