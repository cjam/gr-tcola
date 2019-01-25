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
#include <algorithm>

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
      : tcola_base(windowSize,hopSize,window),
        gr::sync_decimator("overlap_add",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)), windowSize/hopSize),
        d_normalization_gain(1.0)        
    {
      this->d_output_window.resize(this->window_size());
      // Set GNU Radio Scheduler Hints
      this->set_output_multiple(hopSize);      // Tell Scheduler to make requests for full windows
    }

    bool overlap_add_impl::start(){
      this->d_output_window.resize(this->window_size());
      std::fill(this->d_output_window.begin(),this->d_output_window.end(),0);
      
      // Calculate the normalization gain 
      this->d_normalization_gain = this->calculate_normalization_gain();

      return true;
    }

    float overlap_add_impl::calculate_normalization_gain(){
      overlap_add_impl ola(tcola_base::window_size(), tcola_base::hop_size(), tcola_base::window());
      ola.d_normalization_gain = 1.0;

      // Allocate a vector full of windows
      std::vector<float> inputData(ola.ratio()*ola.window_size());
      for(int i=0; i< ola.ratio(); i++){
        for(int j=0; j<ola.window().size(); j++){
            inputData[i*ola.window().size()+j] = ola.window()[j];
        }        
      }
      std::vector<const void*> inputs(1,inputData.data());      
      
      // Allocate output buffer
      std::vector<float> outData(ola.ratio()*ola.hop_size());
      std::vector<void*> outputs(1,outData.data());
     
      // Here we are using a temporary overlap and add block to overlap
      // and windows, then we're taking the max as our normalization gain
      float numOut = ola.work(outData.size(), inputs, outputs);
      float max = *(std::max_element( outData.data(), outData.data()+outData.size()));
      
      return 1.0/max;
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

      
      unsigned outCount = 0;
      for(int startIndex = 0; startIndex < noutput_items*this->ratio(); startIndex = startIndex + this->window_size())
      {     
        for (int j=0; j<this->window_size(); j++)
        {         
          // Overlap and add using our internal output window
          this->d_output_window[j] += in[startIndex+j]*this->window()[j];
       
          // For every window we output a hop_size of samples
          if(j < this->hop_size()){
            out[outCount++] = this->d_output_window[j]*this->d_normalization_gain;
          }
        }

        // Once we've output our hop size of samples, we need to rotate the
        // output window by hop_size and then set the last hop_size samples
        // to zero
        std::rotate(
          this->d_output_window.begin(),
          this->d_output_window.begin()+this->hop_size(),
          this->d_output_window.end()
        );
        std::fill(this->d_output_window.end()-this->hop_size(),this->d_output_window.end(),0);
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace tcola */
} /* namespace gr */

