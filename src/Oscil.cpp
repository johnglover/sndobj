 
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
// Oscil.cpp : implementation of the Oscil base class         //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Oscil.h"
Oscil::Oscil(){

  // initialise all values
  m_ptable = 0;
  m_fr = 440.f;
  m_amp = 1.f;
  m_inputamp = 0;
  m_index = 0.;
  m_size = 0;

  AddMsg("frequency", 21);
  AddMsg("amplitude", 22);
  AddMsg("phase", 23);
  AddMsg("table", 24);
  m_factor = m_size/m_sr;
}

Oscil::Oscil(Table* table, float fr, float amp,  
	     SndObj* inputfreq, SndObj* inputamp, 
	     int vecsize, float sr) : 
  SndObj(inputfreq, vecsize, sr) {


  m_ptable =  table;
  m_size = m_ptable->GetLen();
  m_fr = fr;
  m_amp = amp;
  m_index = 0.;

  m_inputamp = inputamp;

  AddMsg("frequency", 21);
  AddMsg("amplitude", 22);
  AddMsg("phase", 23);
  AddMsg("table", 24);
  m_factor = m_size/m_sr;
}

Oscil::~Oscil(){}

int
Oscil::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    m_input = (SndObj *) input;
    return 1;

  case 22:
    m_inputamp = (SndObj *) input;
    return 1;

  case 23:
    SetTable((Table *) input);
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }


}

int 
Oscil::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 1:
    SetSr(value);
    return 1;

  case 21:
    SetFreq(value);
    return 1;

  case 22:
    SetAmp(value);
    return 1;

  case 23:
    SetPhase(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}


short
Oscil :: DoProcess(){   
  if(!m_error){
    float fr; 
    float amp; 
    if(!m_ptable){ 
      m_error = 1; // empty table object
      return 0;
    }
    // control signal sampled at a lower rate
    fr = m_fr + (m_input == 0 ? 0 : m_input->Output(0));
    amp = m_amp + (m_inputamp == 0 ? 0 : m_inputamp->Output(0));
   
    // wrapping loop
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
   
	// truncating lookup
	m_output[m_vecpos] = amp*m_ptable->Lookup(Ftoi(m_index)); 
	m_incr = (fr * m_factor);
	m_index += m_incr;           
    
	while(m_index >= m_size) m_index -= m_size;
	while(m_index < 0) m_index += m_size;

      } else { // if disabled
	m_output[m_vecpos] = 0.f;
      }
   
    }  // end wrapping loop  
  
  
  
    return 1;
  }
  else return 0;
}



void 
Oscil::SetTable(Table* table){
  m_ptable = table;
  m_size = m_ptable->GetLen();
  m_factor = m_size/m_sr;
}

short
Oscil::SetPhase(float phase){

  if(m_ptable)
    {
      m_index = m_size*phase;
      return 1;
    }

  else { 
    m_error = 2; // empty table
    return 0;
  }
}


void Oscil::SetSr(float sr)
{
  SndObj::SetSr(sr);
  m_factor = m_size/m_sr;
}
