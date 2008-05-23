 
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

#include "Phase.h"

Phase::Phase(){
  m_freq = m_offset = 0.f;
  AddMsg("frequency", 21);
  AddMsg("phase", 22);
}


Phase::Phase(float freq, 
	     SndObj* FreqInput, float offset, int vecsize, float sr):
  SndObj(FreqInput, vecsize, sr)
{
  m_freq = freq;
  m_offset = offset;
  AddMsg("frequency", 21);
  AddMsg("phase", 22);
}

Phase:: ~Phase(){
}


int 
Phase::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetFreq(value);
    return 1;

  case 22:
    SetPhase(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}

int
Phase::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    m_input = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }

}

short
Phase::DoProcess(){

  if(!m_error){
    float s;
    float freq;
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){ 
	freq = m_freq + (m_input == 0 ? 0 : m_input->Output(m_vecpos));
	s = m_offset + freq/m_sr; 
	while(s > 1) s -= 1.;
	while(s < 0) s += 1.;
	m_output[m_vecpos] = m_offset = s;
      }
      else m_output[m_vecpos] =  0.f;
    }
    return 1;
  }
  else return 0;
}
