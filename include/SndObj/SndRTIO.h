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
const int DEFAULT_DEV = 0xFFFFFFFF;

#endif

#ifdef OSS             // Open Sound System (Linux, etc...)
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>

#endif

#ifdef ALSA

#include <alsa/asoundlib.h>

#endif


#ifdef SGI           // SGI on Irix
#include <audio.h>

const int AL_DEFAULT = AL_DEFAULT_OUTPUT;
#endif

#ifdef WIN           // Windows MME
#include <Windows.h>
#include <Mmsystem.h>


void ListDevices();
char* InputDeviceName(int dev, char* name);
char* OutputDeviceName(int dev, char* name);
#endif

class SndRTIO : public SndIO {

 protected:
       
  char* m_cp;
  short* m_sp;     // pointers to the buffer
  int m_count;     // counter
  int m_buffsize; // buffer size
  int m_items;     // items
  int m_encoding;  // encoding
      
#if defined  (WIN) || defined (OSS) || defined (SGI)   
  int m_dev;       // IO device ID
#endif
  int m_mode;

#ifdef MACOSX

  AudioDeviceID m_dev;

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
     
  snd_pcm_t  *m_dev;
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
 public:

#ifdef OSS
  SndRTIO(short channels, int mode, int buffsize = 512, int DMAbuffsize = 512,
	  int encoding = SHORTSAM_LE, SndObj** inputs = 0, int vecsize = DEF_VECSIZE, 
	  float sr=DEF_SR, char* device = "/dev/dsp");

#endif

#ifdef SGI	  
  SndRTIO(short channels, int mode, int buffsize = 512, int DACqueue = 512,
	  int encoding = SHORTSAM, SndObj** inputs=0, int vecsize = DEF_VECSIZE, 
	  float sr=DEF_SR, int dev=AL_DEFAULT);
#endif

#ifdef WIN
  SndRTIO(short channels, int mode, int buffsize = 256, int buffno = 10,
	  int encoding = SHORTSAM, SndObj** inputs=0, int vecsize = DEF_VECSIZE, 
	  float sr=DEF_SR, int dev = WAVE_MAPPER);
  void ResetBuffers(){ for(int n=0; n < m_buffno; n++) 
      memset(m_buffer[n], 0, m_pwhdr[n]->dwBufferLength); 
    m_firsttime = 1; m_ndx  = 0; m_count =  m_buffsize*m_channels; }
#endif

#ifdef MACOSX
  SndRTIO(short channels, int mode, int buffsize = 512, int buffno = 4,
	  int encoding = SHORTSAM, SndObj** inputs=0, 
	  int vecsize = DEF_VECSIZE, 
	  float sr=DEF_SR, AudioDeviceID dev = DEFAULT_DEV);

  OSStatus
    ADIOProc(const AudioBufferList *input,
	     AudioBufferList *output,
	     SndRTIO* cdata);

#endif

#ifdef ALSA
  SndRTIO(short channels, int mode, int buffsize = 1024, int buffno = 2,
	  int encoding = SHORTSAM_LE, SndObj** inputs = 0, int vecsize = DEF_VECSIZE, 
	  float sr=DEF_SR, char* device = "plughw:0,0");

#endif

#ifdef SWIGPYTHON
  SndRTIO() { };
#endif

  ~SndRTIO();
  short Write();
  short Read();
  char* ErrorMessage();
      

};


#endif
