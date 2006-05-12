// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SPECMULT_H
#define _SPECMULT_H

#include "SndObj.h"
#include "Table.h"

class SpecMult : public SndObj{

protected:

SndObj* m_input2;
Table*  m_spectable;
bool m_dynamic;

public:

SpecMult();
SpecMult(SndObj* input1, SndObj* input2, int vecsize=DEF_FFTSIZE,
		 float sr=DEF_SR);
SpecMult(Table* spectab, SndObj* input1, int vecsize=DEF_FFTSIZE,
		 float sr=DEF_SR);
~SpecMult();

int Connect(char* mess, void* input);
void SetInput2(SndObj* input2){ m_input2 = input2; m_dynamic = true; }
void SetTable(Table *spectab) { 
	if(spectab->GetLen() >= m_vecsize){
		m_spectable = spectab;
		m_dynamic = false;
	}
}

short DoProcess();



};

#endif
