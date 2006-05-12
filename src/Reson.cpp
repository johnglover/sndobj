// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Reson.cpp : implementation of the Reson class             //
//               (2nd order band-pass filter).                //
//                                                            //
//                                                            //
//************************************************************//



#include "Reson.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

Reson::Reson(){
m_inputfr=m_inputbw=0;
                 }

Reson::Reson(float fr, float bw, SndObj* inObj,  SndObj* inputfreq, 
			 SndObj* inputbw, int vecsize, float sr) : Filter (fr, bw, inObj,
			 vecsize, sr){


m_inputbw = inputbw;
m_inputfr = inputfreq; 

}

Reson::~Reson(){

}

///////////// OPERATIONS /////////////////////////////////////////
void
Reson::SetFreq(float fr, SndObj* InFrObj){

       m_fr = fr;
       m_inputfr = InFrObj;      

}


void
Reson::SetBW(float bw, SndObj* InBWObj){
      
       m_bw = bw;
       m_inputbw = InBWObj;      
      
}

int
Reson::Connect(char* mess, void* input){

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


short
Reson::DoProcess(){  
                          
if(!m_error){                       
 if(m_input) { 
   double out = 0.;
   float fr, bw;
   for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){  

   if(m_enable){
   fr = m_fr + (m_inputfr == 0 ? 0 : m_inputfr->Output(m_vecpos));
   bw = m_bw + (m_inputbw== 0 ? 0 : m_inputbw->Output(m_vecpos));
  
   SetParam(fr, bw);
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


