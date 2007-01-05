// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
// Rand.cpp : implementation of the Rand class                //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Rand.h"
#include <time.h>

Rand::Rand(){
  m_amp = 1.f;
  m_input = 0;
  srand((unsigned)time(0));
  AddMsg("amplitude",21);
}

Rand::Rand(float amp, SndObj* InAmpObj, int vecsize, float sr):
  SndObj(InAmpObj, vecsize, sr){
  m_amp = amp;
  m_sr = sr;
  srand((unsigned)time(0));
  AddMsg("amplitude",21);
}

Rand::~Rand(){}


///////////// OPERATIONS ////////////////////////////////////////
int 
Rand::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetAmp(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}

int 
Rand::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    m_input = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }


}
short
Rand :: DoProcess(){ 
  if(!m_error){
    float amp;
    for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){
      if(m_enable){
	amp = m_amp + (m_input== 0 ? 0 : m_input->Output(m_vecsize));
	m_output[m_vecpos] = (((float)rand() - MAXR)/MAXR)*amp;
      }

      else { m_output[m_vecpos] = 0.f; }
    }
    return 1;
  }
  else return 0;
}
