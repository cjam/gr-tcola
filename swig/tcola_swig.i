/* -*- c++ -*- */

#define TCOLA_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "tcola_swig_doc.i"

%{
#include "tcola/time_compression.h"
%}

%include "tcola/time_compression.h"
GR_SWIG_BLOCK_MAGIC2_TMPL(tcola, time_compression_fff, time_compression<float,float,float>);
