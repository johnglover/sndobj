 
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
// Copyright (c)Victor Lazzarini and Rory Walsh, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

// SndThread.cpp
// Implementation of the SndThread class
//
// Victor Lazzarini, 2001
//

#ifndef NOPTHREAD   // needs pthread library

#include "SndThread.h"

SndThread::SndThread(){

  SndObjNo = 0;
  InputNo = 0;
  OutputNo = 0;
  last = 0;
  input =  0;
  output = 0;
  status = OFF;
#ifndef USE_WIN32THREADS
  pthread_attr_init(&attrib);
#endif
  ProcessCallback = NULL;
  SndProcessThread = threadfunc;
  m_changed = m_parid[0] = m_parid[1] = m_parid[2] = m_parid[3] = false;
  processing = false;
  
}

SndThread::SndThread(int n, SndObj** objs, SndIO *out, SndIO *in){

  SndObjNo = 0;
  InputNo = 0;
  OutputNo = 0;
  last = 0;
  input =  0;
  output = 0;
  for(int i=0; i < n; i++)AddObj(objs[i]);
  if(in) AddObj(in, SNDIO_IN);
  if(out) AddObj(out, SNDIO_OUT);
  status = OFF;
#ifndef USE_WIN32THREADS
  pthread_attr_init(&attrib);
#endif
  ProcessCallback = NULL;
  SndProcessThread = threadfunc;
  m_changed = m_parid[0] = m_parid[1] = m_parid[2] = m_parid[3] = false;
  processing = false;
  
}

SndThread::~SndThread(){

  SndLink<SndObj>* temp;
  SndLink<SndIO>*  iotemp;
  int i;

  if(status != OFF) ProcOff();
  for(i = 0; i < SndObjNo; i++){
    temp = last->next;
    DeleteObj(temp->obj);
  }
  for(i = 0; i < InputNo; i++){
    iotemp = input->next;
    DeleteObj(iotemp->obj, SNDIO_IN);
  }
  for(i = 0; i < OutputNo; i++){
    iotemp = output->next;
    DeleteObj(iotemp->obj, SNDIO_OUT);
  }
}

int
SndThread::AddObj(SndObj* obj){
  
 SndLink<SndObj> *NewLink, *temp;
  if(!( NewLink = new SndLink<SndObj>))
    return 0; // failed to allocate memory
  
  temp = last; 
  last = NewLink; // NewLink is always last
  last->obj = obj; 
  if(SndObjNo>0) { // if at least 1 link exists
   last->next = temp->next; // last always points to 1st 
   temp->next = last;   // next to last points to last
  } 
  else
    last->next = last; // points to itself (1st)
  SndObjNo++; // increment the number of SndObjs 
  return 1;   // Added Link will always be at the end
  
}

int
SndThread::AddObj(SndIO* obj, int iolist){
  SndLink<SndIO>* NewLink;
  if(!( NewLink = new SndLink<SndIO>))
    return 0; // failed to allocate memory
  NewLink->obj = obj;

  switch(iolist){
    // adding to input list
  case SNDIO_IN:      
    if(InputNo>0) NewLink->next = input->next;
    else input = NewLink;
    input->next = NewLink;
    InputNo++;
    return 1;
   
    // adding to output list
  case SNDIO_OUT:
    if(OutputNo>0) NewLink->next = output->next;
    else output = NewLink;
    output->next = NewLink;
    OutputNo++;
    return 1;  
  
  default:
    delete NewLink;
    return 0;
  }

}

int
SndThread::DeleteObj(SndObj* obj){

  SndLink<SndObj>* temp1; 
  SndLink<SndObj>* temp2;

  // search start from last
  // temp1 is the link to be deleted
  temp1 = last->next; 
  // temp2 is the link before it
  temp2 = last;

  // search loop
  while(temp1->obj != obj){
    // temp2 & temp1 move to the next links
    temp2 = temp1; 
    temp1 = temp1->next;
    // if the search is back at the last, return  
    if(temp1 == last->next) return 0;
  }
  // link the previous to the next
  if(temp1 == last) last = temp2;
  temp2->next = temp1->next;
  SndObjNo--; 
  // delete the link
  delete temp1;
  return 1;
}

int
SndThread::DeleteObj(SndIO* obj, int iolist){

  SndLink<SndIO>* temp1; 
  SndLink<SndIO>* temp2;

  switch(iolist){

  case SNDIO_IN: 
    temp1 = input->next; 
    temp2 = input;

    while(temp1->obj != obj){
      temp2 = temp1; 
      temp1 = temp1->next;
      if(temp1 == input->next) return 0;
    }
    if(temp1 == input) input = temp2;
    temp2->next = temp1->next;
    delete temp1;
    InputNo--;  
    return 1;
 
  case SNDIO_OUT:
    temp1 = output->next; 
    temp2 = output;

    while(temp1->obj != obj){
      temp2 = temp1; 
      temp1 = temp1->next;
      if(temp1 == output->next) return 0;
    }
    if(temp1 == output) output = temp2;
    temp2->next = temp1->next;
    delete temp1; 
    OutputNo--; 
    return 1;

  default:  
    return 0;
  }
}

