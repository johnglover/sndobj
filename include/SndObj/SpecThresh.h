// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SpecThresh_H
#define _SpecThresh_H

#include "SpecPolar.h"


class SpecThresh : public SpecPolar {
	
protected:

float m_thresh;

public:

void SetThreshold(float thresh){ m_thresh = thresh; }

int Set(char* mess, float value);

SpecThresh();
SpecThresh(float threshold, SndObj* input, int vecsize=DEF_FFTSIZE,
		   float sr=DEF_SR);
~SpecThresh();

short DoProcess();

};




#endif
