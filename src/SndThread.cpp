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
  SndLink<SndObj>* NewLink;
  if(!( NewLink = new SndLink<SndObj>))
                 return 0; // failed to allocate memory
  NewLink->obj = obj;

  if(SndObjNo>0) // if at least 1 link exists
    NewLink->next = last->next; // make the new link next 
                                // point to the prev next

  else    // if this is the first link
    last = NewLink; // it is also the last

  last->next = NewLink; // the next link to the last
                        // is the top of the list
 
  SndObjNo++; // increment the number of SndObjs 
  return 1;   // Added Link will always be at the top
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

  // search start from top
  // temp1 is the link to be deleted
  temp1 = last->next; 
  // temp2 is the link before it
  temp2 = last;

  // search loop
  while(temp1->obj != obj){
  // temp2 & temp1 move to the next links
    temp2 = temp1; 
    temp1 = temp1->next;
  // if the search is back at the top, return  
  if(temp1 == last->next) return 0;
    }
  // link the previous to the next
  temp2->next = temp1->next;
  // delete the link
  delete temp1;
  SndObjNo--;  
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
     (void *)this)) return 0; 
#else 
     DWORD threadID;
     HANDLE hThread;
     if(_beginthread(
       (void(*)(void *))SndProcessThread, 4096, (void *)this)
                    ) return 0;        
#endif   
  return status;

}

int
SndThread::ProcOff(){
  status = OFF;
  return status;
}

void
SndProcessThread(SndThread* sndthread){
    
  int i;
  SndLink<SndObj>* temp = sndthread->last;
  SndLink<SndIO>* itemp = sndthread->input;
  SndLink<SndIO>* otemp = sndthread->output;

  while(sndthread->status){
 
    //... processing loop...
    
    for(i = 0; i < sndthread->InputNo; i++){
         itemp->obj->Read();
         itemp = itemp->next;
    }
    // sound processing 
   for(i = 0; i < sndthread->SndObjNo; i++){
         temp->obj->DoProcess();
         temp = temp->next;
    } 
    
   // output processing   
     for(i = 0; i < sndthread->OutputNo; i++){ 
    	 otemp->obj->Write();
         otemp = otemp->next;
		
    }
  }
  
  return;
}


#endif



