 
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
