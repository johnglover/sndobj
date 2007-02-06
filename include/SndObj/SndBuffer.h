// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

/////////////////////////////////////// 
// SndBuffer.h:
// IO buffer for interthread/process
// communication
//
// VL, 2001
///////////////////////////////////////
#ifndef _SNDBUFIO_H
#define _SNDBUFIO_H

#include "SndIO.h"
#ifdef WIN
#include <windows.h>
#endif

class SndBuffer : public SndIO {

  int  m_buffsize;
  int  m_wpointer;
  int  m_rpointer;
  int  m_elements;
  int  wlock, rlock;
  float* m_buff;

 public:

  SndBuffer(short channels, int buffsize=DEF_VECSIZE, 
	    SndObj** inputlist=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~SndBuffer();

  short Write();
  short Read();
 
  void wait_here(){
#ifdef WIN
    Sleep(1);
#else
    usleep(1);
#endif
  }
  char* ErrorMessage();

};

#endif
