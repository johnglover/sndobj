// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Mix.h: interface of the mixer class                       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _MIX_H 
#define _MIX_H

#include "SndObj.h"

struct SndObjList{
  SndObj* obj;
  SndObjList* next;
                 
};
 

class Mixer : public SndObj{

 protected:

  SndObjList*  m_InObj;  // pointer to a linked list of SndObj
  int          m_ObjNo;  // number of input objects

    

 public:

  Mixer();                            
  Mixer(int ObjNo, SndObj** InObjs, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Mixer();
  
  int  GetObjNo() { return m_ObjNo; }  // return number of inputs
  short AddObj(SndObj* InObj);         // add a SndObj to the input list
  short DeleteObj(SndObj* InObj);      // delete a SndObj 
  short DoProcess();         // MIX
  int Connect(char* mess, void* input);

  char* ErrorMessage();
};

#endif
