// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//////////////////////////////////////////////////
// Lowpass resonant filter implementation     
// VL, 2002
//
//////////////////////////////////////////////////

#include "Lp.h"

Lp::Lp(){
}

Lp::Lp(float fr, float bw, SndObj* inObj, SndObj* inputfreq, 
      SndObj* inputBW, int vecsize, float sr):
Reson(fr, bw, inObj, inputfreq, inputBW, vecsize, sr){
}

Lp::~Lp(){
}

int 
Lp::Set(char* mess, float value){

	switch (FindMsg(mess)){

    case 23:
	SetSr(value);
	return 1;

	default:
    return Filter::Set(mess,value);
     
	}

}

short
Lp::DoProcess(){
if(!m_error){                       
 if(m_input) { 

   float out = 0.f;
   float fr, bw;
   for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){  

   if(m_enable){
   fr = m_fr + (m_inputfr == 0 ? 0 : m_inputfr->Output(m_vecpos));
   bw = m_bw + (m_inputbw == 0 ? 0 : m_inputbw->Output(m_vecpos));
  
   SetLPparam(fr, bw);
 
   out = (float) 
   ((m_input->Output(m_vecpos) + (m_b1 + 2*m_b2)*m_delay[0] 
              - m_b2*m_delay[1])/m_a);
    
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


