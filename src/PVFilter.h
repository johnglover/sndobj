// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _PVFilter_H
#define _PVFilter_H

#include "SpecInterp.h"

class PVFilter : public SpecInterp {
	
protected:
float   m_amnt; 

public:

PVFilter();
PVFilter(SndObj* input, SndObj* filspec, float amnt=1.f,
			   SndObj* amntobj=0, int vecsize=DEF_FFTSIZE,
		   float sr=DEF_SR);
PVFilter(Table* filtertable, SndObj* input, float amnt=1.f,
	   SndObj* amntobj=0, int vecsize=DEF_FFTSIZE,
		   float sr=DEF_SR );
~PVFilter();

int Connect(char* mess, void* input);
int Set(char* mess, float value);

void SetFilterInput(SndObj* filobj){ SetInput2(filobj);}
void SetFilterTable(Table* filtab) { SetTable(filtab);}

void SetAmount(float amnt, SndObj* amntobj=0){
	    m_amnt = amnt;
        m_interpobj = amntobj;
}

short DoProcess();

};

#endif
