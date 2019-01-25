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

#ifndef INCLUDED_TCOLA_TCOLA_BASE_H
#define INCLUDED_TCOLA_TCOLA_BASE_H

#include <tcola/api.h>
#include <vector>

namespace gr {
  namespace tcola {

    class TCOLA_API tcola_base
    {
        private:
          unsigned d_window_size;
          unsigned d_hop_size;
          unsigned d_ratio;    
        
        protected:
          std::vector<float> d_window;

        public:
        static std::vector<float> create_default_window(unsigned windowSize, unsigned hopSize);

        tcola_base(unsigned windowSize, unsigned hopSize, const std::vector<float> &window);
        ~tcola_base();        

        virtual unsigned window_size() const { return d_window_size; }
        virtual unsigned hop_size() const { return d_hop_size; }
        unsigned ratio() const { return d_ratio; }
        virtual std::vector<float> window() const { return d_window; }
        
    };

  } // namespace tcola
} // namespace gr

#endif /* INCLUDED_TCOLA_TCOLA_BASE_H */

