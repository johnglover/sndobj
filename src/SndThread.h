 
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
// Copyright (c)Victor Lazzarini and Rory Walsh, 1997-2006
// See License.txt for a disclaimer of all warranties
// and licensing information

//
// SndThread.h 
// Class SndThread: 
// Multithreading support for the SndObj Library
//
// Victor Lazzarini, 2001
// Win32 thread code by Rory Walsh, 2006

#ifndef _SNDTHREAD_H
#define _SNDTHREAD_H

#include "SndObj.h"
#include "SndIO.h"

#ifdef WINPTHREAD
#include <wpthread.h>
#elif USE_WIN32THREADS
#include <process.h>
#include <windows.h>
#else
#include <pthread.h>
#endif



template<class s>  
struct SndLink{      // SndObj / SndIO lists links       
  SndLink<s>* next;  // next link
  s*          obj;   // object pointed at by the link 
};

enum { SNDIO_IN, SNDIO_OUT }; // IO list names     
enum { OFF=0, ON };           // processing status

#ifdef PYTHON_WRAP
struct pycallbackdata {
  PyObject *func;
  PyObject *data;
};
#endif

class SndThread {

 protected:
  // three circular lists are declared: 
  // one for processing and two for IO

  SndLink<SndObj>*  last; // pointer to last element 
  SndLink<SndIO>*  input; // input list
  SndLink<SndIO>*  output; // output list
 
  int SndObjNo; // number of SndObjs in the list
  int InputNo;  // etc inputs
  int OutputNo; // etc outputs
                // used to control the processing loop

  int status;   // processing status ON, OFF

  void (*ProcessCallback)(void *callbackdata);
  void (*SndProcessThread)(void *data);
  void *callbackdata;

  bool processing;
  // pthread-related  member variables
#ifndef USE_WIN32THREADS
  pthread_attr_t  attrib;
  pthread_t       thread;
#else
  uintptr_t hThread;
#endif
  int m_vecsize;
  int m_vecsize_max;
  float m_sr;
  bool m_changed;
  bool m_parid[4];

  void UpdateSr();
  void UpdateVecsize();
  void UpdateLimit();
  void UpdateRestore();

  void  Update(){ if(m_changed){
    if(m_parid[0]){
      UpdateSr(); m_parid[0] = false;
    }
    if(m_parid[1]){
      UpdateVecsize(); m_parid[1] = false;
    }
    if(m_parid[2]){
      UpdateLimit(); m_parid[2] = false;
    }
    if(m_parid[3]){
      UpdateRestore(); m_parid[3] = false;
    }
    m_changed = false;
  }
  }


 public:

#ifdef PYTHON_WRAP
  PyThreadState *_tstate;
  pycallbackdata pydata;
#endif
  void *GetProcessCallback() { return (void *)ProcessCallback; }

  SndThread();
  SndThread(int n, SndObj** objlist, SndIO *out, SndIO *in=0);
  virtual ~SndThread();
 
  int AddObj(SndObj *obj); // add to lists
  int AddObj(SndIO *obj, int iolist);
   
  // insert after a particular SndObj
  int Insert(SndObj *obj, SndObj* prev);
     
  int DeleteObj(SndObj *obj); // delete from lists
  int DeleteObj(SndIO *obj, int iolist);

  void SetProcessCallback(void (*Callback)(void *), void *cbdata){
    ProcessCallback = Callback;
    callbackdata = cbdata;
  }

  int GetStatus() { return status; }
  int GetSndObjNo() { return SndObjNo; }
  int GetInputNo() { return InputNo; }
  int GetOutputNo() { return OutputNo; }
#ifndef USE_WIN32THREADS
  pthread_attr_t GetAttrib() { return attrib; }
  void SetAttrib(pthread_attr_t att) { attrib = att; }
#endif

  void SetVectorSize(int vecsize){
    m_vecsize_max = vecsize; 
    m_changed = m_parid[1] = true;
    if(status==OFF) Update();
  }

  void LimitVectorSize(int limit){
    m_vecsize = limit; 
     m_changed = m_parid[2] = true;
    if(status==OFF) Update();
  }
  void RestoreVectorSize(){
    m_changed = m_parid[3] = true;
    if(status==OFF) Update();
  }
  void SetSr(float sr){
    m_sr = sr;
    m_changed = m_parid[0] = true;
    if(status==OFF) Update();
  };
 
  int ProcOn(); // start processing thread 
  int ProcOff(); // kill processing thread
    
  // external thread function
  friend void threadfunc(void* sndthread); 
     

};

void threadfunc(void* sndthread);

#endif         



