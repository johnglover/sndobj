// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
// Filter.cpp : implementation of the Filter base class       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#include "Filter.h"

Filter::Filter(){

  m_fr = 1000.f;
  m_bw = 250.f;
  m_delay = new double[2];
  m_delay[0] = m_delay[1] = 0.f;

  SetParam(m_fr, m_bw);

  AddMsg("frequency", 21);
  AddMsg("bandwidth", 22);


}

Filter::Filter(float fr, float bw, SndObj* inObj, int vecsize, float sr):
  SndObj(inObj, vecsize, sr){

  m_fr = fr;
  m_bw = bw;

  m_delay = new double[2];
  m_delay[0] = m_delay[1] = 0.f;

  SetParam(m_fr, m_bw);

  AddMsg("frequency", 21);
  AddMsg("bandwidth", 22);


}

Filter::~Filter(){
  delete[] m_delay;
}

int
Filter::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetFreq(value);
    return 1;

  case 22:
    SetBW(value);
    return 1;

  case 1:
    SetSr(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }

}

void
Filter::SetBW(float bw){

  m_bw = bw;
  SetParam(m_fr, m_bw);

}

void
Filter::SetFreq(float fr){

  m_fr = fr;
  SetParam(m_fr, m_bw);

}

short
Filter::DoProcess(){   
  if(!m_error){                      
    if(m_input) { 
      double out = 0.;  
      for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){  
	if(m_enable){
	  out =
	    (m_a*(m_input->Output(m_vecpos)) + m_b1*m_delay[0] - m_b2*m_delay[1]);
    
	  m_delay[1] = m_delay [0]; // recirculate the delay line
	  m_delay[0] = out;
         
	  m_output[m_vecpos] = out;

	}
	else m_output[m_vecpos] = 0.f;
      }
      return 1;
    } else {
      m_error = 11;
      return 0;
    }
  } else return 0;
}




///////////// ERROR HANDLING //////////////////////////////////

char*
Filter::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 11:
    message = "DoProcess() failed. No input object.";
    break;

  default:
    message = SndObj::ErrorMessage();
    break;
  }

  return message;

}
