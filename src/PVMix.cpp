 
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
//
// PVMix.cpp: implementation of the PVMix class.
//
//////////////////////////////////////////////////////////////////////

#include "PVMix.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PVMix::PVMix()
{ }
PVMix::PVMix(SndObj* input, SndObj* input2, 
	     int vecsize,float sr):
  SpecMult(input, input2, vecsize, sr){
}

PVMix::~PVMix()
{
}


short
PVMix::DoProcess(){

  if(!m_error){
    if(m_input && m_input2){

      if(m_enable){	
	float amp1, amp2;

	amp1 = m_input->Output(0);
	amp2 = m_input2->Output(0);
	m_output[0] = amp1 > amp2 ? amp2 : amp1;
	amp1 = m_input->Output(1);
	amp2 = m_input2->Output(1);
	m_output[1] = amp1 > amp2 ? amp2 : amp1;	 
	 

	for(m_vecpos=2;m_vecpos < m_vecsize; m_vecpos+=2){
      
	  amp1 = m_input->Output(m_vecpos);
	  amp2 = m_input2->Output(m_vecpos);

	  if(amp2>amp1){
	    m_output[m_vecpos] = amp2;
	    m_output[m_vecpos+1] = m_input2->Output(m_vecpos+1);
	  }
	  else {
	    m_output[m_vecpos] = amp1;
	    m_output[m_vecpos+1] = m_input->Output(m_vecpos+1);
  	  }
  
	}
      }

      return 1;


    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;



}
