 
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

//*******************************************************//
//     Lookupi.cpp : implementation of the Lookup object
//                  interpolated table lookup 
//
//
//*******************************************************//

#include "Lookupi.h"

//////////////// CONSTRUCTION / DESTRUCTION ////////////////
Lookupi::Lookupi(){
}

Lookupi::Lookupi(Table* table, long offset, SndObj* InObj, int mode,
		 int normal,int vecsize, float sr):
  Lookup(table, offset, InObj, mode, normal, vecsize, sr)
{ }

Lookupi::~Lookupi(){

}
/////////// OPERATIONS ////////////////////////////////

short
Lookupi::DoProcess(){
  if(!m_error){
    if(m_ptable && m_input){ 
      float i; int ps;
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
	if(m_enable){ 
	  i = m_input->Output(m_vecpos);
	  if(m_normal) i *= m_size; // if normalised 
	  // modulus
	  if(m_mode){
	    while(i >= m_size)
	      i -= m_size;        
	    while (i < 0)
	      i += m_size;
	  }
	  else if(i >= m_size || i > 0) 
	    i = (i >= m_size) ? m_size - 1.f : 0.f;
	  // interpolating lookup :
	  ps = Ftoi(i);
	  m_output[m_vecpos] = m_ptable->GetTable()[ps] +      
	    ((m_ptable->GetTable()[ps] - 
	      m_ptable->GetTable()[ps+1])*(ps - i)); 
	}
	else m_output[m_vecpos] =  0.f;
      }
      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;		  
}  



