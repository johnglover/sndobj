// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SpecCart_H
#define _SpecCart_H

#include "SpecMult.h"


class SpecCart : public SpecMult {
	
protected:

void inline convert(float* a, float* b);

public:

SpecCart();
SpecCart(SndObj* input,int vecsize=DEF_FFTSIZE,
		   float sr=DEF_SR);
~SpecCart();

short DoProcess();

};

void
SpecCart::convert(float* a, float* b){

float re, im;
re = (*a)*cos(*b);
im = (*a)*sin(*b);
*a=re;
*b=im;

}

#endif
