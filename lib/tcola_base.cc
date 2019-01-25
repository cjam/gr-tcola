/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "tcola_base.h"
#include <gnuradio/fft/window.h>
#include <algorithm>

namespace gr {
  namespace tcola {

    std::vector<float> 
    tcola_base::create_default_window(unsigned windowSize, unsigned hopSize)
    {
      std::vector<float> newWindow = gr::fft::window::build(gr::fft::window::WIN_HANN, windowSize+1, 0.0);
      newWindow.resize(windowSize);
      std::transform (newWindow.begin(), newWindow.end(), newWindow.begin(), sqrt);

      return newWindow;
    }

    tcola_base::tcola_base(unsigned windowSize, unsigned hopSize, const std::vector<float> &window)
    {
      if( hopSize <= 0)
        throw std::invalid_argument("time_compression_impl: hopSize must be > 0");
      if( windowSize < hopSize)
        throw std::invalid_argument("time_compression_impl: windowSize must be > hopSize");
      if( (float)windowSize/hopSize != floor((float)windowSize/hopSize) )
        throw std::invalid_argument("time_compression_impl: windowSize must be divisible by hopSize");    

      this->d_hop_size = hopSize;
      this->d_window_size = windowSize;
      this->d_ratio = windowSize/hopSize;     
      this->d_window = window;

      // If we weren't given a window, then create one
      if(this->window().size() == 0){     
        this->d_window.resize(windowSize);
        std::vector<float> newWindow = tcola_base::create_default_window(windowSize,hopSize);
        this->d_window.assign(newWindow.begin(),newWindow.end());        
      }

    }

    tcola_base::~tcola_base()
    {
    }

  } /* namespace tcola */
} /* namespace gr */

