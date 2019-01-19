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

#ifndef INCLUDED_TCOLA_TIME_COMPRESSION_IMPL_H
#define INCLUDED_TCOLA_TIME_COMPRESSION_IMPL_H

#include <tcola/time_compression.h>

namespace gr {
  namespace tcola {
    template <class IN_T, class OUT_T, class TAP_T>
    class time_compression_impl : public time_compression<IN_T,OUT_T,TAP_T>
    {
     private:
        unsigned d_history;
        unsigned d_window_size;
        unsigned d_hop_size;
        std::vector<TAP_T> d_taps;
      // Nothing to declare in this block.

     public:
      time_compression_impl(unsigned windowSize, unsigned hopSize, const std::vector<TAP_T> &taps);
      ~time_compression_impl();

      unsigned history() const { return d_history; }
      void set_history(unsigned history) { d_history = history; }

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace tcola
} // namespace gr

#endif /* INCLUDED_TCOLA_TIME_COMPRESSION_IMPL_H */

