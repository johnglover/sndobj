 
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

#include "SpecMult.h"


SpecMult::SpecMult(){
  SetVectorSize(DEF_FFTSIZE);
  m_input2 = 0;
  AddMsg("input 2", 21);
  AddMsg("table", 22);
}


SpecMult::SpecMult(SndObj* input1, SndObj* input2, int vecsize,
		   float sr)
  : SndObj(input1, vecsize, sr){

  m_input2 = input2;
  AddMsg("input 2", 21);
  AddMsg("table", 22);
  m_dynamic = true;
}

SpecMult::SpecMult(Table* spectab, SndObj* input1, int vecsize,
		   float sr)
  : SndObj(input1, vecsize, sr){

  m_input2 = 0;
  AddMsg("input 2", 21);
  AddMsg("table", 22);

  if(spectab->GetLen() >= vecsize) {
    m_spectable = spectab;
  }
  m_dynamic = false;


}


SpecMult::~SpecMult(){
}

int
SpecMult::Connect(char* mess, void* input){

  switch(FindMsg(mess)){

  case 21:
    SetInput2((SndObj*) input);
    return 1;
    
  case 22:
    SetTable((Table*) input);
    return 1;

  default:
    return SndObj::Connect(mess, input);

  }


}

short
SpecMult::DoProcess(){

  if(!m_error){
    if(m_input && (m_input2 || !m_dynamic)){
      float re1,re2,im1,im2;
	  
      for(m_vecpos = 2; m_vecpos < m_vecsize; m_vecpos+=2) {
     
	// every complex pair except 0 and nyquist
	if(m_enable) {
        
	  re1 = m_input->Output(m_vecpos);
	  if(m_dynamic){
	    re2 = m_input2->Output(m_vecpos); 
	  }
	  else re2 = m_spectable->Lookup(m_vecpos);
           
	  im1 = m_input->Output(m_vecpos+1);
	  if(m_dynamic) {
	    im2 = m_input2->Output(m_vecpos+1);
	  }
	  else 
	    im2 = m_spectable->Lookup(m_vecpos+1); 
	  // complex multiplication (a+ib)*(c+id)
	  // (ac - bd) - i(ad + bc)  
	  m_output[m_vecpos] = re1*re2 - im1*im2;
	  m_output[m_vecpos+1] = re1*im2 + im1*re2;

	}
	else 
	  m_output[m_vecpos+1] = m_output[m_vecpos] = 0.f;
      } 
      m_output[0] = m_input->Output(0)*(m_dynamic ?
					m_input2->Output(0) : m_spectable->Lookup(0));
      m_output[1] = m_input->Output(1)*(m_dynamic ?
					m_input2->Output(1) : m_spectable->Lookup(1));

      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;

}
