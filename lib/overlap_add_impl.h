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

#ifndef INCLUDED_TCOLA_OVERLAP_ADD_IMPL_H
#define INCLUDED_TCOLA_OVERLAP_ADD_IMPL_H

#include <tcola/overlap_add.h>

namespace gr {
  namespace tcola {

    class overlap_add_impl : public overlap_add
    {
     private:
      unsigned d_window_size;
      unsigned d_hop_size;
      std::vector<float> d_window;
      std::vector<float> d_output_window;

     public:
      overlap_add_impl(unsigned windowSize, unsigned hopSize, const std::vector<float> &window);
      ~overlap_add_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      bool start();

      unsigned window_size() const { return d_window_size; }
      unsigned hop_size() const { return d_hop_size; }
      std::vector<float> window() const { return d_window; }
    };

  } // namespace tcola
} // namespace gr

#endif /* INCLUDED_TCOLA_OVERLAP_ADD_IMPL_H */

