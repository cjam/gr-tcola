/* -*- c++ -*- */

#define TCOLA_API

%include "gnuradio.i"			// the common stuff

// This isn't included in GRC 3.7.9 so copying it from
// https://github.com/gnuradio/gnuradio/blob/master/gnuradio-runtime/swig/gr_swig_block_magic.i
// Renamed it to avoid collisions in future release
%define TCOLA_SWIG_BLOCK_TMPL(PKG, BASE_NAME, TARGET_NAME...)
%template(BASE_NAME) gr:: ## PKG ## :: ## TARGET_NAME;
%template(BASE_NAME ## _sptr) boost::shared_ptr<gr:: ## PKG ## :: ## TARGET_NAME ## >;
%pythoncode %{
BASE_NAME ## _sptr.__repr__ = lambda self: "<gr_block %s (%d)>" % (self.name(), self.unique_id())
BASE_NAME = BASE_NAME.make
%}
%enddef


//load generated python docstrings
%include "tcola_swig_doc.i"

%{
#include "tcola/time_compression.h"
#include "tcola/overlap_add.h"
%}

%include "tcola/time_compression.h"
%include "tcola/overlap_add.h"

TCOLA_SWIG_BLOCK_TMPL(tcola, time_compression_f, time_compression<float>);
TCOLA_SWIG_BLOCK_TMPL(tcola, time_compression_c, time_compression<gr_complex>);
TCOLA_SWIG_BLOCK_TMPL(tcola, overlap_add_f, overlap_add<float>);
TCOLA_SWIG_BLOCK_TMPL(tcola, overlap_add_c, overlap_add<gr_complex>);

