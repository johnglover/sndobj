////////////////////////////////////////////////////////
// IFFT_alternative.cpp : a self-contained alternative
//  to the IFFT class, not using FFTW, using its own
//  FFT functions. Slower, but not depending on other code.
//  Victor Lazzarini, 2003
/////////////////////////////////////////////////////////

#ifndef _IFFT_H
#define _IFFT_H

#include "FFT.h"

class IFFT : public FFT {

protected:

void inline ifft(float* signal);

public:

IFFT::IFFT();
IFFT::IFFT(Table* window, SndObj* input, int fftsize = DEF_FFTSIZE, 
		   int hopsize=DEF_VECSIZE, int vecsize = DEF_VECSIZE, float sr=DEF_SR);
IFFT::~IFFT();

short DoProcess();


};


#endif
          