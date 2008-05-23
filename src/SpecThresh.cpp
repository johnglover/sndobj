 
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

#include "SpecThresh.h"

SpecThresh::SpecThresh(){
  m_thresh = 0;
  AddMsg("threshold", 41);
}

SpecThresh::SpecThresh(float threshold, SndObj *input, int vecsize, float sr)
  :SpecPolar(input,vecsize, sr){
  m_thresh = threshold;
  AddMsg("threshold", 41);
}

SpecThresh::~SpecThresh(){
}

int 
SpecThresh::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 41:
    SetThreshold(value);
    return 1;

  default:
    return SpecPolar::Set(mess,value);
     
  }


}

short
SpecThresh::DoProcess(){
	
  if(!m_error){
    if(m_input){ 
      if(m_enable) {  
	float a, b, max=0.f; 
	for(m_vecpos = 2; m_vecpos < m_vecsize; m_vecpos+=2){
	  a = m_input->Output(m_vecpos);
	  b = m_input->Output(m_vecpos+1);     
	  convert(&a, &b);
	  max = (max < a ? a : max);
	  m_output[m_vecpos] = a;
	  m_output[m_vecpos+1] = b;
	}
	max = (max < m_input->Output(0) ? 
	       m_input->Output(0) : max); 
	max = (max < m_input->Output(1) ? 
	       m_input->Output(1) : max); 
				
	for(m_vecpos = 2; m_vecpos < m_vecsize; m_vecpos+=2){
	  a = (m_output[m_vecpos] > max*m_thresh ?
	       m_output[m_vecpos] : 0.f);
	  b = m_output[m_vecpos+1];
	  m_output[m_vecpos] = a*cos(b);
	  m_output[m_vecpos+1] = a*sin(b);    
	}
	m_output[1] = (m_output[1] > max*m_thresh ?
		       m_output[1] : 0.f);
	m_output[0] =  (m_output[0] > max*m_thresh ?
			m_output[0] : 0.f);
      }
      else 
	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos+=2)
	  m_output[m_vecpos] = m_output[m_vecpos+1] = 0.f;
				
      return 1;
				
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;
	
}
