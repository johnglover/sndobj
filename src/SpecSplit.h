// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SpecSplit_H
#define _SpecSplit_H

#include "SpecPolar.h"


class SpecSplit : public SpecPolar {
	
protected:

SndObj* m_channel;
int m_halfsize;

public:

SndObj* magnitude;
SndObj* phase;

SpecSplit();
SpecSplit(SndObj* input,int vecsize=DEF_FFTSIZE+2,
		   float sr=DEF_SR);
~SpecSplit();

short DoProcess();

};




#endif
