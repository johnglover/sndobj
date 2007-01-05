// Copyright (c)Rory Walsh May 2003  
// See License.txt for a disclaimer of all warranties
// and licensing information

//*************************************************************//
// HiPass.h : 1st order high pass filter                       //
//                                			      //
//         Rory Walsh May 2003   			      //
//                                          		      //
//*************************************************************//
#ifndef _HIPASS_H 
#define _HIPASS_H

#include "LowPass.h"


class HiPass : public LoPass
 
{
 protected:


 public:

  HiPass();
  HiPass(float freq, SndObj* inObj, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~HiPass();

  void SetFreq(float fr){
    m_fr = fr;
    double  C = 2 - cos(2*PI*m_fr/m_sr);	
    m_b1 = C - sqrt((C*C) - 1); 
    m_a = 1 - m_b1;
  }

  void SetSr(float sr){
    m_sr = sr;
    double  C = 2 - cos(2*PI*m_fr/m_sr);	
    m_b1 = C - sqrt((C*C) - 1); 
    m_a = 1 - m_b1;	
  }

  int Set(char* mess, float value);

};

#endif
