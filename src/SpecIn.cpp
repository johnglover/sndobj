// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  SpecIn.cpp: implementation of the SpecIn class.             //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "SpecIn.h"


SpecIn::SpecIn(){
   m_ioinput = 0;
   m_channel = 1;
   m_sr = 44100.f;
   m_enable = 1;
   m_initpos= 0;
   AddMsg("channel", 22);
          }

SpecIn::SpecIn(SndFIO *input, short channel, int vecsize, float sr): 
		  SndObj(0, vecsize, sr){

   m_ioinput = input;
   m_channel = channel;
   m_initpos = (m_channel-1)*vecsize;
   AddMsg("channel", 22);
}

SpecIn::~SpecIn(){
}


int
SpecIn::Connect(char* mess, void* input){

	switch (FindMsg(mess)){

	case 3:
    SetInput((SndIO *) input);
	return 1;

	default:
    return SndObj::Connect(mess,input);
     
	}


}


int
SpecIn::Set(char* mess, float value){

	switch (FindMsg(mess)){

	case 22:
    m_channel = (short) value; 
	return 1;

	default:
    return SndObj::Set(mess,value);
     
	}


}

   
short 
SpecIn::DoProcess(){
if(!m_error){
  for(m_vecpos=0;m_vecpos < m_vecsize; m_vecpos++){
	if(m_enable){
	if(m_ioinput){
     m_output[m_vecpos] = m_ioinput->Output(m_vecpos+m_initpos);   
		}
      else{	
        m_error = 10;
        return 0;
         }
	}
  else m_output[m_vecpos] = 0.f;

 }

   return 1;
}
	else return 0;
}

///////////// ERROR HANDLING //////////////////////////////////

char*
SpecIn::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
  message = "No error.";
  break; 

  case 10:
  message = "DoProcess() failed. No SndIO input object.";
  break;

  default:
  message = SndObj::ErrorMessage();
  break;
  }

 return message;

}
