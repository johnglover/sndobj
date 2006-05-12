// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//***********************************************************//
//  Comb.cpp: Implementation of the Comb Object              //
//                (comb filter)                              //
//                                                           //
//                                                           //
//***********************************************************//

#include "Comb.h"

//////////CONSTRUCTION /////////////////////

Comb::Comb(){
m_gain = 0.f;
AddMsg("gain", 31);
}

Comb::Comb(float gain, float delaytime, SndObj* InObj, 
	   int vecsize, float sr)
   : DelayLine(delaytime, InObj, vecsize, sr)
{
m_gain = gain;
AddMsg("gain", 31);
}

Comb::~Comb()
{
}

////////////////////OPERATIONS////////////////////

int
Comb::Set(char* mess, float value){

	switch (FindMsg(mess)){

	case 31:
    SetGain(value);
	return 1;

	default:
    return DelayLine::Set(mess,value);
     
	}


}

void 
Comb::SetGain(float gain){
m_gain = gain;
}

short
Comb::DoProcess(){
	if(!m_error){ 
if(m_input){ 
	for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){
  if(m_enable){
   m_output[m_vecpos] = GetSample();
   PutSample(m_input->Output(m_vecpos) + m_output[m_vecpos]*m_gain);       
       }
 else *m_output = 0.f;
	}
 return 1;
  }
else {
        m_error = 1;
        return 0;
    }
	}
	else return 0;
}









