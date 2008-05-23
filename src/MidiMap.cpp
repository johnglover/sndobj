 
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
// MidiMap.cpp: implementation of the MidiMap         /
//                class, SndObj MIDI input          /
//                                                  /
/***************************************************/

#include "MidiMap.h"
#include <stdio.h>

MidiMap::MidiMap(){

  m_maptable = 0;
  m_min = 0.f;
  m_max = 0.f;
  if(!(m_map = new float[128])){
    m_error = 31;
  }
  AddMsg("range min", 31);
  AddMsg("range max", 32);
  AddMsg("map table", 33);
  MapReset();

}

MidiMap::MidiMap(SndMidiIn* input, Table* maptable,
		 short message, short channel,
		 int vecsize, float sr): MidiIn (input, message, channel,
						 vecsize, sr){
  m_maptable = maptable;
  m_min = 0.f; m_max = 0.f;
  m_map = 0;
  AddMsg("range min", 31);
  AddMsg("range max", 32);
  AddMsg("map table", 33);
}

MidiMap::MidiMap(SndMidiIn* input, float max, float min,
		 short message, short channel,
		 int vecsize, float sr): MidiIn (input, message, channel,
						 vecsize, sr){
  m_max = max;
  m_min = min;
  if(!(m_map = new float[128])){
    m_error = 31;
  }
  MapReset();
  m_maptable = 0;
  AddMsg("range min", 31);
  AddMsg("range max", 32);
}

MidiMap::~MidiMap(){
  delete[] m_map;
}

int
MidiMap::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 31:
    SetRange(value, m_max);
    return 1;

  case 32:
    SetRange(m_min, value);
    return 1;

  default:
    return MidiIn::Set(mess,value);
     
  }
}

int
MidiMap::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 33:
    m_maptable = (Table *) input;
    return 1;

  default:
    return MidiIn::Connect(mess,input);
     
  }
}


short
MidiMap::DoProcess(){
  if(!m_error) { 
    if(m_ioinput){   
      if(m_ioinput->NewMessage(m_channel+1) && 
	 (m_message == m_ioinput->GetMessage(m_channel+1))){
	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){   
	  if(m_enable){
	    if(!m_readvel  &&  !m_readaft){
	      if(m_maptable)
		m_output[m_vecpos] = m_maptable->GetTable()[Ftoi(m_ioinput->Output(m_channel))];
	      else
		m_output[m_vecpos] = m_map[Ftoi(m_ioinput->Output(m_channel))];
	    }
	    else {
	      if(m_readvel){
		if(m_maptable)
		  m_output[m_vecpos] = m_maptable->GetTable()[Ftoi((float)m_ioinput->LastNoteVelocity())];
		else	   
		  m_output[m_vecpos] = m_map[Ftoi((float)m_ioinput->LastNoteVelocity())];

	      }
	      if(m_readaft){
		if(m_maptable)
		  m_output[m_vecpos] = m_maptable->GetTable()[Ftoi((float)m_ioinput->LastNoteAftertouch())];
		else	   
		  m_output[m_vecpos] = m_map[Ftoi((float)m_ioinput->LastNoteAftertouch())];
	      }
	    }
	  } else m_output[m_vecpos] = 0.f;
	}
	return 1; 
      } else return 1;
    }  
    else{
      m_error = 11; 
      return 0;
    }
  }
  else return 0;
}

char*
MidiMap::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 31:
    message = "Error allocating map table";
    break;

  default:
    message = MidiIn::ErrorMessage();
    break;
  }

  return message;

}
