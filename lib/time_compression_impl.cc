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

#include "time_compression_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/fft/window.h>
#include <volk/volk.h>

namespace gr {
  namespace tcola {

    time_compression::sptr
    time_compression::make(unsigned windowSize, unsigned hopSize, const std::vector<float> &window)
    {
      return gnuradio::get_initial_sptr
        (new time_compression_impl(windowSize, hopSize, window));
    }

    /*
     * The private constructor
     */
    time_compression_impl::time_compression_impl(unsigned windowSize, unsigned hopSize, const std::vector<float> &window)
      : tcola_base::tcola_base(windowSize, hopSize, window),
      gr::sync_interpolator("time_compression",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(float)), windowSize/hopSize)
    {
      // Set GNU Radio Scheduler Hints
      this->set_output_multiple(windowSize);      // Tell Scheduler to make requests for full windows
      this->set_history(windowSize-hopSize+1);    // We need these past samples in order to calculate the new window
    }

    /*
     * Our virtual destructor.
     */
    time_compression_impl::~time_compression_impl()
    {
    }
    
    int
    time_compression_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      unsigned outCount = 0;

      // Hop across the input signal in increments of hop_size
      for(int startIndex = 0; startIndex < noutput_items/this->ratio(); startIndex = startIndex + this->hop_size())
      {     
        // Output windows of the input signal
        for (int j=0; j<this->window_size(); j++)
        {
          float num = in[startIndex+j]*this->window().at(j);
          out[outCount++] = num;
        }
      }

      // Tell runtime system how many output items we produced.
      return outCount;
    }

  } /* namespace tcola */
} /* namespace gr */

