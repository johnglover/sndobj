// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//////////////////////////////////////////////////////
// PVS.h: Phase Vocoder Synthesis Class
//
//        Victor Lazzarini, 2003
//
/////////////////////////////////////////////////////////

#ifndef _PVS_H
#define _PVS_H

#include "IFFT.h"

class PVS : public IFFT {

protected:

int m_rotcount; // rotation counter
float m_factor;  // conversion factor
float* m_phases;  // old phases

private:
void inline pvsynthesis(float* signal); 

public:

PVS();
PVS(Table* window, SndObj* input, int fftsize=DEF_FFTSIZE,
		   int hopsize=DEF_VECSIZE, float sr=DEF_SR);
~PVS();

 
	int Set(char* mess, float value);
        void SetFFTSize(int fftsize);
	void SetHopSize(int hopsize);

short DoProcess();


};




#endif
