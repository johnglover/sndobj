// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

/////////////////////////////////////////////////////////
//  SndIO.cpp: implementation of the SndIO class
//
//
//
//

#include "SndIO.h"


SndIO::SndIO(short channels, short bits, SndObj** inputlist,
		int vecsize, float sr){

int n;
m_channels = channels;
m_bits = bits;
m_sampsize = bits/8;
m_vecsize = vecsize;
m_vecpos = 0;
m_sr = sr;

if(m_channels){
if(!(m_IOobjs = new SndObj*[m_channels])){
	m_error = 2;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
	return;
}

if(inputlist)  // if an array of input objects exists	 
   for(n=0;n<m_channels;n++){	     
     m_IOobjs[n]=inputlist[n]; // set output channels 
     
}
else for(n=0;n<m_channels;n++) m_IOobjs[n] = 0; // zero the pointers
// vecsize is in frames! m_samples is vecsize in samples
m_samples = m_vecsize*m_channels;
if(!(m_output = new float[m_samples])){
	m_error = 1;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
	return;
 }
}
else {
	m_IOobjs = 0;
        m_output = 0;
	m_samples = 0;
}
m_error = 0;

}

SndIO::~SndIO(){

delete[] m_IOobjs;
delete[] m_output;

}


short
SndIO::Write(){

if(m_IOobjs){
  for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++)
	for(int n = 0; n < m_channels; n++)
		if(m_IOobjs[n])
        cout << m_IOobjs[n]->Output(m_vecpos) << "\n";
	 return 1;
    }
    else{
	m_error = 4;
	return 0;
	}
}

short
SndIO::Read(){
  for(m_vecpos = 0; m_vecpos < m_samples; m_vecpos+=m_channels)
    for(int n = 0; n < m_channels; n++)
       cin >> m_output[n+m_vecpos];
    return 1;
}

char* SndIO::ErrorMessage(){
	 
  char* message;
   
  switch(m_error){

  case 0:
  message = "No error\n";
  break; 

  case 1:
  message = "Failed to allocate vector memory\n";
  break;

  case 2:
  message = "Failed to allocate input object memory\n";
  break;

  case 3:
  message = "Sampling rate mismatch\n";
  break;

  case 4:
  message = "No input objects \n";
  break;

  default:
  message = "Undefined error\n";
  break;
  
  }

 return message;

}

