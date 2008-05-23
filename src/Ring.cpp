 
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
//  Ring.cpp: implementation of the Ring class                //
//           (ring modulator)                                 //
//                                                            //
//                                                            //
//************************************************************//


#include "Ring.h"

//////////////// CONSTRUCTION / DESTRUCTION ////////////////////

Ring::Ring(){
  m_input2 = 0;
  AddMsg("input 2", 21);
}

Ring::Ring(SndObj* InObj1, SndObj* InObj2, int vecsize, float sr):
  SndObj(InObj1, vecsize, sr) {
  m_input2 = InObj2;
  AddMsg("input 2", 21);
}

Ring::~Ring(){
}

////////////////// OPERATIONS ///////////////////////////////
int
Ring::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    m_input2 = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }


}

short
Ring::DoProcess(){
  if(!m_error){
    if(m_input2 && m_input){ 
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
	if(m_enable){
	  m_output[m_vecpos] = (m_input->Output(m_vecpos))*(m_input2->Output(m_vecpos));
	}
	else { 
	  m_output[m_vecpos] = 0.f ;
	}

      }
      return 1;
    }
    else {
      m_error = 3;
      return 0;
    }  
  }
  else return 0;
}



