 
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
// SndMidiIn.cpp: implementation of the SndMidiIn   / 
//                class, MIDI input                 //
//***************************************************/
#if defined (SGI) || defined (OSS) || defined (WIN)

#include "SndMidiIn.h"

SndMidiIn::SndMidiIn():SndMidi(64, 44100.f){

#ifdef OSS
m_port = "/dev/midi";
if(!(m_fd = open(m_port, O_RDONLY)))
m_error = 11; 
else m_error = 0;
#endif 

#ifdef SGI
mdInit();
if(!(m_port = mdOpenInPort("Serial Port 2")))
m_error = 11; 
else m_error = 0;
#endif

#ifdef WIN
if((m_result = midiInOpen(&m_handle, 0, (DWORD) midiInputHandler, 
   (DWORD) this,  CALLBACK_FUNCTION)) != MMSYSERR_NOERROR)
m_error = 11; 
else m_error = 0;
#endif

#ifdef WIN
if(midiInStart(m_handle) != MMSYSERR_NOERROR)
m_error = 12;
#endif

#ifdef SGI
if(!(m_fd = mdGetFd(m_port)))
m_error = 12;
else m_error = 0;
#endif

#if defined(SGI) || defined(OSS)
m_midifd.events = POLLIN;
m_midifd.fd = m_fd;
#endif

m_msgflag = 0;
}

