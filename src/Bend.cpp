 
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

/***************************************************/
// Bend.cpp: implementation of the Bend class,      /
//           MIDI pitchbend input processing        /
//                                                  /
/***************************************************/

#include "Bend.h"

Bend::Bend(){
  m_message = 0;
  m_bend = 0;
  m_range = 0;
  AddMsg("range", 31);
}

Bend::Bend(SndObj* InObj, SndMidiIn* input, 
	   float range, short channel, int vecsize, float sr) 
  : MidiIn (input, 0, channel, vecsize, sr)
{

  m_input = InObj;
  m_range = range;
  m_bend = 0;
  AddMsg("range", 31);
}

Bend::~Bend(){
}


int
Bend::Set(char* mess, float value){

  switch(FindMsg(mess)){
    
  case 31:
    SetRange(value);
    return 1;

  default:
    return MidiIn::Set(mess, value);


  }

}

short
Bend::DoProcess(){
  if(!m_error) { 
    if(m_ioinput && m_input){   
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){   
	if(m_enable){
	  if(m_message == m_ioinput->GetMessage(m_channel+1)) 
	    m_bend = m_input->Output(m_vecpos)*(
						((m_ioinput->Output(m_channel) - 64.f)*(m_range/100))/ 64.f);
	  m_output[m_vecpos]  = m_input->Output(m_vecpos) + m_bend;
	} else m_output[m_vecpos] = 0.f;
      }
      return 1; 
    }  
    else{
      m_error = 11; 
      return 0;
    }
  }
  else return 0;
}



