// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ButtBP.cpp : implementation of the ButtBP class           //
//               (2nd order band-pass filter).                //
//                                                            //
//                                                            //
//************************************************************//

#include "ButtBP.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////
ButtBP::ButtBP(){
m_inputbw = 0;
m_inputfr = 0; 
m_type = 1;
SetParam(m_fr, m_bw, m_type);

                 }

ButtBP::ButtBP(float fr, float bw, SndObj* inObj,  SndObj* inputfreq, 
			   SndObj* inputbw, int vecsize, float sr) 
			   : TpTz (0., 0., 0., 0., 0., inObj, vecsize, sr){
m_fr = fr;
m_bw = bw;
m_inputbw = inputbw;
m_inputfr = inputfreq; 
m_type = 1;
SetParam(m_fr, m_bw, 1);

}

ButtBP::~ButtBP(){

}

///////////// OPERATIONS /////////////////////////////////////////
int
ButtBP::Set(char* mess, float value){

	switch (FindMsg(mess)){

	case 21:
    SetFreq(value);
	return 1;

	case 22:
	SetBW(value);
    return 1;

    case 23:
	SetSr(value);
	return 1;

	default:
    return SndObj::Set(mess,value);
     
	}

}

int
ButtBP::Connect(char* mess, void* input){

	switch (FindMsg(mess)){

	case 21:
    m_inputfr = (SndObj *) input;
	return 1;

	case 22:
	m_inputbw = (SndObj *) input;
    return 1;

	default:
    return SndObj::Connect(mess,input);
     
	}

}

void 
ButtBP::SetFreq(float fr, SndObj* InFrObj){

       m_fr = fr;
       if(!(m_inputfr = InFrObj)) SetParam(m_fr, m_bw, m_type);
}


void
ButtBP::SetBW(float bw, SndObj* InBWObj){
      
       m_bw = bw;
       if(!(m_inputbw = InBWObj)) SetParam(m_fr, m_bw, m_type);
      
}



short
ButtBP::DoProcess(){   

if(!m_error){                       
 if(m_input) { 
   double out = 0. ,w = 0.;
   float fr, bw;
   for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){  

   if(m_enable){
   
   if(m_inputfr || m_inputbw){
   fr = m_fr + (m_inputfr == 0 ? 0 : m_inputfr->Output(m_vecpos));
   bw = m_bw + (m_inputbw== 0 ? 0 : m_inputbw->Output(m_vecpos));

      // set params              
   SetParam(fr,bw,m_type);

	   }

    // filtering 
    //
    w = m_a*(m_input->Output(m_vecpos)) - m_b1*m_delay[0] - m_b2*m_delay[1];
    out = w + m_a1*m_delay[0] + m_a2*m_delay[1];

	m_delay[1] = m_delay [0];    
    m_delay[0] = w;

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

  
   
