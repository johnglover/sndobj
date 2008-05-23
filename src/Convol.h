 
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
// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

///////////////////////////////////////////////
// Convol.h: Fast convolution using a tabulated
//             impulse response
//
//           VL, 2003
/////////////////////////////////////////////


#ifndef _CONVOL_H
#define _CONVOL_H
#include "SndObj.h"
#include "Table.h"
#include <rfftw/rfftw.h>

class Convol: public SndObj {


 protected:

  Table* m_table;
  float* m_impulse;
  float* m_sigframe;
  float* m_outframe;
  float* m_overlap;

  int m_L;
  int m_count;
  int m_fftsize;
  float m_scale;

  rfftw_plan m_fwd;
  rfftw_plan m_inv;

  void inline mult(float* a, float* b, float* res);
  void inline fft(float* in, float* out);
  void inline ifft(float* in, float* out);

 public:

  // constructors / destructor
  Convol();
  Convol(Table* impulse, SndObj* input, float scale=1.f,
	 int vecsize=DEF_VECSIZE, float sr=DEF_SR);

  ~Convol();
   
  int Connect(char* mess, void* input);
  int Set(char* mess, float value);
  void SetImpulse(Table* impulse, float scale);


  short DoProcess();

};
	
#endif