#if defined(SGI) || defined(OSS)
SndMidiIn::SndMidiIn(char* port, int buffsize):SndMidi(buffsize, 44100.f){
#endif
#ifdef WIN
	SndMidiIn::SndMidiIn(int port, int buffsize):SndMidi(buffsize, 44100.f){
#endif

#ifdef OSS
m_port = port;
if(!(m_fd = open(m_port, O_RDONLY)))
m_error = 11; 
else m_error = 0;
#endif 

#ifdef SGI
mdInit();
if(!(m_port = mdOpenInPort(port)))
m_error = 11; 
else m_error = 0;
#endif

#ifdef WIN
if((m_result = midiInOpen(&m_handle, port, (DWORD) midiInputHandler, 
   (DWORD) this,  CALLBACK_FUNCTION)) != MMSYSERR_NOERROR)
m_error = 11; 
else m_error = 0;
#endif

#ifdef WIN
if(midiInStart(m_handle) != MMSYSERR_NOERROR)
m_error = 12;
#endif

#ifdef SGI
if(!(m_fd = mdGetFd(m_port)))
m_error = 12;
else m_error = 0;
#endif

#if defined(SGI) || defined(OSS)
m_midifd.events = POLLIN;
m_midifd.fd = m_fd;
#endif

m_msgflag = 0;
}


SndMidiIn::~SndMidiIn(){

#ifdef SGI
mdClosePort(m_port);
#endif

#ifdef OSS
close(m_fd);
#endif

#ifdef WIN
midiInStop(m_handle);
midiInClose(m_handle);
#endif

}

#if defined(WIN) || defined(SGI)
void inline 
#ifndef SGI
SndMidiIn::PutOutput(MIDI_event* cur){
#endif
#ifndef WIN
SndMidiIn::PutOutput(MDevent* cur){
#endif

m_status = cur->msg[0];
m_chans = m_status & 15;
m_type = m_status >> 4;
m_msgflag = (1<<m_chans) | m_msgflag;


switch (m_type){

case 8: // Note OFF
m_message[m_chans] = NOTEOFF_MESSAGE;
m_noteoff = 1;
m_vel[cur->msg[1]] = 0;
m_note  = cur->msg[1];
m_output[m_chans] = (float) m_note;

break;

case 9: // Note ON
if((m_vel[cur->msg[1]] = cur->msg[2]) > 0){ 
m_message[m_chans] = NOTE_MESSAGE;
m_noteon = 1;

}
else{
m_message[m_chans] = NOTEOFF_MESSAGE;
m_noteoff = 1;
}
m_note = cur->msg[1];
m_output[m_chans] = (float) m_note;
break;

case 10: // Aftertouch (POLY),  
m_message[m_chans] = POLYAFTOUCH_MESSAGE;
m_aft[cur->msg[1]] = cur->msg[2];
m_output[m_chans] = (float) cur->msg[2];
break;

case 11: // Control change
m_message[m_chans] = cur->msg[1];
m_output[m_chans] = (float) cur->msg[2];
break;


case 12:  // Program change
m_message[m_chans] = PROGRAM_MESSAGE;
m_output[m_chans] = (float) cur->msg[1];
break;

case 13: // Aftertouch (MONO)
m_message[m_chans] = AFTOUCH_MESSAGE;
m_output[m_chans] = (float) cur->msg[1];
break;

case  14:  // Pitch bend, seems to be byte-reversed...
m_message[m_chans] = 0;
m_output[m_chans] = (float) cur->msg[2];
m_output[m_chans] += (float)cur->msg[1]*.0078125f;
break;

default:
break;
}
}
#endif

short
SndMidiIn::Read(){

if(!m_error){

#ifdef WIN

if(m_error == MMSYSERR_NOERROR){
if(m_count == m_read) 
  return 0;
else {
MIDI_event temp = ReadBuf();
PutOutput(&temp);
return 1;
}
}
else return 0;
#endif

#ifdef SGI
if(m_count == m_read){   // if all items are sent, poll input
    if( poll(&m_midifd, 1, 0)){
m_read = mdReceive(m_port, m_event, m_buffsize);
m_count = 0;     
PutOutput(&m_event[m_count]);
          }              
    else return 0;
}
else
PutOutput(&m_event[m_count]);
m_count++;
return m_read;
#endif

#ifdef OSS
unsigned char temp[2];
if(poll(&m_midifd, 1, 0)){

read(m_fd, temp, 1);
m_event->msg[0] = temp[0];
m_status = m_event->msg[0];
m_chans = m_status & 15;
m_type = m_status >> 4;
m_msgflag = (1<<m_chans) | m_msgflag;

switch (m_type){

case 8: // Note OFF
read(m_fd, temp, 1);
m_event->msg[1] = temp[0];
read(m_fd, temp, 1);
 m_event->msg[2] = temp[0];
m_message[m_chans] = NOTEOFF_MESSAGE;
m_noteoff = 1;
m_vel[m_event->msg[1]] = 0;
m_output[m_chans] = m_note = m_event->msg[1];
break;

case 9: // Note ON
read(m_fd, temp, 1);
m_event->msg[1] = temp[0];
read(m_fd, temp, 1);
m_event->msg[2] = temp[0];
m_vel[m_event->msg[1]] = m_event->msg[2];
if(m_event->msg[2] > 0){ 
m_message[m_chans] = NOTE_MESSAGE;
m_noteon = 1;
}
else{
m_message[m_chans] = NOTEOFF_MESSAGE;
m_noteoff = 1;
}
m_output[m_chans] = m_note = m_event->msg[1];
break;

case 10: // Aftertouch (POLY)
read(m_fd, temp, 1);
m_event->msg[1] = temp[0];
read(m_fd, temp, 1);
m_event->msg[2] = temp[0];
m_vel[m_event->msg[1]] = m_event->msg[2];
m_message[m_chans] = POLYAFTOUCH_MESSAGE;
m_aft[m_event->msg[1]] = m_event->msg[2];
m_output[m_chans] = (float) m_event->msg[2];
break;

case 11: // Control change
read(m_fd, temp, 1);
m_event->msg[1] = temp[0];
read(m_fd, temp, 1);
m_event->msg[2] = temp[0];
m_vel[m_event->msg[1]] = m_event->msg[2];
m_message[m_chans] = m_event->msg[1];
m_output[m_chans] = (float) m_event->msg[2];
break;

case 12:  // Program change
read(m_fd, temp, 1);
m_event->msg[1] = temp[0];
m_message[m_chans] = PROGRAM_MESSAGE;
m_output[m_chans] = (float) m_event->msg[1];
break;

case 13: // Aftertouch (MONO)
read(m_fd, temp, 1);
m_event->msg[1] = temp[0];
m_message[m_chans] = AFTOUCH_MESSAGE;
m_output[m_chans] = (float) m_event->msg[1];
break;

case  14:  // Pitch bend, seems to be byte-reversed...
read(m_fd, temp, 1);
m_event->msg[1] = temp[0];
read(m_fd, temp, 1);
m_event->msg[2] = temp[0];
m_vel[m_event->msg[1]] = m_event->msg[2];
m_message[m_chans] = 0;
m_output[m_chans] = (float)m_event->msg[2];
m_output[m_chans] += (float)m_event->msg[1]*.0078125;
break;

default:
break;
} // endswitch
  
} // endif
 
return 1;
#endif

}
else return 0;
}

#ifdef WIN
void
#ifdef VISUALC
static
#endif
CALLBACK midiInputHandler(HMIDIIN hmin, UINT wMsg, 
         DWORD dwInstance, DWORD dwParam1, DWORD dwParam2){

midi_msg msg;
SndMidiIn* midi;
midi = (SndMidiIn *) dwInstance;
switch (wMsg)
{
case MIM_DATA:
msg.dword = dwParam1;
midi->WriteBuf(msg.event);
break;
default:
break;
}	
}

MIDI_event
SndMidiIn::ReadBuf(){
MIDI_event cur = m_event[m_read];
m_read++;
m_read %= m_buffsize;
return cur;

}
void
SndMidiIn::WriteBuf(MIDI_event event){

m_event[m_count] = event;
m_count++;
m_count %= m_buffsize;

}
#endif

char*
SndMidiIn::ErrorMessage(){

char* message;
  switch(m_error){

  case 21:
#ifdef SGI
  message = "mdOpenInPort() failed.";
#endif
#ifdef OSS
  message = "open() failed.";
#endif
#ifdef WIN
	switch(m_result){
	case MMSYSERR_ALLOCATED:
	message = "The specified resource is already allocated.";
	break;
	case MMSYSERR_BADDEVICEID:
	message = "The specified device identifier is out of range.";
	break;
	case MMSYSERR_INVALFLAG:
	message = "The flags specified by dwFlags are invalid.";
	break;
	case MMSYSERR_INVALPARAM:
	message = "The specified pointer or structure is invalid. ";
	break;

	case MMSYSERR_NOMEM:
	message = "The system is unable to allocate or lock memory. ";
        break;
	default:
	message = "Undefined Midi Input Open error.";
	break;
	}
#endif
	break;

  case 22:
#ifdef WIN
  message =  "midiInStart() failed.";
#endif
#ifdef SGI
  message =  "mdGetFd() failed.";
#endif
  break;
  default:
	  message = SndMidi::ErrorMessage();
  break;

  }

return message;

}

#endif
