 
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

#include "Tap.h"
//////////CONSTRUCTION /////////////////////
Tap::Tap(){

  Enable();
  m_DLine = 0;
  m_delaytime = 0;
  m_delaysamples = 0;

  AddMsg("delaytime", 31);
  AddMsg("delay line", 32);

}

Tap::Tap(float delaytime, DelayLine* DLine, int vecsize, float sr)
  : DelayLine(delaytime, 0, vecsize, sr)
{

  m_DLine = DLine;
  if(m_delaytime <= m_DLine->GetDelayTime())
    m_delaytime = delaytime;
  else {
    m_delaytime = m_DLine->GetDelayTime();
    m_error = 20;
  }
  delete[] m_delay;
  m_delay = m_DLine->Buffer();
  m_size = (long) (m_DLine->GetDelayTime()*m_sr);
  m_delaysamples = (long) (m_delaytime*m_sr);

  m_rpointer = m_DLine->GetWritePointerPos() +
    (m_size-m_delaysamples);

  AddMsg("delaytime", 31);
  AddMsg("delay line", 32);
}

Tap::~Tap()
{
  m_delay = new float[1]; // just so that DelayLine destructor
  // has something to destroy.
}


//////////////////OPERATIONS //////////////////////
void 
Tap::SetDelayTime(float delaytime){
  m_delaytime = delaytime;
  if(m_delaytime > m_DLine->GetDelayTime())
    {
      m_delaytime = m_DLine->GetDelayTime();
      m_error = 20;
    }
         
  m_size = (long) (m_DLine->GetDelayTime()*m_sr);
  m_delaysamples = (long)(m_delaytime*m_sr);
  m_rpointer = m_DLine->GetWritePointerPos() +
    (m_size-m_delaysamples);

}

void
Tap::SetDelayTap(DelayLine *DLine){

  m_DLine = DLine;
  if(m_delaytime > m_DLine->GetDelayTime())
    {
      m_delaytime = m_DLine->GetDelayTime();
      m_error = 20;
    }

  m_delay = m_DLine->Buffer();
  m_sr = m_DLine->GetSr();
  m_size = (long) (m_DLine->GetDelayTime()*m_sr);
  m_delaysamples = (long)(m_delaytime*m_sr);
  m_rpointer = m_DLine->GetWritePointerPos() +
    (m_size-m_delaysamples);

}

int
Tap::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 31:
    SetDelayTime(value);
    return 1;

  default:
    return DelayLine::Set(mess,value);
     
  }

}

int
Tap::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 32:
    SetDelayTap((DelayLine *) input);
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }

}

short
Tap::DoProcess(){
  if(!m_error){  
    if(m_DLine){
      for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){
	if(m_enable)m_output[m_vecpos] = GetSample(); 
	else *m_output = 0.f;	
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
Tap::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 20:
    message = "Delaytime > max delay. Max delay set.";
    break;

  default:
    message = DelayLine::ErrorMessage();
    break;
  }

  return message;

}
