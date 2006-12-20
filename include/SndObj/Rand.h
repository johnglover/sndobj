// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Rand.h: interface of the Rand class                       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _RAND_H 
#define _RAND_H

#include "SndObj.h"
#include <stdlib.h>

const float MAXR = float(RAND_MAX/2);



class Rand : public SndObj {

                       protected:
  
  float m_amp;
  
 
			 public:
   
  Rand();
  Rand(float amp, SndObj* InAmpObj = 0, int vecsize=DEF_VECSIZE, 
	  float sr = DEF_SR);
  ~Rand();  
  
  void SetAmp(float amp, SndObj* InAmpObj = 0){ 
    m_amp = amp;
    m_input = InAmpObj;
   }
  
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  short DoProcess();
  
                              };

 #endif






