// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//***********************************************************//
//  Allpass.cpp: Implementation of the Allpass Object        //
//                (Allpass filter)                           //
//                                                           //
//                                                           //
//***********************************************************//

#include "Allpass.h"

//////////CONSTRUCTION /////////////////////

   Allpass::Allpass(){}

   Allpass::Allpass(float gain, float delaytime, SndObj* InObj, 
	   int vecsize, float sr)
   : Comb(gain, delaytime, InObj, vecsize, sr)
   {}

   Allpass::~Allpass()
   {}

////////////////////OPERATIONS////////////////////

short
Allpass::DoProcess(){
if(!m_error){ 
 if(m_input){ 
  for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){
     if(m_enable){
            m_output[m_vecpos] = m_input->Output(m_vecpos)*(-m_gain) + GetSample();
            PutSample(m_input->Output(m_vecpos) + this->Output(m_vecpos)*m_gain);   
	 }
 else *m_output = 0.f;
  }
 return 1;
 }
else{
        m_error = 1;
        return 0;
    }
}
	else return 0;
}








