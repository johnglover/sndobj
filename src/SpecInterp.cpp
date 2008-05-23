 
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

#include "SpecInterp.h"

SpecInterp::SpecInterp(){


  m_offset = 0.f;
  m_interpobj = 0;
  AddMsg("interpolation", 31);

}

SpecInterp::SpecInterp(float  i_offset, SndObj *input1, SndObj* input2,
		       SndObj* interpobj, int vecsize, float sr)
  :SpecMult(input1, input2, vecsize, sr)
{

  m_offset = i_offset;
  m_interpobj = interpobj;
  AddMsg("interpolation", 31);

}

SpecInterp::~SpecInterp(){

}


int
SpecInterp::Connect(char* mess, void* input){

  switch(FindMsg(mess)){

  case 31:
    SetInterp(m_offset, (SndObj*) input);
    return 1;

  default:
    return SpecMult::Connect(mess, input);

  }


}

int
SpecInterp::Set(char* mess, float value){

  switch(FindMsg(mess)){

  case 31:
    SetInterp(value, m_interpobj);
    return 1;

  default:
    return SndObj::Set(mess, value);

  }


}

short
SpecInterp::DoProcess(){

  if(!m_error){
    if(m_input && m_input2){
      float interp, val;		 
      interp =  m_offset + (m_interpobj ? m_interpobj->Output(0) : 0);
      interp =  interp < 0 ? 0 : (interp <= 1 ? interp : 1);
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++) {
	if(m_enable) {     
	  // interpolate 
	  val = m_input->Output(m_vecpos);
	  m_output[m_vecpos] = val + 
	    (m_input2->Output(m_vecpos) - val)*interp;

	}
	else 
	  m_output[m_vecpos] = 0.f;
      } 
      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;

}
