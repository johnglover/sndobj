////////////////////////////////////////////////////////
// SndCoreAudio.h: Interface of the SndCoreAudio class
//       realtime audio IO with Mac OSX Core Audio 
//
//

#ifdef MACOSX

#ifndef SndCoreAudio_H_
#define SndCoreAudio_H_

#include <CoreAudio.h>
#include "SndIO.h"

const int DEV_DEFAULT = 0xFFFFFFFF;

class SndCoreAudio : public SndIO {

AudioDeviceID m_dev;

float** m_inbuffs;
float** m_outbuffs;

AudioStreamBasicDescription m_format;
unsigned int m_bufframes;
unsigned int m_buffsize;
unsigned int m_buffitems;
unsigned int m_buffnos;
unsigned int m_outcurbuff;
unsigned int m_incurbuff;
unsigned int m_iocurbuff;
unsigned int m_outcount;
unsigned int m_incount;
bool* m_inused;
bool* m_outused;
float m_norm;

public:

SndCoreAudio(int channels=2,int bufframes=512, int buffnos=4,  float norm=32767.f,
              SndObj** inObjs=0, AudioDeviceID dev=DEV_DEFAULT, 
           int vecsize=DEF_VECSIZE, float sr=DEF_SR);
~SndCoreAudio();

OSStatus
ADIOProc(const AudioBufferList *input, AudioBufferList *output, SndCoreAudio* cdata);

short Read();
short Write();
char* ErrorMessage();


};



#endif

#endif