int 
SndThread::Insert(SndObj* obj, SndObj* prev){

  SndLink<SndObj>* temp;
  SndLink<SndObj>* InsertLink;
  int pos = 0;

  if(!( InsertLink = new SndLink<SndObj>))
    return 0; // failed to allocate memory
  InsertLink->obj = obj;

  // search start from last
  // temp is the link in front of
  // which the inserted link will be
  temp = last; 
  // search loop
  while(temp->obj != prev){
    temp = temp->next;
    pos++; // position counter (0 is last, 1 is top)
    // if the search is back at the top, return  
    if(temp == last) return 0;
  }
  InsertLink->next = temp->next;
  temp->next = InsertLink;
  SndObjNo++;
  return pos+1; // returns inserted link position
}
     

int
SndThread::ProcOn(){
  status = ON; 
#ifndef USE_WIN32THREADS
  if(pthread_create(&thread, &attrib, 
		    (void * (*)(void *)) SndProcessThread,
		    (void *)this)) return status; 
#else 
  if(hThread = _beginthread(
		  (void(*)(void *))SndProcessThread, 4096, (void *)this)
     ) return status;        
#endif   
  return 0;

}

int
SndThread::ProcOff(){
  status = OFF;
  return status;
}

void SndThread::UpdateSr(){

  int i;
  SndLink<SndObj>* temp = last;

    for(i = 0; i < SndObjNo; i++){
      temp->obj->SetSr(m_sr);
      temp = temp->next;
    } 

}

void SndThread::UpdateVecsize(){

  int i;
  SndLink<SndObj>* temp = last;
  SndLink<SndIO>* itemp = input;
  SndLink<SndIO>* otemp = output;

   for(i = 0; i < InputNo; i++){
     itemp->obj->SetVectorSize(m_vecsize_max);
      itemp = itemp->next;
    }
    for(i = 0; i < SndObjNo; i++){
      temp->obj->SetVectorSize(m_vecsize_max);
      temp = temp->next;
    } 
    for(i = 0; i < OutputNo; i++){ 
      otemp->obj->SetVectorSize(m_vecsize_max);
      otemp = otemp->next;
    }
}

void SndThread::UpdateLimit(){

  int i;
  SndLink<SndObj>* temp = last;
  SndLink<SndIO>* itemp = input;
  SndLink<SndIO>* otemp = output;
  
   for(i = 0; i < InputNo; i++){
     itemp->obj->LimitVectorSize(m_vecsize);
      itemp = itemp->next;
    }
    for(i = 0; i < SndObjNo; i++){
      temp->obj->LimitVectorSize(m_vecsize);
      temp = temp->next;
    } 
    for(i = 0; i < OutputNo; i++){ 
      otemp->obj->LimitVectorSize(m_vecsize);
      otemp = otemp->next;
    }
  
}
void SndThread::UpdateRestore(){

  int i;
  SndLink<SndObj>* temp = last;
  SndLink<SndIO>* itemp = input;
  SndLink<SndIO>* otemp = output;

   for(i = 0; i < InputNo; i++){
      itemp->obj->RestoreVectorSize();
      itemp = itemp->next;
    }
    for(i = 0; i < SndObjNo; i++){
      temp->obj->RestoreVectorSize();
      temp = temp->next;
    } 
    for(i = 0; i < OutputNo; i++){ 
      otemp->obj->RestoreVectorSize();
      otemp = otemp->next;
    }
}
void
threadfunc(void* data){
    
  int i;
  SndThread *sndthread = (SndThread *) data;
  SndLink<SndObj>* temp;
  SndLink<SndIO>* itemp;
  SndLink<SndIO>* otemp;

 
  while(sndthread->status){

   temp = sndthread->last;
   itemp = sndthread->input;
   otemp = sndthread->output;

    //... processing loop...

    sndthread->Update();
    
    for(i = 0; i < sndthread->InputNo; i++){
      itemp->obj->Read();
      itemp = itemp->next;
    }
    // callback
    if(sndthread->ProcessCallback != NULL)
    sndthread->ProcessCallback(sndthread->callbackdata);          

    // sound processing 

    sndthread->processing = true;
    for(i = 0; i < sndthread->SndObjNo; i++){
      temp = temp->next;
      temp->obj->DoProcess();
    } 
    sndthread->processing = false;

    // output processing   
    for(i = 0; i < sndthread->OutputNo; i++){ 
      otemp->obj->Write();
      otemp = otemp->next;
		
    }
  }
#ifndef USE_WIN32THREADS 
  return;
#else
  _endthread();
#endif
}


#endif



