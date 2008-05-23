 
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

#include "SpecCart.h"

SpecCart::SpecCart(){
}

SpecCart::SpecCart(SndObj *input, int vecsize, float sr)
  :SpecMult(input, 0, vecsize, sr){
}

SpecCart::~SpecCart(){
}


short
SpecCart::DoProcess(){

  if(!m_error){
    if(m_input){
      float a, b;
      for(m_vecpos = 1; m_vecpos < m_vecsize; m_vecpos+=2) {
		 
	// every complex pair except 0 and nyquist
	if(m_enable) {     
	  // convert 
	  a = m_input->Output(m_vecpos); 	               
	  b  = m_input->Output(m_vecpos+1);
	  convert(&a, &b);
	  m_output[m_vecpos] = a; 
	  m_output[m_vecpos+1] = b;
	}
	else 
	  m_output[m_vecpos+1] = m_output[m_vecpos] = 0.f;
      } 
      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;

}
