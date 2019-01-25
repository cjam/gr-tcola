/* -*- c++ -*- */

#define TCOLA_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "tcola_swig_doc.i"

%{
#include "tcola/time_compression.h"
#include "tcola/overlap_add.h"
%}

%include "tcola/time_compression.h"
GR_SWIG_BLOCK_MAGIC2(tcola, time_compression);
%include "tcola/overlap_add.h"
GR_SWIG_BLOCK_MAGIC2(tcola, overlap_add);
