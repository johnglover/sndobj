 
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
//
// PVTransp.cpp: implementation of the PVTransp class.
//
//////////////////////////////////////////////////////////////////////

#include "PVTransp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PVTransp::PVTransp()
{
  m_pitch = 1.f;
  m_base = m_sr/m_vecsize;
  m_keepform = false;
  AddMsg("pitch", 31);
  AddMsg("mode", 32);
}
PVTransp::PVTransp(SndObj* input, float pitch, int mode,
		   SndObj* inpitch, 
		   int vecsize,float sr):
  SpecMult(input, inpitch, vecsize, sr){

  m_pitch =pitch;
  m_base = m_sr/m_vecsize;
  m_keepform = mode ? true : false;
  AddMsg("pitch", 31);
  AddMsg("mode", 32);
}

PVTransp::~PVTransp()
{

}

void
PVTransp::SetPitch(float pitch, SndObj* inpitch){
  m_pitch = pitch;
  m_input2 = inpitch;
}

int
PVTransp::Connect(char* mess, void* input){

  switch(FindMsg(mess)){

  case 31:
    SetPitch(m_pitch, (SndObj*) input);
    return 1;    

  default:
    return SpecMult::Connect(mess, input);

  }

}

int
PVTransp::Set(char* mess, float value){

  switch(FindMsg(mess)){

  case 31:
    SetPitch(value, m_input2);
    return 1;  
	
  case 32:
    SetMode((int)value);
    return 1;

  default:
    return SpecMult::Set(mess, value);

  }


}

short
PVTransp::DoProcess(){

  if(!m_error){
    if(m_input){
	  
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos+=2){
	m_output[m_vecpos] = 0.f;
	m_output[m_vecpos+1] = (m_vecpos/2)*m_base;
      }

      if(m_enable){	

	int chan, newchan;
	float pitch = m_pitch + (m_input2 ? m_input2->Output(0) :
				 0.f);
     
	m_output[0] = m_input->Output(0);
	m_output[1] = m_input->Output(1);

	for(m_vecpos=2,chan=1;m_vecpos < m_vecsize; m_vecpos+=2,chan++){

	  newchan = Ftoi(chan*pitch)*2; 
	  if(newchan < m_vecsize-1 && newchan > 0){
	    if(m_keepform) m_output[newchan] = m_input->Output(newchan);
	    else m_output[newchan] = m_input->Output(m_vecpos);
	    m_output[newchan+1] = m_input->Output(m_vecpos+1)*pitch;	  
	  }
	}
      }

      return 1;


    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;



}
