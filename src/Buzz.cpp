 
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

#include "Buzz.h"
#include <math.h>

Buzz::Buzz(){

  m_fr = 440.f;
  m_amp = 1.f;
  m_harm = 10;

  if(!(m_ptable = new HarmTable(2048, 1, SINE))){
    m_error = 12;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  } 

  if(!(oscil1 = new Oscili(m_ptable, m_fr*((2*m_harm+1)/2.f), 1.f, 0,0,1))){
    m_error = 11;
    cout << ErrorMessage();
    return;
  }
  if(!(oscil2 = new Oscili(m_ptable, m_fr/2.f, 1.f,0,0,1))){
    m_error = 11;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  m_inputamp = 0;
  AddMsg("frequency", 21);
  AddMsg("amplitude", 22);
  AddMsg("harmonics", 23);

}

Buzz::Buzz(float fr, 
	   float amp, short harms,  SndObj* inputfreq, 
	   SndObj* inputamp, int vecsize, float sr):
  SndObj(inputfreq, vecsize, sr){

  m_fr = fr;
  m_amp = amp;
  m_harm = harms;  
  m_inputamp = inputamp;


  if(!(m_ptable = new HarmTable((long)m_sr/10, 1, SINE))){
    m_error = 12;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }

  if(!(oscil1 = new Oscili(m_ptable, m_fr*((2*m_harm)+1)/2, 1.f, 0, 0,
			   1, m_sr))){
    m_error = 11;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  if(!(oscil2 = new Oscili(m_ptable, m_fr/2, 1.f, 0, 0, 1, m_sr))){
    m_error = 11;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }

  AddMsg("frequency", 21);
  AddMsg("amplitude", 22);
  AddMsg("harmonics", 23);

}

Buzz::~Buzz(){
  delete m_ptable;
  delete oscil1;
  delete oscil2;

}

void
Buzz::SetSr(float sr){
  m_sr = sr;
  oscil1->SetSr(m_sr);
  oscil2->SetSr(m_sr);
}

void
Buzz::SetHarm(int harm){
  m_harm = harm;
  oscil1->SetFreq(m_fr*((2*m_harm+1)/2.f));
  oscil1->SetPhase(0.f);
  oscil2->SetPhase(0.f);
}

void
Buzz::SetFreq(float fr, SndObj* InFrObj){
  m_fr = fr;
  if(!(m_input = InFrObj)){ 
    oscil1->SetFreq(fr*((2*m_harm+1)/2.f));
    oscil2->SetFreq(fr/2.f);
  }
}

int 
Buzz::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetFreq(value);
    return 1;

  case 22:
    SetAmp(value);
    return 1;

  case 23:
    SetHarm((int)value);
    return 1;

  case 1:
    SetSr(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}

int 
Buzz::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    m_input = (SndObj *) input;
    return 1;

  case 22:
    m_inputamp = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }


}
 
short 
Buzz :: DoProcess(){  
  if(!m_error){
    float a;
    float b; 
    float fr;
    float amp;  

    for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
  
	amp = m_amp + (m_inputamp == 0 ? 0 : m_inputamp->Output(m_vecpos));
   
	if(m_input){
	  fr =  m_fr+m_input->Output(m_vecpos);
	  oscil1->SetFreq(fr*((2*m_harm+1)/2.f));
	  oscil2->SetFreq(fr/2.f);
	} 
	oscil1->DoProcess();
	oscil2->DoProcess();
	a = oscil1->Output(0);
	b = oscil2->Output(0);
   

	if(b != 0) 
	  m_output[m_vecpos] = (amp/(2*m_harm))*((a/b)-1);
	else m_output[m_vecpos] = amp;     

	// a simple limiter to avoid occasional big pops 
	if(fabs((double)m_output[m_vecpos]) > amp) 
	  m_output[m_vecpos] = 
	    (m_output[m_vecpos] > 0 ? amp : -amp);  
      }
      else m_output[m_vecpos] = 0.f;
    }
    return 1;
  }
  else return 0;
}




char*
Buzz::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 11:
    message = "Error allocating memory for oscillator objects\n";
    break;

  case 12:
    message = "Error allocating memory for table object\n";
    break;

  default:
    message = SndObj::ErrorMessage();
    break;
  }

  return message;

}
