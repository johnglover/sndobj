 
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
// SndMidi.h: interface of the SndMidi              /
// (LINUX/CYGWIN/SGI)abstract class, MIDI IO        /
//                                                  /
/***************************************************/

#ifndef _SNDMIDI_H 
#define _SNDMIDI_H


#include "SndIO.h"

#if defined(OSS) || defined (SGI) 

#include <stropts.h>
#include <poll.h>

#ifndef SGI
#include <unistd.h>
#endif

#ifndef OSS
#include <dmedia/midi.h>
#endif

#endif // OSS SGI

#ifdef WIN

#include <windows.h>
#include <mmsystem.h>
void MidiDeviceList();
char* MidiInputDeviceName(int dev, char* name);

#endif

enum { NOTE_MESSAGE = -1, PBEND_MESSAGE,
       MOD_MESSAGE, BREATH_MESSAGE, FREE1, FOOT_MESSAGE,
       PORT_MESSAGE, VOL_MESSAGE, BAL_MESSAGE,
       FREE2, PAN_MESSAGE, EXPR_MESSAGE };
const int POLYAFTOUCH_MESSAGE = 129;
const int PROGRAM_MESSAGE = 130;
const int AFTOUCH_MESSAGE = 128;
const int VELOCITY_MESSAGE = 255;
const int NOTEOFF_MESSAGE = 256;
const int OUTOFRANGE = -128;

#ifdef OSS

typedef struct __mdevent{ // SGI's midi event struc, borrowed for compat
  unsigned char msg[4]; // message bytes
  char* sysexmsg;    // system excl (currently not supported)
  unsigned long long stamp; // time stamp (not used)
  int msglen;    // system excl msg length

} MDevent;

#endif

#ifdef WIN

typedef struct {
  unsigned char msg[4];
} MIDI_event;

typedef union {
  MIDI_event event;
  DWORD  dword;
} midi_msg;

#endif

class SndMidi : public SndIO {

 protected:

  short m_noteon;
  short m_noteoff;
  unsigned char *m_vel;
  unsigned char  *m_aft;
  short* m_message;
  unsigned char m_status;
  unsigned char m_type;
  unsigned char m_note;
  int m_read;
  int m_count;
  int m_buffsize;
  short m_chans; // channels in the range of 0-15
  short m_msgflag; // flag to check for new messages

#if defined(OSS) || defined(SGI) // OSS& SGI  MIDI 

  int    m_fd;
#ifndef SGI
  char*  m_port;  // midi device
#endif
#ifndef OSS
  MDport m_port;
#endif
  MDevent* m_event; 
  pollfd m_midifd;

#endif    // OSS & SGI MIDI

#ifdef WIN   // Windows MME MIDI

  MIDI_event*  m_event;
 
#endif // Windows MME MIDI

 public:
	
  short NoteOn();
  short NoteOff();
  char LastNote() { return m_note; }
  char  Velocity(char note){ 
    return m_vel[note];}
  char  LastNoteVelocity(){ return m_vel[m_note];}
  char  Aftertouch(char note) {  
    return m_aft[note];
  }
  char  LastNoteAftertouch(){ return m_aft[m_note];}
  short GetMessage(short channel) { if(channel > 0 && channel <= 16)
    return m_message[channel-1];
  else return OUTOFRANGE;}

  bool NewMessage(short channel){
    channel--;
    if((1<<channel) & m_msgflag){
      m_msgflag = m_msgflag ^ (1<<channel);
      return true;
    }
    else return false;
  }


  SndMidi(int buffsize, float sr=DEF_SR);
  ~SndMidi();
  char* ErrorMessage();

};


#endif
