// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _BUZZ_H
#define _BUZZ_H

#include "SndObj.h"
#include "HarmTable.h"
#include "Oscili.h"

class Buzz : public SndObj {

                       protected:

  
  HarmTable* m_ptable;         // reference to a Table obj

  Oscili* oscil1;
  Oscili* oscil2; 

  float m_fr; 
  float m_amp;
  short m_harm; 
  
  SndObj* m_inputamp;  

                         public:
  Buzz();  
  Buzz(float fr, float amp, short harms, SndObj* InFrObj=0,
       SndObj* InAmpObj=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Buzz();
  void SetFreq(float fr, SndObj* InFrObj=0);
  void SetAmp(float amp, SndObj* InAmpObj=0){
	  m_amp = amp;
	  m_inputamp = InAmpObj;
  }
  void SetSr(float sr);
  void SetHarm(int harm);
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  char* ErrorMessage();
  short DoProcess();
  
                              };

#endif

