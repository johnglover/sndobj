 
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

#include "SpecCombine.h"

SpecCombine::SpecCombine(){
  m_halfsize = m_vecsize/2;
  AddMsg("magnitude input", 33);
  AddMsg("phase input", 34);
}

SpecCombine::SpecCombine(SndObj *magin, SndObj* phasin, int vecsize, float sr)
  :SpecCart(magin, vecsize, sr){
  m_input2 = phasin;
  m_halfsize = m_vecsize/2;
  AddMsg("magnitude input", 33);
  AddMsg("phase input", 34);
}

SpecCombine::~SpecCombine(){
}

int
SpecCombine::Connect(char* mess, void *input){

  switch (FindMsg(mess)){

  case 33:
    m_input = (SndObj *) input;
    return 1;

  case 34:
    m_input2 = (SndObj *) input;
    return 1;

  default:
    return 0;

  }
}

short
SpecCombine::DoProcess(){

  if(!m_error){
    if(m_input && m_input2){

      float a, b; int p;

      m_output[0] = m_input->Output(0);
      m_output[1] = m_input->Output(m_halfsize);

      if(m_enable) {  
	
	for(m_vecpos = 1; m_vecpos < m_halfsize; m_vecpos++) {

	  p = m_vecpos*2;
	  a = m_input->Output(m_vecpos);
	  b = m_input2->Output(m_vecpos);
  
	  convert(&a, &b);

	  m_output[p] = a;
	  m_output[p+1] = b;

	}

      }
      else 
	for(m_vecpos = 0; m_vecpos < m_halfsize; m_vecpos++)
	  m_output[m_vecpos] = m_output[m_vecpos+m_halfsize] = 0.f;
 
      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;

}
