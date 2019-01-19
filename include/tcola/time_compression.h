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


#ifndef INCLUDED_TCOLA_TIME_COMPRESSION_H
#define INCLUDED_TCOLA_TIME_COMPRESSION_H

#include <tcola/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace tcola {

    /*!
     * \brief <+description of block+>
     * \ingroup tcola
     *
     */
    template<class IN_T, class OUT_T, class TAP_T>
    class TCOLA_API time_compression : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr< time_compression<IN_T,OUT_T,TAP_T> > sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of tcola::time_compression.
       *
       * To avoid accidental use of raw pointers, tcola::time_compression's
       * constructor is in a private implementation
       * class. tcola::time_compression::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned windowSize, unsigned hopSize, const std::vector<TAP_T> &taps);
      virtual unsigned window_size() const = 0;
      virtual unsigned hop_size() const = 0;

      virtual void set_taps(const std::vector<TAP_T> &taps) = 0;
      virtual std::vector<TAP_T> taps() const = 0;
    };

    typedef time_compression<float, float, float> time_compression_fff;

  } // namespace tcola
} // namespace gr

#endif /* INCLUDED_TCOLA_TIME_COMPRESSION_H */
