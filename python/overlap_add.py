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

class overlap_add(gr.decim_block):
    """
    docstring for block overlap_add
    """
    def __init__(self, windowSize=100,hopSize=50):
        verify_tcola_params(windowSize,hopSize)
        ratio = int(windowSize/hopSize)
        gr.decim_block.__init__(self,
            name="overlap_add",
            in_sig=[np.float32],
            out_sig=[np.float32], 
            decim=ratio
        )
        self.windowSize = windowSize
        self.hopSize = hopSize
        self.delayMatrix = np.zeros([windowSize,ratio)])


    def work(self, input_items, output_items):
        in0 = input_items[0]
        out = output_items[0]
        M = self.windowSize
        R = self.hopSize

        outputSignal = np.asarray([])

        # Iterate through the input samples
    for sample in inputSignal:

        # Commutate the input samples. Each input sample has only
        # one destination. Apply the window coeffs.
        delayMatrix[inPhaseCnt, -(inPhaseCnt/R+1)] = sample*winCoeffs[inPhaseCnt]
 
        # Increment the phase counter
        inPhaseCnt += 1

        # Process if we have reached the window size 
        # Internally each phase runs at f2/M = f1/R 
        if inPhaseCnt == M:

            # Create the R output phases by adding the appropriate R/M phases together
            # from the last column of the delay matrix.
            # delayMatrix[n::R, -1] means from the last (-1) column, 
            # take every Rth row, starting from n.
            filtOutput = np.zeros(R)
            for n in np.arange(0, R):
                filtOutput[n] = np.sum(delayMatrix[n::R,-1])

            # Normalize the output gain.
            filtOutput /= M/(2.0*R)

            # "Interpolate" by serializing all R output phases (output commutator)
            outputSignal = np.concatenate([outputSignal, filtOutput])

            # Shift the columns of the delay matrix to the right.
            # delayMatrix[:,1:] means all rows from columns 1 to the end.
            # delayMatrix[:,:-1] means all rows from the first column up to but not 
            # including the last column.
            delayMatrix[:,1:] = delayMatrix[:,:-1]

            # Reset the counter.
            inPhaseCnt = 0

        out[:] = outputSignal
        return len(out)

