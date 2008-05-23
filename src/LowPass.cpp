 
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
// Copyright (c)Rory Walsh 2003
// See License.txt for a disclaimer of all warranties
// and licensing information

//*************************************************************//
// LowPass.cpp : implementation of a Low Pass filter dervied from 
//               Filter Base Class  
//         Rory Walsh May 2003   			
//*************************************************************//
#include "LowPass.h"

LoPass::LoPass()
{
  double C = 2 - cos(2*PI*m_fr/m_sr);	
  m_b1 = sqrt((C*C) - 1) - C; 
  m_a = 1 + m_b1;
}

LoPass::LoPass(float freq, SndObj* inObj, int vecsize, float sr):
  Filter(freq, 1, inObj,vecsize,sr)
{
  double  C = 2 - cos(2*PI*m_fr/m_sr);	
  m_b1 = sqrt((C*C) - 1) - C; 
  m_a = 1 + m_b1;
}

LoPass::~LoPass(){
}

int
LoPass::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetFreq(value);
    return 1;

  case 23:
    SetSr(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }
}

short
LoPass::DoProcess(){   
                          
  if(!m_error){                       
    if(m_input) { 
      for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){  

	if(m_enable){

	  m_output[m_vecpos] = m_delay[0] = 
	    m_a*m_input->Output(m_vecpos)  - m_b1*m_delay[0];
	    
	}
	else m_output[m_vecpos] = 0.f;
      }
      return 1;
	 
    } else {
      m_error = 11;
      return 0;
    }
  } else return 0;
}
