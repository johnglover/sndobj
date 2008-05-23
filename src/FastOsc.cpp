 
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

#include "FastOsc.h"

FastOsc:: FastOsc(){

  m_phase = 0;
  m_ptable = 0;
  m_size = 0;
  m_factor = maxlength/m_sr;
  m_amp = 16000.f;
  m_fr = 440.f;


  AddMsg("frequency", 21);
  AddMsg("amplitude", 22);
  AddMsg("phase", 23);
  AddMsg("table", 24);

}

FastOsc:: FastOsc(Table* table, float fr, float amp,
                  int vecsize, float sr): 
  SndObj(0, vecsize, sr){

  m_phase = 0;
  m_ptable = table;
  if(m_ptable){	
    m_size = table->GetLen();
    int lobits = 0;
    for(int len = m_size;
	(len & maxlength)==0; lobits++, len<<=1);
    m_lobits = lobits;
  }
  else m_size = 0;

  m_factor = (float)maxlength/m_sr;
  m_amp = amp;
  m_fr = fr;


  AddMsg("frequency", 21);
  AddMsg("amplitude", 22);
  AddMsg("phase", 23);
  AddMsg("table", 24);

}

FastOsc::~FastOsc(){ 
}

void FastOsc::SetSr(float sr)
{
  SndObj::SetSr(sr);
  m_factor = maxlength/m_sr;
}

int
FastOsc::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 23:
    SetTable((Table *) input);
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }


}

void
FastOsc::SetTable(Table *table)
{
  m_ptable = table;
  m_size = m_ptable->GetLen(); 
  m_phase = 0;
  int lobits =0;
  for(int len = m_size;
      (len & maxlength)==0; lobits++, len<<=1);
  m_lobits = lobits;
}



int
FastOsc::Set(char* mess, float value){

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
FastOsc::DoProcess(){

  if(!m_error){
    if(!m_ptable){ 
      m_error = 1; // empty table object
      return 0;
    }
    long incr = (long) (m_fr * m_factor);
    float amp = m_amp;
    long ph = m_phase;
    float *tab = m_ptable->GetTable();  
    // wrapping loop
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
   
	m_output[m_vecpos] =  *(tab+(ph>>m_lobits)) * amp ;	   
	ph += incr;
	ph &= phasemask;

      } 
      else { // if disabled
	m_output[m_vecpos] = 0.f;
      }

    }  // end wrapping loop 
    m_phase = ph;

    return 1;
  }
  else return 0;
}
