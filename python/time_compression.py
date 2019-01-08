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
    
    def work(self, input_items, output_items):
        in0 = input_items[0]
        out = output_items[0]
        M = self.windowSize
        R = self.hopSize

        outputSignal = np.asarray([])

        for sample in in0:
            # Commutate the input samples. Each input sample has M/R destinations. 
            for n in np.arange(0, M/R):
                self.delayMatrix[n*R+self.inPhaseCnt, n] = sample
            # Increment the phase counter
            self.inPhaseCnt += 1

            # Process if we have reached the hop size. Internally each phase
            # runs at f1/R. 
            if self.inPhaseCnt == R:

                # "Interpolate" by serializing all M phases from the last column of the delay matrix
                # multiplied by the window coeffs (output commutator)
                # delayMatrix[:,-1] means all rows from the last column.
                # The output sample rate is f2 = f1*M/R
                outputSignal = np.concatenate([outputSignal, self.delayMatrix[:,-1]*self.windowCoeffs])

                # Shift the columns of the delay matrix to the right.
                # delayMatrix[:,1:] means all rows from columns 1 to the end.
                # delayMatrix[:,:-1] means all rows from column 0 up to but not 
                # including the last column.
                self.delayMatrix[:,1:] = self.delayMatrix[:,:-1]

                # Reset the counter.
                self.inPhaseCnt = 0

        # <+signal processing here+>
        out[:] = outputSignal
        return len(out)

