/* -*- c++ -*- */

#define FILTDES_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "filtdes_swig_doc.i"


%{
#include "gr_remez.h"
#include "gr_firdes.h"
#include "gr_iirdes.h"
%}

%include "gr_remez.i"
%include "gr_firdes.i"
%include "gr_iirdes.i"

