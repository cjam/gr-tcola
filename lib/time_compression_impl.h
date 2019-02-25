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
#include "tcola_base.h"

namespace gr {
  namespace tcola {
    template<class T>
    class time_compression_impl : public time_compression<T>, public tcola_base
    {
     public:
      time_compression_impl(unsigned windowSize, unsigned hopSize, const std::vector<float> &window);
      ~time_compression_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      unsigned window_size() const { return tcola_base::window_size(); }
      unsigned hop_size() const { return tcola_base::hop_size(); }
      std::vector<float> window() const { return tcola_base::window(); }
    };

  } // namespace tcola
} // namespace gr

#endif /* INCLUDED_TCOLA_TIME_COMPRESSION_IMPL_H */

