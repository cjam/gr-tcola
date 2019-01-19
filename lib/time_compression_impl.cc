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
#include "time_compression_impl.h"

namespace gr {
  namespace tcola {


    template <class IN_T, class OUT_T, class TAP_T>
    typename time_compression<IN_T,OUT_T,TAP_T>::sptr
    time_compression<IN_T,OUT_T,TAP_T>::make(unsigned windowSize, unsigned hopSize, const std::vector<TAP_T> &taps)
    {
      return gnuradio::get_initial_sptr
        (new time_compression_impl<IN_T,OUT_T,TAP_T>(windowSize, hopSize, taps));
    }

    /*
     * The private constructor
     */
    template <class IN_T, class OUT_T, class TAP_T>
    time_compression_impl<IN_T,OUT_T,TAP_T>::time_compression_impl(unsigned windowSize, unsigned hopSize, const std::vector<TAP_T> &taps)
      : gr::block("time_compression<IN_T,OUT_T,TAP_T>",
              gr::io_signature::make(1, 1, sizeof(IN_T)),
              gr::io_signature::make(1, 1, sizeof(OUT_T)))
    {
      if(windowSize == 0)
	      throw std::out_of_range("time_compression_impl<IN_T,OUT_T,TAP_T>: windowSize must be > 0");
      if(hopSize == 0)
	      throw std::out_of_range("time_compression_impl<IN_T,OUT_T,TAP_T>: hopSize must be > 0");

      this->d_window_size=windowSize;
      this->d_hop_size=hopSize;

      this->d_history = windowSize;
      this->set_relative_rate((uint64_t)windowSize,(uint64_t)hopSize);
      this->set_output_multiple(windowSize);

    }

    /*
     * Our virtual destructor.
     */
    template <class IN_T, class OUT_T, class TAP_T>
    time_compression_impl<IN_T,OUT_T,TAP_T>::~time_compression_impl()
    {
    }

    template <class IN_T, class OUT_T, class TAP_T>
    void
    time_compression_impl<IN_T,OUT_T,TAP_T>::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    template <class IN_T, class OUT_T, class TAP_T>
    int
    time_compression_impl<IN_T,OUT_T,TAP_T>::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const IN_T *in = (const IN_T *) input_items[0];
      OUT_T *out = (OUT_T *) output_items[0];

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      this->consume_each(noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace tcola */
} /* namespace gr */

