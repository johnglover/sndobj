 
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


//************************************************************//
// Randh.cpp : implementation of the Randh class              //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Randh.h"


Randh::Randh(){
  m_inputfr = 0;
  m_period = 1;
  m_count = 1;
  AddMsg("frequency", 31);

}

Randh::Randh(float fr,float amp, SndObj* InFrObj, 
	     SndObj* InAmpObj, int vecsize, float sr)
  : Rand(amp, InAmpObj, vecsize, sr)
{
  m_fr = fr;              
  m_period = (long) (m_fr > 0.1 ? m_sr/m_fr : m_sr/.1);
  m_count = m_period;
  m_inputfr = InFrObj;
  AddMsg("frequency", 31);

     
}

Randh ::~Randh(){

}


/////////////// OPERATIONS //////////////////////////////////////
void
Randh::SetSr(float sr){
  m_sr = sr;
  m_period = (long) (m_fr > 0.1 ? m_sr/m_fr : sr/.1); 
  m_count = m_period;
}


int 
Randh::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 31:
    SetFreq(value);
    return 1;

  case 1:
    SetSr(value);
    return 1;

  default:
    return Rand::Set(mess,value);
     
  }


}


int 
Randh::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 31:
    m_inputfr = (SndObj *) input;
    return 1;

  default:
    return Rand::Connect(mess,input);
     
  }


}

short
Randh::DoProcess(){  
 
  if(!m_error){
    long oldper; 
    float freq, amp;  
    for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){	     
      if(m_enable){
	oldper = m_period;
	freq = m_fr + (m_inputfr == 0 ? 0 : m_inputfr->Output(m_vecpos));
	amp = m_amp + (m_input== 0 ? 0 : m_input->Output(m_vecpos));
	m_period = (long) ( freq > .1 ? m_sr/freq : m_sr/.1 );   
	if((m_count-1) > 0 ) {
	  m_count = (m_count--)+(m_period - oldper);
	  m_output[m_vecpos] = Output(m_vecpos-1); 
	}
	else{
	  m_output[m_vecpos] = amp*((rand()-MAXR)/MAXR);
          m_count = m_period;
	}
      }
      else m_output[m_vecsize] = 0.f ;
    }

    return 1;
  }

  else return 0;

}





