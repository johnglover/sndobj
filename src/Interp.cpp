//***********************************************************//
//  Interp.cpp : implementation of the Interp object
//            (interpolation object) 
//
//***********************************************************//
#include "Interp.h"

Interp::Interp(){
  m_initial = m_final = 0.f;
  m_count = m_dur = 0;
  m_typec = 0.f;
  AddMsg("initial", 21);
  AddMsg("final", 22);
  AddMsg("type", 23);
  AddMsg("duration", 24);


           }

Interp::Interp(float initial, float final,
			   float dur, float type, int vecsize, float sr):
           SndObj(0, vecsize, sr){
  
  m_count = 0;
  m_typec = type; 
  m_initial = initial;
  m_final = final;
  m_dur = (unsigned long) (dur*m_sr);
    AddMsg("initial", 21);
  AddMsg("final", 22);
  AddMsg("type", 23);
  AddMsg("duration", 24);
                           }

Interp::~Interp(){ 
}

int
Interp::Set(char* mess, float value){

	switch(FindMsg(mess)){

	case 21:
	SetCurve(value, m_final, m_typec);
	return 1;

	case 22:
	SetCurve(m_initial, value, m_typec);
	return 1;

	case 23:
	SetCurve(m_initial, m_final, value);
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
Interp::SetCurve(float initial, float final, 
                  float m_typec){
    m_initial = initial;
    m_final = final;
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
   if(m_count == m_dur) m_output[m_vecpos] = m_final;
    else {
     if(m_typec == 0.f){ // linear
     m_output[m_vecpos] = m_initial + ((m_final - m_initial)/m_dur)*m_count;                 
     }
     else {             // exponential
     m_output[m_vecpos] = m_initial + (m_final - m_initial)*(float) 
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

   


