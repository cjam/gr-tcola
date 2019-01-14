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
        
        self.set_history(windowSize)
        self.set_output_multiple(windowSize)

    def start(self): 
        self.log("Normalization Gain", self.normalizationGain)
        return True

    def work(self, input_items, output_items):
        inputSignal = input_items[0]
        out = output_items[0]
        M = self.windowSize
        R = self.hopSize

        outputSignal = np.zeros(int(len(inputSignal)/self.ratio))
        outputSignal[0:] = inputSignal[0:R]
        self.log("Output Length",outputSignal)
        self.log("Input",inputSignal)
        for index in np.arange(R,len(inputSignal)-R,R):
            outIndex = index-R
            if index + M > len(inputSignal):
                break
            self.log("Index",index)
            self.log("Output Window",outputSignal[outIndex:outIndex+M])
            windowed_input = inputSignal[index:index+M]*self.windowCoeffs
            outputSignal[outIndex:outIndex+M] = outputSignal[outIndex:outIndex+M]
            self.log("Windowed Input",windowed_input)            
            outputSignal=np.concatenate([outputSignal[:], windowed_input[:]])

        # Iterate through the input samples
        #for sample in inputSignal:

            # # Commutate the input samples. Each input sample has only
            # # one destination. Apply the window coeffs.
            # self.delayMatrix[self.inPhaseCnt, -(self.inPhaseCnt/R+1)] = sample*self.windowCoeffs[self.inPhaseCnt]
    
            # # Increment the phase counter
            # self.inPhaseCnt += 1

            # # Process if we have reached the window size 
            # # Internally each phase runs at f2/M = f1/R 
            # if self.inPhaseCnt == M:

            #     # Create the R output phases by adding the appropriate R/M phases together
            #     # from the last column of the delay matrix.
            #     # delayMatrix[n::R, -1] means from the last (-1) column, 
            #     # take every Rth row, starting from n.
            #     filtOutput = np.zeros(R)
            #     for n in np.arange(0, R):
            #         filtOutput[n] = np.sum(self.delayMatrix[n::R,-1])*self.normalizationGain

            #     # "Interpolate" by serializing all R output phases (output commutator)
            #     outputSignal = np.concatenate([outputSignal, filtOutput])

            #     # Shift the columns of the delay matrix to the right.
            #     # delayMatrix[:,1:] means all rows from columns 1 to the end.
            #     # delayMatrix[:,:-1] means all rows from the first column up to but not 
            #     # including the last column.
            #     self.delayMatrix[:,1:] = self.delayMatrix[:,:-1]

            #     # Reset the counter.
            #     self.inPhaseCnt = 0

        out[:] = outputSignal
        return len(out)

