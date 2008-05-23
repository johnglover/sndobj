 
////////////////////////////////////////////////////////////////////////
// This file is part of the SndObj library
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
//
// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "Ap.h"

Ap::Ap(){

  m_inputfr = 0;
  m_inputR = 0;    
  SetAPParams(m_fr, m_bw);
  AddMsg("pole frequency", 31);
  AddMsg("pole radius", 32);


}

Ap::Ap(float fr, float R, SndObj* input,  
       SndObj* inputfreq, 
       SndObj* inputR, int vecsize, float sr):
  TpTz(0.,0.,0., 0., 0., input, vecsize, sr){
  m_fr = fr;
  m_bw = R;
  m_inputfr = inputfreq;
  m_inputR = inputR;
  SetAPParams(fr, R);

  AddMsg("pole frequency", 31);
  AddMsg("pole radius", 32);


}

Ap::~Ap(){ }


int
Ap::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 31:
    SetFreq(value,0);
    return 1;

  case 32:
    SetR(value);
    return 1;

  case 1:
    SetSr(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }

}

int
Ap::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 31:
    m_inputfr = (SndObj *) input;
    return 1;

  case 32:
    m_inputR = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }

}


void 
Ap::SetFreq(float fr, SndObj* inputfreq){

  if(!(m_inputfr = inputfreq))
    SetAPParams(fr, m_bw);
  m_fr = fr;

}

void 
Ap::SetR(float r, SndObj* inputR){

  if(!(m_inputR = inputR))
    SetAPParams(m_fr, r);

  m_bw = r;
}


short
Ap::DoProcess(){

  if(!m_error){
    if(m_input){
	 
      double out = 0., w = 0.;
      float fr, R;

      for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){  

	if(m_enable){
   
	  if(m_inputfr || m_inputR){
	    fr = m_fr + (m_inputfr == 0 ? 0 : m_inputfr->Output(m_vecpos));
	    R = m_bw + (m_inputR== 0 ? 0 : m_inputR->Output(m_vecpos));

	    // set params              
	    SetAPParams(fr, R);

	  }

	  // filtering 
    
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
      m_error = 3;
      return 0;
    }
  }
  else return 0;
}

char*
Ap::ErrorMessage(){
 
  char* message;
   
  switch(m_error){

    // handle your error codes here
  case 21:
    message = "Memory allocation error\n";
    break;

  default:
    message = Filter::ErrorMessage();
    break;
  
  }

  return message;

}

