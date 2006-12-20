// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SpecVoc_H
#define _SpecVoc_H

#include "SpecPolar.h"


class SpecVoc : public SpecPolar {
	
protected:

public:

SpecVoc();
SpecVoc(SndObj* input, SndObj* input2, int vecsize=DEF_FFTSIZE,
		   float sr=DEF_SR);
~SpecVoc();

short DoProcess();

};




#endif
