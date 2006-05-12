// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SPECPOLAR_H
#define _SPECPOLAR_H

#include "SpecMult.h"


class SpecPolar : public SpecMult {
	
protected:

void inline convert(float* a, float* b);

public:

SpecPolar();
SpecPolar(SndObj* input,int vecsize=DEF_FFTSIZE,
		   float sr=DEF_SR);
~SpecPolar();

short DoProcess();

};

void
SpecPolar::convert(float* a, float* b){

float mag, pha;
mag = sqrt((*a)*(*a) + (*b)*(*b));
pha = atan((*b)/(*a));
*a=mag;
*b=pha;

}

#endif
