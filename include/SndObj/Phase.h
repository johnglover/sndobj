// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Phase.h: interface of the Phase class.                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _Phase_H
#define _Phase_H

#include "SndObj.h"


class Phase : public SndObj {

 protected:
  float m_freq;
  float m_offset;

 public:
   
  Phase();
  Phase(float freq, SndObj* FreqInput = 0 , float offset = 0.f,
	int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Phase();

  void SetFreq(float freq, SndObj* FreqInput = 0){
    m_freq = freq;
    m_input = FreqInput;
  }
    
  void SetPhase(float offset){ m_offset = offset; }
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  short DoProcess();

};

#endif
 
