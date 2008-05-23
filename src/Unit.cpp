 
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
//  Unit.cpp: implementation of the Unit class.               //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Unit.h"

Unit::Unit(){
  m_amp = 1.f;
  m_mode = UNIT_SAMPLE;
  m_step = 0.f;

  AddMsg("mode", 21);
  AddMsg("step", 22);
  AddMsg("amplitude", 23);

}

Unit::Unit(float amp, short mode, float step, int vecsize, float sr):
  SndObj(0, vecsize, sr){
  m_amp = amp;
  m_step = step;
  m_mode = mode;

  AddMsg("mode", 21);
  AddMsg("step", 22);
  AddMsg("amplitude", 23);
}

Unit::~Unit(){
}

int
Unit::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetMode((short)value);
    return 1;

  case 23:
    SetStep(value);
    return 1;

  case 22:
    SetAmp(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}


short 
Unit::DoProcess(){
  if(!m_error){
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
	m_output[m_vecpos] = m_amp;
	if(m_mode == UNIT_SAMPLE) Disable();
	else if (m_mode == RAMP) m_amp += m_step;
      }
      else m_output[m_vecpos] = 0.f;
    }
    return 1;
  }
  else return 0;
}



