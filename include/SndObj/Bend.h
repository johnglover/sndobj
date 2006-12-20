// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

/***************************************************/
// Bend.cpp: implementation of the Bend class,      /
//           MIDI pitchbend input processing        /
//                                                  /
/***************************************************/

#ifndef _BEND_H
#define _BEND_H

#include "MidiIn.h"

class Bend : public MidiIn {

protected:

float m_bend;
float m_range;

public:

Bend();
Bend(SndObj* InObj, SndMidiIn* input, float range, short channel = 1, 
	 int vecsize=DEF_VECSIZE, float sr=DEF_SR);
~Bend();

void SetRange(float range){ m_range = range;}

int Set(char* mess, float value);

short DoProcess();

};

#endif


