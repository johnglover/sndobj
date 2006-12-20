// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//////////////////////////////////////////////////////
//     IFGram.h: Instant Freq Analysis
//            
//          Victor Lazzarini, 2003
//           
/////////////////////////////////////////////////////////

#ifndef _IFGram_H
#define _IFGram_H
#include "PVA.h"

class IFGram : public PVA {

protected:


float* m_diffwin; // difference window
float* m_fftdiff; // holds fft of diff window
float* m_diffsig;
float* m_pdiff;

private:

void inline IFAnalysis(float* signal); 

public:

	IFGram();
	IFGram(Table* window, SndObj* input, float scale=1.f,
		 int fftsize=DEF_FFTSIZE, int hopsize=DEF_VECSIZE, float sr=DEF_SR);

	~IFGram();
 
	int Set(char* mess, float value);
	int Connect(char* mess, void* input);
    void SetFFTSize(int fftsize);
	short DoProcess();
  
};

#endif





