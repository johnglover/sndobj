 
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

//***********************************************************//
//  VDelay.cpp: Implementation of the VDelay Object          //
//                (variable delay line)                      //
//                                                           //
//                                                           //
//***********************************************************//
#include "stdio.h"
#include "VDelay.h"
//////////CONSTRUCTION /////////////////////

VDelay::VDelay(){

  Enable();
  m_vrpointer = 0.0;
  m_vdtime = 0.f;
  m_inputvdt= 0;
  m_fdbgain = 0.f;
  m_fwdgain = 0.f;
  m_dirgain = 0.f;
  m_inputfdbg = 0;
  m_inputfwdg = 0;
  m_inputdirg = 0;

  AddMsg("delaytime", 31);
  AddMsg("maxdelaytime", 32);
  AddMsg("direct gain", 33);
  AddMsg("feedback gain", 34);
  AddMsg("feedforward gain", 35);

}

VDelay::VDelay(float maxdelaytime, float fdbgain, float fwdgain, 
	       float dirgain, SndObj* InObj, SndObj* InVdtime, 
	       SndObj* InFdbgain, SndObj* InFwdgain, SndObj* InDirgain,
	       int vecsize, float sr)
  : DelayLine(maxdelaytime, InObj, vecsize, sr){ 


  m_wpointer = 0;
  m_vrpointer = (m_size/2.);
  m_vdtime = m_vrpointer/m_sr;
  m_inputvdt = InVdtime;
  m_fdbgain = fdbgain;
  m_fwdgain = fwdgain;
  m_dirgain = dirgain;
  m_inputfdbg = InFdbgain;
  m_inputfwdg = InFwdgain;
  m_inputdirg = InDirgain;

  AddMsg("delaytime", 31);
  AddMsg("maxdelaytime", 32);
  AddMsg("direct gain", 33);
  AddMsg("feedback gain", 34);
  AddMsg("feedforward gain", 35);

}

VDelay::VDelay(float maxdelaytime, float delaytime, float fdbgain, float fwdgain, 
	       float dirgain, SndObj* InObj, SndObj* InVdtime, 
	       SndObj* InFdbgain, SndObj* InFwdgain, SndObj* InDirgain,
	       int vecsize, float sr)
  : DelayLine(maxdelaytime, InObj, vecsize, sr){ 


  m_wpointer = 0;
  m_vrpointer = (maxdelaytime - delaytime)*m_sr;
  m_vdtime = delaytime;
  m_inputvdt = InVdtime;
  m_fdbgain = fdbgain;
  m_fwdgain = fwdgain;
  m_dirgain = dirgain;
  m_inputfdbg = InFdbgain;
  m_inputfwdg = InFwdgain;
  m_inputdirg = InDirgain;
  AddMsg("delaytime", 31);
  AddMsg("maxdelaytime", 32);
  AddMsg("direct gain", 33);
  AddMsg("feedback gain", 34);
  AddMsg("feedforward gain", 35);



}


VDelay::~VDelay()
{ }

//////////////////OPERATIONS //////////////////////
int 
VDelay::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 31:
    SetDelayTime(value);
    return 1;

  case 32:
    SetMaxDelayTime(value);
    return 1;

  case 33:
    SetDirgain(value);
    return 1;

  case 34:
    SetFdbgain(value);
    return 1;

  case 35:
    SetFwdgain(value);
    return 1;


  default:
    return SndObj::Set(mess,value);
     
  }


}

int 
VDelay::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 31:
    m_inputvdt = (SndObj *) input;
    return 1;

  case 33:
    m_inputdirg = (SndObj *) input;
    return 1;

  case 34:
    m_inputfdbg = (SndObj *) input;
    return 1;

  case 35:
    m_inputfwdg = (SndObj *) input;
    return 1;


  default:
    return SndObj::Connect(mess,input);
     
  }


}


short
VDelay::DoProcess(){

  if(!m_error) {
    if(m_input){ 
      float dir, w, del, pos, fdbgain, fwdgain, dirgain, vdsamp;
      for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){
	if(m_enable){
	  fdbgain = m_fdbgain + (m_inputfdbg == 0 ? 0 : m_inputfdbg->Output(m_vecpos));
	  fwdgain = m_fwdgain + (m_inputfwdg == 0 ? 0 : m_inputfwdg->Output(m_vecpos));
	  dirgain = m_dirgain + (m_inputdirg == 0 ? 0 : m_inputdirg->Output(m_vecpos));
	  vdsamp = (m_vdtime  + (m_inputvdt == 0 ? 0 : m_inputvdt->Output(m_vecpos)))*m_sr;

      
	  if(vdsamp < 0) vdsamp = 0;
	  else if (vdsamp > m_size) vdsamp = m_size;

	  pos = m_wpointer - vdsamp;
    
	  while(pos > m_size) pos -= m_size;
	  while(pos < 0) pos += m_size;
   
	  dir = m_input->Output(m_vecpos);
	  del = GetSample(pos);
	  w = dir + fdbgain*del;
	  PutSample(w);
	  m_output[m_vecpos] = w + fwdgain*del + dir*dirgain;
	}
	else m_output[m_vecpos] = 0.f;
      }
      return 1;
    }
    else {
      m_error = 11;
      return 0;
    }
  }

  else return 0;
}









