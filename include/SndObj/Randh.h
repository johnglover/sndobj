// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Randh.h: interface of the Randh class                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _RANDH_H 
#define _RANDH_H


#include "Rand.h"

class Randh : public Rand {

                       protected:
 
  float m_fr; 
  long m_period;
  long m_count;
  SndObj* m_inputfr;
  
			 public:
   
  Randh();
  Randh(float fr,float amp,SndObj* InFrObj=0,
	  SndObj* InAmpObj=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Randh();

  int Connect(char* mess, void* input);
  void SetSr(float sr);
  void SetFreq(float fr, SndObj* InFrObj = 0){
  
	  m_fr = fr;
	  m_period = (long) (m_fr > .1 ? m_sr/m_fr : m_sr/.1); 
      m_count = m_period;
      m_inputfr = InFrObj;
         
}
  int Set(char* mess, float value);
  short DoProcess();
  
                              };
#endif 


                        


