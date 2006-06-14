// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

///////////////////////////////////////////////////
//  SndRTIO.h: interface of the SndRTIO class
//  realtime audio IO 
//  currently supported on Irix, Linux (with OSS), MAC OSX (CoreAudio) 
//  and Windows
//

#ifndef _SNDRTIO_H 
#define _SNDRTIO_H

#include "SndIO.h"

#ifdef MACOSX    // Mac CoreAudio
#include <CoreAudio.h>
const int DEF_DEV = 0xFFFFFFFF;
const int DEF_BSIZE = 512;
const int DEF_PERIOD = 4;
#endif

#ifdef OSS             // Open Sound System (Linux, etc...)
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
typedef int AudioDeviceID;
#define DEF_DEV  "/dev/dsp"
const int DEF_BSIZE = 512;
const int DEF_PERIOD = 512;
#endif

#ifdef ALSA
#include <alsa/asoundlib.h>
typedef snd_pcm_t * AudioDeviceID;
#define DEF_DEV "plughw:0,0"
const int DEF_BSIZE = 1024;
const int DEF_PERIOD = 2;
#endif


#ifdef SGI           // SGI on Irix
#include <audio.h>
const int AL_DEFAULT = AL_DEFAULT_OUTPUT;
typedef int AudioDeviceID;
const int DEF_DEV = AL_DEFAULT; 
const int DEF_BSIZE = 512;
const int DEF_PERIOD = 512;
#endif

#ifdef WIN           // Windows MME
#include <Windows.h>
#include <Mmsystem.h>
typedef int AudioDeviceID;
void ListDevices();
char* InputDeviceName(int dev, char* name);
char* OutputDeviceName(int dev, char* name);
const int DEF_DEV = WAVE_MAPPER;
const int DEF_BSIZE = 256;
const int DEF_PERIOD = 10;
#endif

class SndRTIO : public SndIO {

 protected:
       
  char* m_cp;
  short* m_sp;     // pointers to the buffer
  int m_count;     // counter
  int m_buffsize; // buffer size
  int m_items;     // items
  int m_encoding;  // encoding
  AudioDeviceID m_dev;   // device ID
  int m_mode;

#ifdef MACOSX

  float** m_inbuffs;
  float** m_outbuffs;

  AudioStreamBasicDescription m_format;
  unsigned int m_bufframes;
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

#endif

#if defined (SGI) || defined (OSS) || defined (ALSA)
		  
  void* m_buffer;     // IO buffer
      
#endif // SGI or OSS or ALSA


#ifdef WIN

  WAVEFORMATEX* m_wfx;  // formatex structure 
  WAVEHDR** m_pwhdr;   // header structures, one for each data block 
  HGLOBAL*  m_hwhdr;   // header strructures handles
  HANDLE*   m_hData;   // data blocks handles

  void** m_buffer; // buffers (data blocks)
  int m_buffno; // number of buffers
  int m_ndx;   // buffer index

  HWAVEOUT m_hwo;      // output device handle
  HWAVEIN m_hwi;      // output device handle

  int m_cur;
  int m_status;
  bool m_firsttime; 

#endif

#ifdef SGI
  long* m_lp;         // long & float pointers
  float* m_fp;        // supported only on Irix

  ALconfig m_config;  // Audio Library config
  ALport   m_port;    // AL IO port
	  
  void Writef();  // write functions for different sample formats;        
  void Writel(); 

  void Readf();  // read functions for different sample formats
  void Readl();
#endif

#ifdef ALSA
     
  long* m_lp;

  void Writel();
  void Readl();

#endif


#ifndef MACOSX	       
  void Writec(); // write functions for different sample formats;        
  void Writes();

  void Reads();  // read functions
  void Readc();
#endif

  void SndRTIO_init(short, int, int=DEF_BSIZE, int=DEF_PERIOD,int=SHORTSAM, 
		    SndObj** =0,int=DEF_VECSIZE, float=DEF_SR, 
#if defined (OSS) || defined (ALSA)           
		    char* =DEF_DEV);
#else 
  AudioDeviceID=DEF_DEV);
#endif


public: 

SndRTIO(short ch, int mode, int bsize = DEF_BSIZE, 
        int period = DEF_PERIOD, int encoding = SHORTSAM, 
        SndObj** input=0, int vsize= DEF_VECSIZE, float sr=DEF_SR, 
#if defined(OSS) || defined(ALSA)
        char* dev = DEF_DEV)
#else
     int dev = DEF_DEV)
#endif
#ifndef MACOSX
: SndIO(ch, encoding*8,input,vsize, sr)
#else
: SndIO((ch < 2 ?  2 : ch), 
        (encoding > 0 ? encoding : sizeof(float)*8), 
         input, vsize, sr) 
#endif
{
SndRTIO_init(ch,mode,bsize,period,encoding,input,vsize,sr,dev);
}

SndRTIO() 
#ifndef MACOSX
  : SndIO(1,16,0,DEF_VECSIZE,DEF_SR)
#else
  : SndIO(2,16,0,DEF_VECSIZE,DEF_SR)
#endif
 { SndRTIO_init(1, SND_OUTPUT); }

SndRTIO(short channels, SndObj** input=0)
#ifndef MACOSX
  : SndIO(channels,16,input,DEF_VECSIZE,DEF_SR)
#else
: SndIO((ch < 2 ?  2 : ch), 
        (encoding > 0 ? encoding : sizeof(float)*8), 
         input, vsize, sr) 
#endif 
{
      SndRTIO_init(channels,SND_OUTPUT,DEF_BSIZE,DEF_PERIOD,SHORTSAM,input);
}

SndRTIO(SndObj *p) 
#ifndef MACOSX
  : SndIO(1,16,0,DEF_VECSIZE,DEF_SR)
#else
  : SndIO(2,16,0,DEF_VECSIZE,DEF_SR)
#endif
 { SndRTIO_init(1, SND_OUTPUT);
 SetOutput(1, p);
#ifdef MACOSX
    SetOutput(2, p); 
#endif
}

SndRTIO(SndObj *pl, SndObj *pr) : SndIO(2,16,0,DEF_VECSIZE,DEF_SR)
 { 
   SndRTIO_init(2, SND_OUTPUT); 
   SetOutput(1, pl); 
   SetOutput(2, pr); 
}


  ~SndRTIO();
  short Write();
  short Read();
  char* ErrorMessage();

#ifdef MACOSX
OSStatus ADIOProc(const AudioBufferList *input, AudioBufferList *output,
	     SndRTIO* cdata);
#endif   

};


#endif
