 
////////////////////////////////////////////////////////////////////////
// This file is part of the SndObj library
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
//
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
          