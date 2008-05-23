 
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
//  Mix.cpp: implementation of the Mixer class                //
//           (Sound Object mixer).                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Mix.h"

//////////////// CONSTRUCTION / DESTRUCTION ////////////////////

Mixer::Mixer(){
  m_ObjNo = 0;
  m_InObj = 0;
  AddMsg("mix", 21);
  AddMsg("disconnect", 22);
}

Mixer::Mixer(int ObjNo, SndObj** InObjs, int vecsize, float sr):
  SndObj(0, vecsize, sr){

  int i;
  SndObjList* temp;
  m_ObjNo = 0;
  m_InObj = 0;

  for(i = 0; i < ObjNo; i++) {
    if(InObjs[i]->GetSr() == m_sr){
      temp = m_InObj;               // first is last on list
      m_InObj = new SndObjList;
      m_InObj->obj = InObjs[i];
      m_InObj->next = temp;
      m_ObjNo++;
    }
    else m_error = 12;	 
  }
  AddMsg("mix", 21);
  AddMsg("disconnect", 22);
}

Mixer::~Mixer(){
  
  SndObjList* temp;
  
  while(m_InObj){
    temp = m_InObj;
    m_InObj = temp->next;
    delete temp;
  }

}

////////////////// OPERATIONS ///////////////////////////////

short
Mixer::AddObj(SndObj* InObj){
     
  if(m_sr != InObj->GetSr()){
    m_error = 12;
    return 0;
  }
  m_sr = InObj->GetSr();
  SndObjList* temp;
  temp = m_InObj; 	 
  m_InObj = new SndObjList;
  m_InObj->obj = InObj;
  m_InObj->next = temp;
  m_ObjNo++;
     
  return 1;
                                        
}

short
Mixer::DeleteObj(SndObj* InObj){

  SndObjList* temp;
  SndObjList* previous = 0;
  temp = m_InObj;
  while(temp){
    if(temp->obj == InObj){
      if(previous){
	previous->next = temp->next;
        /* m_InObj = previous; */
      }
      else m_InObj = temp->next;
      m_ObjNo--;
      delete temp;
      return 1;
    }
    else{
      previous = temp;
      temp = temp->next;
    }
  }
  m_error = 13;
  return 0;	
}

int
Mixer::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    AddObj((SndObj *) input);
    return 1;

  case 22:
    DeleteObj((SndObj *) input);
    return 1;
	
  default:
    return SndObj::Connect(mess,input);
     
  }
}

short
Mixer::DoProcess(){
  if(!m_error){
    if(m_ObjNo){
      SndObjList* temp; 
      for(m_vecpos=0;m_vecpos < m_vecsize; m_vecpos++){  	  
	m_output[m_vecpos] = 0.f;
	if(m_enable){ 
	  temp = m_InObj;
	  while(temp){ 
	    m_output[m_vecpos] += (temp->obj)->Output(m_vecpos);
	    temp = temp->next;
	  }
	} 
      }
      return 1;
    }
    else {
      m_error = 11;
      return 0;
    }
  }
  else return 0;
}
   


char*
Mixer::ErrorMessage(){

  char *message;
	
  switch(m_error){

  case 11:
    message = "DoProcess() failed, no input objects\n";
    break;
    
  case 12 :
    message = "Cannot add object: incompatible sampling rate\n";
    break;

  case 13:
    message = "Cannot delete object: obj not present in the input list\n";

  default :
    message =  SndObj::ErrorMessage();
    break;
  }

  return message;

}





