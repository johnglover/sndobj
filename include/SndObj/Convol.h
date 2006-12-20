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
#include <rfftw.h>

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

