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


#ifndef INCLUDED_TCOLA_OVERLAP_ADD_H
#define INCLUDED_TCOLA_OVERLAP_ADD_H

#include <tcola/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace tcola {

    /*!
     * \brief <+description of block+>
     * \ingroup tcola
     *
     */
    class TCOLA_API overlap_add : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<overlap_add> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of tcola::overlap_add.
       *
       * To avoid accidental use of raw pointers, tcola::overlap_add's
       * constructor is in a private implementation
       * class. tcola::overlap_add::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned windowSize, unsigned hopSize, const std::vector<float> &window);

      virtual unsigned window_size() const = 0;
      virtual unsigned hop_size() const = 0;
      virtual std::vector<float> window() const = 0;
    };

  } // namespace tcola
} // namespace gr

#endif /* INCLUDED_TCOLA_OVERLAP_ADD_H */

