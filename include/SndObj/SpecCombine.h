// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SpecCombine_H
#define _SpecCombine_H

#include "SpecCart.h"


class SpecCombine : public SpecCart {
	
protected:

int m_halfsize;

public:

SpecCombine();
SpecCombine(SndObj* magin, SndObj* phasin, 
			int vecsize=DEF_FFTSIZE, float sr=DEF_SR);
~SpecCombine();

void SetPhaseInput(SndObj* phasin){ m_input2 = phasin; }
void SetMagInput(SndObj* magin) { m_input = magin; }

int Connect(char* mess, void* input);

short DoProcess();

};


#endif
