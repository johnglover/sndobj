 
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

//***********************************************************//
//  DelayLine.cpp: Implementation of the DelayLine Object    //
//                (simple delay line)                        //
//                                                           //
//                                                           //
//***********************************************************//

#include "DelayLine.h"
//////////CONSTRUCTION /////////////////////

DelayLine::DelayLine(){

  m_delaytime = 0.f;
  m_size = 0;
  m_delay = 0;
  m_wpointer = 0;
  m_rpointer = 0;

  AddMsg("max delaytime", 21);

}

DelayLine::DelayLine(float delaytime, SndObj* InObj, 
		     int vecsize, float sr):
  SndObj(InObj, vecsize, sr)
{


  m_delaytime = delaytime;
  m_size = (long)(delaytime*m_sr);
  if(!(m_delay = new float[m_size])){
    m_error = 13;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }

  m_wpointer = 0;
  m_rpointer = 1;

  Reset();
  AddMsg("max delaytime", 21);

}

DelayLine::~DelayLine()
{

  delete[] m_delay;

}

//////////////////OPERATIONS //////////////////////

int 
DelayLine::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetDelayTime(value);
    return 1;

  case 1:
    SetSr(value);
    return 1;	

  default:
    return SndObj::Set(mess,value);
     
  }


}


void 
DelayLine::SetSr(float sr){
  m_sr = sr;
  if(m_delay) delete[] m_delay;
  m_size = (long)(m_delaytime*m_sr);
  if(!(m_delay = new float[m_size])){
    m_error = 13;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  Reset();
}

void
DelayLine::Reset(){
  for(int n = 0; n < m_size; n++)
    PutSample(0.f);
}


void 
DelayLine::SetDelayTime(float delaytime)
{
  m_delaytime = delaytime;
  m_size = (long)(delaytime*m_sr);
  if(m_delay) delete[] m_delay;
  if(!(m_delay = new float[m_size])){
    m_error = 13;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  Reset();
}

short
DelayLine::DoProcess(){
  if(!m_error){     
    if(m_input){
      for(m_vecpos=0; m_vecpos < m_vecsize;m_vecpos++){
	if(m_enable){
	  m_output[m_vecpos] = GetSample();
	  PutSample(m_input->Output(m_vecpos));
	}
	else m_output[m_vecpos] = 0.f;
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

//////////// ERROR HANDLING //////////////////////////////////

char*
DelayLine::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 11:
    message = "DoProcess() failed. No input object.";
    break;

  case 13:
    message = "Delay line allocation error.";
    break;

  default:
    message = SndObj::ErrorMessage();
    break;
  }

  return message;

}







