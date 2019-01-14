from __future__ import print_function
import numpy as np
from math import floor

class TcolaBase(object):
    def __init__(self, windowSize=100,hopSize=50,windowType='hanning'):
        TcolaBase.verify_tcola_params(windowSize,hopSize)

        self.windowType = windowType
        self.windowSize = windowSize
        self.hopSize = hopSize
        self.ratio = int(windowSize/hopSize)
        self.delayMatrix = np.zeros([windowSize,self.ratio]) 
        self.windowCoeffs = self.generate_window_coeffs()
        self.inPhaseCnt = 0
        
        self.debug = False

    @staticmethod
    def verify_tcola_params(windowSize,hopSize):
        """
        Verify the TCOLA parameters for use in TCOLA
            :param windowSize: size of window
            :param hopSize: size of hop
        """
        if hopSize <= 0:
            raise ValueError("Hop Size (hopSize) must be greater than 0")
        if windowSize < hopSize:
            raise ValueError("Window Size (windowSize) must be greater or equal to Hop Size (hopSize)")
        if windowSize/float(hopSize) != floor(windowSize/float(hopSize)):
            raise ValueError("Window Size must be divisible by Hop Size" )

    def generate_window_coeffs(self):
        """
        Generates Window Coefficients for a given window size and type
        """
        if self.windowType.lower() == 'hanning':
            return np.sqrt(np.hanning(self.windowSize+1))[:-1]
        else: # Default to rectangular window
            return np.ones(self.windowSize)

    def log(self,*args):
        if(self.debug):
            for v in args:
                print(v,' ',end='')
            print('')

