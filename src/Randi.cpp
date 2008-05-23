 
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
// Randi.cpp : implementation of the Randi class              //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Randi.h"

Randi::Randi(){
  m_target = m_start = 0;
}

Randi::Randi(float fr,float amp, SndObj* InFrObj, 
	     SndObj* InAmpObj, int vecsize, float sr)
  : Randh(fr, amp, InFrObj, InAmpObj, vecsize, sr)
{
  m_target = m_start = 0;     
}

Randi ::~Randi(){

}


/////////////// OPERATIONS //////////////////////////////////////
short
Randi::DoProcess(){  
 
  if(!m_error){
    float freq, amp, out;  
    for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){	     
      if(m_enable){

	freq = m_fr + (m_inputfr == 0 ? 0 : m_inputfr->Output(m_vecpos));
	amp = m_amp + (m_input== 0 ? 0 : m_input->Output(m_vecpos));

	out = ((m_target - m_start)*freq*m_count)/m_sr +
	  m_start;

	if((m_target-m_start) >= 0) {
	  if(out >= m_target){
	    m_start = m_target;
	    m_target = ((float)rand() - MAXR)/MAXR;
	    m_count = 0;
	  }   
	}
	else{
	  if(out <= m_target){
	    m_start = m_target;
	    m_target = ((float)rand() - MAXR)/MAXR;
	    m_count = 0;		  
	  }
	}

	m_count++;
	m_output[m_vecpos] = amp*out;
      }
      else m_output[m_vecpos] = 0.f;

    }
    return 1;
  }
  else return 0;

}





