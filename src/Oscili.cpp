 
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
// Oscilt.cpp : implementation of the Oscili class            //
//              (interpolating oscillator).                   //
//                                                            //
//                                                            //
//************************************************************//

#include "Oscili.h"

//////////// CONSTRUCTION / DESTRUCTION ////////////////////////

Oscili::Oscili(){}

Oscili::Oscili(Table* table, float fr, 
	       float amp,  SndObj* inputfreq, 
	       SndObj* inputamp, int vecsize, float sr)
  : Oscil(table, fr, amp, 
	  inputfreq, inputamp, vecsize, sr){
}

Oscili::~Oscili(){}

////////////////// OPERATIONS ////////////////////////////////////


short
Oscili :: DoProcess(){  

  if(!m_error) {
    // wrapping loop
    float fr; 
    float amp; 
    if(!m_ptable){ 
      m_error = 1; // empty table object
      return 0;
    } 
    float* tab = m_ptable->GetTable();
    int i;

    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
	fr = m_fr + (m_input == 0 ? 0 : m_input->Output(m_vecpos));
	amp = m_amp + (m_inputamp== 0 ? 0 : m_inputamp->Output(m_vecpos));
	i = Ftoi(m_index);                                       
	m_output[m_vecpos] =  amp*(tab[i] +
				   ((tab[i] - tab[i+1])*(i - m_index)));
	        
	m_incr = fr * m_factor;                         
	m_index += m_incr;             // increment m_index
         
	while(m_index >= m_size)
	  m_index -= m_size;        // modulus
	while (m_index < 0)
	  m_index += m_size;
   
      }else {
	m_output[m_vecpos] = 0.f;
      }
    } // end wrapping loop
    return 1;
  }
  else return 0;
}











