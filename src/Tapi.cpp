 
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

#include "Tapi.h"

//////////CONSTRUCTION /////////////////////

Tapi::Tapi(){
  AddMsg("delay time modulation", 41);
}

Tapi::Tapi(SndObj* delayinput, DelayLine* DLine, int vecsize, float sr)
  : Tap(0.001f, DLine, vecsize, sr)
{

  m_delaytime = 0.f;
  m_input = delayinput;
  AddMsg("delay time modulation", 41);
}

Tapi::~Tapi()
{}


//////////////////OPERATIONS //////////////////////
int
Tapi::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 41:
    SetDelayInput((SndObj *) input);
    return 1;

  default:
    return Tap::Connect(mess,input);
     
  }

}
short
Tapi::DoProcess(){
  
  if(!m_error){   
    if(m_DLine && m_input){
      float pos;  
      for(m_vecpos=0;m_vecpos<m_vecsize;m_vecpos++){
	if(m_enable){	 
	  m_delaytime = m_input->Output(m_vecpos);
	  pos = m_DLine->GetWritePointerPos() - (m_delaytime*m_sr)
	        - m_vecsize + m_vecpos;
	  while(pos > m_size) pos -= m_size;
	  while(pos < 0) pos += m_size;
	  m_output[m_vecpos] = GetSample(pos);
	}
	else m_output[m_vecpos] = 0.f;
      }
      return 1;
    } 
    else {
      m_error = 1;
      return 0;
    }
  } else return 0;

}
