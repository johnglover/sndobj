 
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

#include "Osc.h"

Osc::Osc(){
  m_inputamp = m_inputfr = 0;
}

Osc::Osc(Table* table, float fr, float amp, 
	 SndObj* inputfr, SndObj* inputamp,
	 int vecsize, float sr) 
  : FastOsc(table, fr, amp,vecsize, sr){

  m_inputamp = inputamp;
  m_inputfr = inputfr;

}

Osc::~Osc(){
}

int
Osc::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    SetFreq((SndObj*) input);
    return 1;

  case 22:
    SetAmp((SndObj*) input);
    return 1;

  default:
    return FastOsc::Connect(mess,input);
     
  }


}

short
Osc::DoProcess(){

  if(!m_error){
    if(!m_ptable){ 
      m_error = 1; // empty table object
      return 0;
    }
    long incr;
    float amp, fr;
    long ph = m_phase;
    float *tab = m_ptable->GetTable();  
    // wrapping loop
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
   
	fr = m_fr + (m_inputfr == 0 ? 0 : m_input->Output(m_vecpos));
	amp = m_amp + (m_inputamp == 0 ? 0 : m_inputamp->Output(m_vecpos));

	m_output[m_vecpos] = amp*tab[ph>>m_lobits] ;	
	incr = (long)(fr * m_factor);   
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
