 
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
// Rand.cpp : implementation of the Rand class                //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Rand.h"
#include <time.h>

Rand::Rand(){
  m_amp = 1.f;
  m_input = 0;
  srand((unsigned)time(0));
  AddMsg("amplitude",21);
}

Rand::Rand(float amp, SndObj* InAmpObj, int vecsize, float sr):
  SndObj(InAmpObj, vecsize, sr){
  m_amp = amp;
  m_sr = sr;
  srand((unsigned)time(0));
  AddMsg("amplitude",21);
}

Rand::~Rand(){}


///////////// OPERATIONS ////////////////////////////////////////
int 
Rand::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetAmp(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}

int 
Rand::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 21:
    m_input = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }


}
short
Rand :: DoProcess(){ 
  if(!m_error){
    float amp;
    for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){
      if(m_enable){
	amp = m_amp + (m_input== 0 ? 0 : m_input->Output(m_vecsize));
	m_output[m_vecpos] = (((float)rand() - MAXR)/MAXR)*amp;
      }

      else { m_output[m_vecpos] = 0.f; }
    }
    return 1;
  }
  else return 0;
}
