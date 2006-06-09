// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//
// SndThread.h 
// Class SndThread: 
// Multithreading support for the SndObj Library
//
// Victor Lazzarini, 2001
//

#ifndef _SNDTHREAD_H
#define _SNDTHREAD_H

#include "AudioDefs.h"

#ifdef WINPTHREAD
#include <wpthread.h>
#endif

#ifndef WINPTHREAD
#include <pthread.h>
#endif

template<class s>  
struct SndLink{      // SndObj / SndIO lists links       
  SndLink<s>* next;  // next link
  s*          obj;   // object pointed at by the link 
};


enum { SNDIO_IN, SNDIO_OUT }; // IO list names     
enum { OFF=0, ON };           // processing status

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

  // pthread-related  member variables
  pthread_attr_t  attrib;
  pthread_t       thread;
 
  public:
  
  SndThread();
  SndThread(int n, SndObj** objlist, SndIO *out, SndIO *in=0);
  ~SndThread();
 
  int AddObj(SndObj *obj); // add to lists
  int AddObj(SndIO *obj, int iolist);
   
  // insert after a particular SndObj
  int Insert(SndObj *obj, SndObj* prev);
     
  int DeleteObj(SndObj *obj); // delete from lists
  int DeleteObj(SndIO *obj, int iolist);

  int GetStatus() { return status; }
  int GetSndObjNo() { return SndObjNo; }
  int GetInputNo() { return InputNo; }
  int GetOutputNo() { return OutputNo; }

  pthread_attr_t GetAttrib() { return attrib; }
  void SetAttrib(pthread_attr_t att) { attrib = att; }

  int ProcOn(); // start processing thread 
  int ProcOff(); // kill processing thread
     
  // external thread function
  friend void SndProcessThread(SndThread* sndthread); 
     

};

void SndProcessThread(SndThread* sndthread);

#endif         



