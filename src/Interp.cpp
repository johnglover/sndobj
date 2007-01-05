//***********************************************************//
//  Interp.cpp : implementation of the Interp object
//            (interpolation object) 
//
//***********************************************************//
#include "Interp.h"

Interp::Interp(){
  m_initial = m_fin = 0.f;
  m_count = m_dur = 0;
  m_typec = 0.f;
  AddMsg("initial", 21);
  AddMsg("fin", 22);
  AddMsg("type", 23);
  AddMsg("duration", 24);


}

Interp::Interp(float initial, float fin,
	       float dur, float type, int vecsize, float sr):
  SndObj(0, vecsize, sr){
  
  m_count = 0;
  m_typec = type; 
  m_initial = initial;
  m_fin = fin;
  m_dur = (unsigned long) (dur*m_sr);
  AddMsg("initial", 21);
  AddMsg("fin", 22);
  AddMsg("type", 23);
  AddMsg("duration", 24);
}

Interp::~Interp(){ 
}

int
Interp::Set(char* mess, float value){

  switch(FindMsg(mess)){

  case 21:
    SetCurve(value, m_fin, m_typec);
    return 1;

  case 22:
    SetCurve(m_initial, value, m_typec);
    return 1;

  case 23:
    SetCurve(m_initial, m_fin, value);
    return 1;

  case 24:
    SetDur(value);
    return 1;

  case 1:
    SetSr(value);
    return 1;

  default:
    return SndObj::Set(mess, value);

  }

}


void
Interp::SetCurve(float initial, float fin, 
		 float m_typec){
  m_initial = initial;
  m_fin = fin;
  m_typec = 0.f;
  m_count = 0;
}

void
Interp::SetSr(float sr){
  m_dur = (unsigned long)((sr/m_sr)*m_dur);
  m_sr = sr;
}



short
Interp::DoProcess(){

  if(!m_error){
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){ 
	if(m_count == m_dur) m_output[m_vecpos] = m_fin;
	else {
	  if(m_typec == 0.f){ // linear
	    m_output[m_vecpos] = m_initial + ((m_fin - m_initial)/m_dur)*m_count;                 
	  }
	  else {             // exponential
	    m_output[m_vecpos] = m_initial + (m_fin - m_initial)*(float) 
	      ((1.f - exp(((double)m_count/m_dur)*m_typec))/
	       (1.f - exp((double)m_typec)));
	  }
	  m_count++;
	}
      }
      else m_output[m_vecpos] = 0.f;
    }
    return 1;
  } else return 0;
}

   


