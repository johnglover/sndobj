 
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
// MidiIn.cpp: implementation of the MidiIn         /
//                class, SndObj MIDI input          /
//                                                  /
/***************************************************/

#include "MidiIn.h"
#include <stdio.h>

MidiIn::MidiIn(){


  m_ioinput = 0;
  m_message = NOTE_MESSAGE;
  m_channel = 0;
  m_readvel = 0;

  AddMsg("message type", 21);
  AddMsg("channel", 22);
  AddMsg("midi input", 23);

}

MidiIn::MidiIn(SndMidiIn* input, short message, short channel,
	       int vecsize, float sr): SndObj (0, vecsize, sr){


  m_ioinput = input;
  if((message != VELOCITY_MESSAGE)  &&  (message != POLYAFTOUCH_MESSAGE)){
    m_readvel = m_readaft = 0;
    m_message = message;
         
  }
  else{
    if(message == VELOCITY_MESSAGE){
      m_readaft = 0;
      m_readvel = 1;
      m_message = NOTE_MESSAGE;
    }
    if(message == POLYAFTOUCH_MESSAGE) { 
      m_readaft = 1;
      m_readvel =  0;
      m_message = NOTE_MESSAGE;
    }
  }

  m_channel = channel-1;

  AddMsg("message type", 21);
  AddMsg("channel", 22);
  AddMsg("midi input", 23);
}


MidiIn::~MidiIn(){
}


int
MidiIn::Set(char* mess, float value){

  switch(FindMsg(mess)){

  case 21:
    SetMessage((short) value);
    return 1;

  case 22:
    SetChannel((short) value);
    return 1;

  default:
    return SndObj::Set(mess, value);

  }

}

int
MidiIn::Connect(char* mess, void* input){

  switch(FindMsg(mess)){

  case 23:
    m_ioinput = (SndMidiIn *) input;
    return 1;

  default:
    return SndObj::Connect(mess, input);

  }

}

short
MidiIn::DoProcess(){
  if(!m_error) { 
    if(m_ioinput){   
      if(m_message == m_ioinput->GetMessage(m_channel+1)){
	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){   
	  if(m_enable){
	    if(!m_readvel  &&  !m_readaft)
	      m_output[m_vecpos] = m_ioinput->Output(m_channel);		
	    else {
	      if(m_readvel)m_output[m_vecpos] = m_ioinput->LastNoteVelocity();
	      if(m_readaft)m_output[m_vecpos] = m_ioinput->LastNoteAftertouch();
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
MidiIn::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
    message = "No error.";
    break; 

  case 11:
    message = "DoProcess() failed. No input object(s).";
    break;

  default:
    message = "Undefined error";
    break;
  }

  return message;

}
