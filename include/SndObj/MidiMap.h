// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

/***************************************************/
// MidiMap.h: interface of the MidiMap                /
//                class, SndObj MIDI input          /
//                                                  /
/***************************************************/

#ifndef _MIDIMAP_H
#define _MIDIMAP_H

#include "MidiIn.h"
#include  "Table.h"

class MidiMap : public MidiIn {

               protected:
Table*  m_maptable;
float m_min;
float m_max;
float* m_map;
	       
void MapReset() {
	if(m_map) {
		for(int i =0; i < 128; i++)
			m_map[i] = ((m_max-m_min)/127)*i + m_min;
	}
}
			   public:

void SetTable(Table* maptable){ m_maptable =  maptable;}
void SetRange(float min, float max){ m_min = min; 
                                     m_max = max;
									 m_maptable = 0;
                                     MapReset();
									}
int Set(char* mess, float value);
int Connect(char* mess, void* input);

MidiMap();
MidiMap(SndMidiIn* input, Table* maptable,
 short message = NOTE_MESSAGE, short channel = 1,
 int vecsize = DEF_VECSIZE, float sr = DEF_SR);
MidiMap(SndMidiIn* input, float min, float max, 
		short message = NOTE_MESSAGE, short channel = 1, 
		int vecsize = DEF_VECSIZE, float sr = DEF_SR);

~MidiMap();
short DoProcess();
char* ErrorMessage();
};

#endif 

