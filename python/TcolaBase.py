import numpy as np
from math import floor

class TcolaBase(object):
    def __init__(self, windowSize=100,hopSize=50,windowType='hanning'):
        TcolaBase.verify_tcola_params(windowSize,hopSize)

        self.windowSize = windowSize
        self.hopSize = hopSize
        self.ratio = int(windowSize/hopSize)
        self.delayMatrix = np.zeros([windowSize,self.ratio]) 
        self.windowCoeffs = TcolaBase.generate_window_coeffs(windowSize,windowType)
        self.inPhaseCnt = 0

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
        
    @staticmethod
    def generate_window_coeffs(windowSize,windowType='hanning'):
        """
        Generates Window Coefficients for a given window size and type
            :param windowSize: 
            :param windowType='hanning': the type of window 'hanning' or 'rectangular' 
        """
        if windowType.lower() is 'hanning':
            return np.sqrt(np.hanning(windowSize))
        else: # Default to rectangular window
            return np.ones(windowSize)