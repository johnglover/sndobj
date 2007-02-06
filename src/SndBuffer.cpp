// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

////////////////////////////////////////
// SndBuffer.cpp:
// Implementation of the SndBuffer class
//
// VL, 2001
///////////////////////////////////////

#include "SndBuffer.h"


SndBuffer::SndBuffer(short channels, int buffsize, SndObj **inputlist, int vecsize, float sr):
  SndIO(channels, 32, inputlist, vecsize, sr){

  m_elements = m_wpointer = m_rpointer = 0;
  m_buffsize = buffsize*m_channels;
  if(!(m_buff = new float[m_buffsize])){
    m_error = 11;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
  }
  wlock = rlock = 0;
}

SndBuffer::~SndBuffer(){

}

short
SndBuffer::Read(){
 
  if(!m_error) { 
      while(1){ 
      // retrieve a sample from the buffer
      // if there is not enough new samples (elements < m_samples), block
      if (m_elements >= m_samples){
	int n;
	while(wlock) wait_here();
	 rlock = 1;
	for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
	  for(n=0; n < m_channels; n++){    
	    m_output[m_vecpos+n] = m_buff[m_rpointer];
	    m_rpointer=(m_rpointer+1)%m_buffsize;
	    m_elements--;
	  }
	 rlock = 0;
	return 1 ;
      }
      else wait_here();
	}
  }
  else return 0;     
}

short
SndBuffer::Write(){
 
  if(!m_error) { 
    while(1){
      // put a sample in the buffer
      // if there is no space left, block
      if(m_elements < m_buffsize) { 
	int n; 
	while(rlock) wait_here();
        wlock = 1;
	for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
	  for(n=0; n < m_channels; n++){
	    if(m_IOobjs[n])       
	      m_buff[m_wpointer]= m_IOobjs[n]->Output(m_vecpos);
	    else  m_buff[m_wpointer] = 0.f;
	      m_wpointer=(m_wpointer+1)%m_buffsize;
	      m_elements++;
	  }
        wlock = 0;
	return 1;  
      }   else wait_here();
    }
  }
  else return 0;       
}


char* 
SndBuffer::ErrorMessage(){ 

  char* message;

  switch(m_error){

  case 11:
    message = "Error allocating buffer memory.";
    break;


  default:
    message = SndIO::ErrorMessage();
    break;
  }

  return message;

}
