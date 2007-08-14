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

const int DEF_BSIZE =  512;
const int DEF_PERIOD = 4;
const int DEF_DEV = 0xFFFFFFFF;

class SndCoreAudio : public SndIO {

  AudioDeviceID m_dev;

  float** m_inbuffs;
  float** m_outbuffs;

  int m_sleept;
  int m_dont_use_input;
  int m_dont_use_output;

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
  bool m_interleaved;
  bool m_stopped;
  bool m_called_read;
  float m_norm;

  int OpenDevice(bool isInput=true);

 public:

  SndCoreAudio(int channels=2,int bufframes=DEF_BSIZE, int buffnos=DEF_PERIOD,  float norm=32767.f,
	       SndObj** inObjs=0, int dev=DEF_DEV, 
	       int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~SndCoreAudio();

  OSStatus
    ADIOProc(AudioDeviceID indev,
                        const AudioTimeStamp *inN, const AudioBufferList *input,
		        const AudioTimeStamp *inT, AudioBufferList *output,
	      const AudioTimeStamp *inOT, void* cdata);

  void Stop(){ m_stopped = true; }
  short Read();
  short Write();
  void SetSleepTime(int t) { m_sleept = t; }
  char* ErrorMessage();


};

int ListDevices(char **d, int devs=50);
void PrintDevices();

#endif

#endif
