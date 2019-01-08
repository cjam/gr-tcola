from math import floor
import numpy as np

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