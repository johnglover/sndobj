// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

/***************************************************/
// SndMidiIn.h: interface of the SndMidiIn          /
// (LINUX/CYGWIN/SGI) class, MIDI input             /
//                                                  /
/***************************************************/


#ifndef _SNDMIDIIN_H
#define _SNDMIDIIN_H



#include "SndMidi.h" 

#ifdef OSS

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#endif

class SndMidiIn : public SndMidi {

protected:

#ifdef SGI

void PutOutput(MDevent* cur);

#endif

#ifdef WIN

HMIDIIN m_handle;
MMRESULT m_result;

inline void PutOutput(MIDI_event*cur);

void WriteBuf(MIDI_event event);
MIDI_event ReadBuf();

private:

friend 
#ifdef VISUALC
static
#endif 
void  
#ifndef SWIGPYTHON
CALLBACK
#endif
midiInputHandler(HMIDIIN, UINT wMsg, DWORD dwInstance,
    DWORD dwParam1, DWORD dwParam2);

#endif 

public:

SndMidiIn();

#if defined (OSS) || defined (SGI)
SndMidiIn(char* port, int buffsize = 64);
#endif

#ifdef WIN
SndMidiIn(int port, int buffsize = 64);
#endif

~SndMidiIn();

short Read();


char* ErrorMessage();

};


#endif

