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
#include "overlap_add_impl.h"

namespace gr {
  namespace tcola {

    overlap_add::sptr
    overlap_add::make(unsigned windowSize, unsigned hopSize, const std::vector<float> &window)
    {
      return gnuradio::get_initial_sptr
        (new overlap_add_impl(windowSize, hopSize, window));
    }

    /*
     * The private constructor
     */
    overlap_add_impl::overlap_add_impl(unsigned windowSize, unsigned hopSize, const std::vector<float> &window)
      : gr::sync_decimator("overlap_add",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)), windowSize/hopSize),
              d_window_size(windowSize),
              d_hop_size(hopSize),
              d_window(window)
    {
      // Set GNU Radio Scheduler Hints
      this->set_output_multiple(hopSize);      // Tell Scheduler to make requests for full windows
    }

    bool overlap_add_impl::start(){
      // Create the output window which we use to store state between
      // the calls to work
      this->d_output_window = *(new std::vector<float>(this->window_size(),0));
      return true;
    }

    /*
     * Our virtual destructor.
     */
    overlap_add_impl::~overlap_add_impl()
    {
    }

    int
    overlap_add_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      const unsigned M = this->window_size();
      const unsigned R = this->hop_size();

      unsigned outCount = 0;

      for(int startIndex = 0; startIndex < noutput_items*M/R; startIndex = startIndex + M)
      {     
        for (int j=0; j<M; j++)
        {
          // std::cout << " start: " << startIndex;
          // std::cout << " start+j: " << startIndex+j;
          float num = in[startIndex+j]*this->window().at(j);
          // std::cout << " num: " << num;
          // std::cout << " outCount: " << outCount << "\r\n";
          out[outCount++] = num;
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace tcola */
} /* namespace gr */

