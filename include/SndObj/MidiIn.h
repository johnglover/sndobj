 
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
// MidiIn.h: interface of the MidiIn                /
//                class, SndObj MIDI input          /
//                                                  /
/***************************************************/

#ifndef _MIDIIN_H
#define _MIDIIN_H

#include "SndObj.h"
#include "SndMidiIn.h"


class MidiIn : public SndObj {

 protected:

  SndMidiIn* m_ioinput;
  short m_message;
  short m_channel;
  short m_readvel;  // if 1 MidiIn outputs the velocity byte
  short m_readaft;   // same, with afttouch
 public:

  void SetMessage(short message){ 

    if((message != VELOCITY_MESSAGE)  &&  (message != POLYAFTOUCH_MESSAGE)){
      m_readvel = m_readaft = 0;
      m_message = message;
      return;
    }
    else{
      if(message == VELOCITY_MESSAGE){
	m_readaft = 0;
	m_readvel = 1;
	m_message = NOTE_MESSAGE;
	return;
      }
      if(message == POLYAFTOUCH_MESSAGE) { 
	m_readaft = 1;
	m_readvel =  0;
	m_message = NOTE_MESSAGE;
	return;
      }
    }
  }


  void SetChannel(short channel){ m_channel = channel;}
  void SetMidiInput(SndMidiIn* input){ m_ioinput = input; }

  int Set(char* mess, float value);
  int Connect(char* mess, void* input);

  MidiIn();
  MidiIn(SndMidiIn* input, short message = NOTE_MESSAGE, short channel = 1,
	 int vecsize = DEF_VECSIZE, float sr = DEF_SR);
  ~MidiIn();

  short DoProcess();
  char* ErrorMessage();

};

#endif 

