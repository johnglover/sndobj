 
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

/////////////////////////////////////
// TpTz.cpp: implementation of the Two-pole Two-zero
//           filter class
////////////////////////////////////////

#include "TpTz.h"


TpTz::TpTz(){

  m_a1 = m_a2 = m_b1 = m_b2 = m_a = 0.0;
  AddMsg("coefficient a0", 21);
  AddMsg("coefficient a1", 22);
  AddMsg("coefficient a2", 23);
  AddMsg("coefficient b1", 24);
  AddMsg("coefficient b2", 25);
}

TpTz::TpTz(double a, double a1, double a2,
	   double b1, double b2, SndObj* input,
	   int vecsize, float sr) 
  : Filter(0.f, 0.f, input, vecsize, sr){


  m_a = a;
  m_a1 = a1;
  m_a2 = a2;
  m_b2 = b2;
  m_b1 = b1;

  AddMsg("coefficient a0", 21);
  AddMsg("coefficient a1", 22);
  AddMsg("coefficient a2", 23);
  AddMsg("coefficient b1", 24);
  AddMsg("coefficient b2", 25);

}

TpTz::~TpTz(){
}

int
TpTz::Set(char* mess, float value){
  switch (FindMsg(mess)){

  case 21:
    SetParam((double)value,m_a1,m_a2,m_b1, m_b2);
    return 1;

  case 22:
    SetParam(m_a,(double)value,m_a2,m_b1, m_b2);
    return 1;

  case 23:
    SetParam(m_a,m_a1,(double)value,m_b1, m_b2);
    return 1;

  case 24:
    SetParam(m_a,m_a1,m_a2,(double)value, m_b2);
    return 1;

  case 25:
    SetParam(m_a,m_a1,m_a2,m_b1, (double)value);
    return 1;

  default:
    return Filter::Set(mess,value);
     
  }
}


short
TpTz::DoProcess(){   

  if(!m_error){                      
    if(m_input) { 
      double out = 0.f, w = 0.f;  
      for(m_vecpos=0;m_vecpos < m_vecsize;m_vecpos++){  
	if(m_enable){

	  w = m_a*(m_input->Output(m_vecpos)) - m_b1*m_delay[0] - m_b2*m_delay[1];
	  out = w + m_a1*m_delay[0] + m_a2*m_delay[1];

	  m_delay[1] = m_delay [0];    
	  m_delay[0] = w;
	  m_output[m_vecpos] = (float) out;

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









