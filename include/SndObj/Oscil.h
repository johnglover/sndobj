
// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Oscil.h: interface of the Oscil abstract base class       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _OSCIL_H
#define _OSCIL_H

#include "SndObj.h"
#include "Table.h"


class Oscil : public SndObj {

 protected:
  Table* m_ptable;         // reference to a Table obj
  
  float m_fr; 
  float m_amp;
  float m_index;
  float m_incr;
  long  m_size; 

  SndObj* m_inputamp;

 public:
  void SetSr(float sr);
  float m_factor;
  Oscil();
  Oscil(Table* table, float fr=440.f, 
	float amp=1.f,  SndObj* inputfreq = 0, 
	SndObj* inputamp = 0, int vecsize = DEF_VECSIZE, float sr=DEF_SR);
  ~Oscil();

  short SetPhase(float phase); // returns error
  void SetTable(Table* table);
  void SetFreq(float fr, SndObj* InFrObj= 0){
    m_fr = fr;
    if(InFrObj)
      m_input = InFrObj; 
  }
 

  void SetAmp(float amp, SndObj* InAmpObj= 0){    
    m_amp = amp;
    if(InAmpObj)
      m_inputamp = InAmpObj;            
  }
 
  void SetFreq(SndObj* inputfr){ m_input = inputfr; }
  void SetAmp(SndObj* inputamp) { m_inputamp = inputamp; }


  int Connect(char* mess, void* input);
  int Set(char* mess, float value);
  short DoProcess();
  
};

#endif
