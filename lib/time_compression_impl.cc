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

#include <gnuradio/io_signature.h>
#include <gnuradio/fft/window.h>
#include "time_compression_impl.h"

using std::vector;

namespace gr {
  namespace tcola {

    time_compression::sptr
    time_compression::make(unsigned windowSize, unsigned hopSize)
    {
      return gnuradio::get_initial_sptr
        (new time_compression_impl(windowSize, hopSize));
    }

    /*
     * The private constructor
     */
    time_compression_impl::time_compression_impl(unsigned windowSize, unsigned hopSize)
      : gr::sync_interpolator("time_compression",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(float)), windowSize/hopSize),
              d_window_size(windowSize),
              d_hop_size(hopSize)
    {
      if( hopSize <= 0)
        throw std::out_of_range("time_compression_impl: hopSize must be > 0");
      if( windowSize < hopSize)
        throw std::out_of_range("time_compression_impl: windowSize must be > hopSize");
      if( (float)windowSize/hopSize != floor((float)windowSize/hopSize) )
        throw std::out_of_range("time_compression_impl: windowSize must be divisible by hopSize");

      this->set_output_multiple(windowSize);
      this->set_history(windowSize);

      // Build the sqrt hanning window
      this->d_window = new std::vector<float>(windowSize, 0);
      std::vector<float> window = gr::fft::window::build(gr::fft::window::WIN_HANN, windowSize+1, 0.0);
      std::transform (window.begin(), window.end()-1, this->d_window->begin(), sqrt);
    }

    /*
     * Our virtual destructor.
     */
    time_compression_impl::~time_compression_impl()
    {
      delete this->d_window;
    }

    
    int
    time_compression_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];


      for(int i=0; i<noutput_items/this->window_size; i++)
      {

        

      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace tcola */
} /* namespace gr */

