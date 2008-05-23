 
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
