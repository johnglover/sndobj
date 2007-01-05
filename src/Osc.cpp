// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "Osc.h"

Osc::Osc(){
  m_inputamp = m_inputfr = 0;
}

Osc::Osc(Table* table, float fr, float amp, 
	 SndObj* inputfr, SndObj* inputamp,
	 int vecsize, float sr) 
  : FastOsc(table, fr, amp,vecsize, sr){

  m_inputamp = inputamp;
  m_inputfr = inputfr;

}

Osc::~Osc(){
}

int
Osc::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    SetFreq((SndObj*) input);
    return 1;

  case 22:
    SetAmp((SndObj*) input);
    return 1;

  default:
    return FastOsc::Connect(mess,input);
     
  }


}

short
Osc::DoProcess(){

  if(!m_error){
    if(!m_ptable){ 
      m_error = 1; // empty table object
      return 0;
    }
    long incr;
    float amp, fr;
    long ph = m_phase;
    float *tab = m_ptable->GetTable();  
    // wrapping loop
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
   
	fr = m_fr + (m_inputfr == 0 ? 0 : m_input->Output(m_vecpos));
	amp = m_amp + (m_inputamp == 0 ? 0 : m_inputamp->Output(m_vecpos));

	m_output[m_vecpos] = amp*tab[ph>>m_lobits] ;	
	incr = (long)(fr * m_factor);   
	ph += incr;
	ph &= phasemask;

      } 
      else { // if disabled
	m_output[m_vecpos] = 0.f;
      }

    }  // end wrapping loop 
    m_phase = ph;

    return 1;
  }
  else return 0;
}
