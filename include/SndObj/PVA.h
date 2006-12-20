// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//////////////////////////////////////////////////////
//     PVA.h: Phase Vocoder Analysis Class
//            
//          Victor Lazzarini, 2003
//           
/////////////////////////////////////////////////////////

#ifndef _PVA_H 
#define _PVA_H
#include "FFT.h"

class PVA : public FFT {

protected:

int  m_rotcount; // rotation counter 
float m_factor;  // conversion factor
float* m_phases;

private:

void inline pvanalysis(float* signal); 

public:

	PVA();
	PVA(Table* window, SndObj* input, float scale=1.f,
		 int fftsize=DEF_FFTSIZE, int hopsize=DEF_VECSIZE, float sr=DEF_SR);

	~PVA();
    	float Outphases(int pos){ return m_phases[pos]; } // reads phase output.
	int Set(char* mess, float value);
    void SetFFTSize(int fftsize);
	void SetHopSize(int hopsize);
	short DoProcess();
  
};

#endif





