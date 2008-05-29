 
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
//  ADSR.cpp: implementation of the ADSR class                //
//         Attack - Decay - Sustain - Release                 //
//         envelope, for amplitude shaping                    //
//                                                            //
//************************************************************//


#include "ADSR.h"

//////////////// CONSTRUCTION / DESTRUCTION ////////////////////

ADSR::ADSR(){
   
  Enable();
  m_att = m_maxamp = m_dec = m_sus = m_rel = 0.f;
  m_sustain = 0;
  m_count = m_dur = 0;
  AddMsg("attack", 21);
  AddMsg("decay", 22);
  AddMsg("sustain", 23);
  AddMsg("release", 24);
  AddMsg("maxamp", 25);
  AddMsg("duration", 26);
  AddMsg("go to release", 27);
  AddMsg("lock to sustain", 28);
  AddMsg("restart", 29);

}

ADSR::ADSR(float att, float maxamp, float dec, float sus, float rel,
	   float dur, SndObj* InObj, int vecsize, float sr):
  SndObj(InObj, vecsize, sr){
   
  Enable();
  m_maxamp = maxamp;
  m_sus = sus;
  m_sustain = 0;
  m_count = 0;
  m_att = att*m_sr;
  m_dec = dec*m_sr;
  m_rel = rel*m_sr;
  m_dur = (unsigned long) (dur*m_sr);
  AddMsg("attack", 21);
  AddMsg("decay", 22);
  AddMsg("sustain", 23);
  AddMsg("release", 24);
  AddMsg("maxamp", 25);
  AddMsg("duration", 26);
  AddMsg("go to release", 27);
  AddMsg("lock to sustain", 28);
  AddMsg("restart", 29);
}

ADSR::~ADSR(){  
}

////////////////// OPERATIONS ///////////////////////////////


void
ADSR::SetADSR(float att, float dec, float sus, float rel)
{
  m_att = m_sr*att;
  m_dec = m_sr*dec;
  m_sus = sus;
  m_rel = m_sr*rel;            
}

void
ADSR::SetSr(float sr){
  m_att = (sr/m_sr)*m_att;
  m_dec =  (sr/m_sr)*m_dec;
  m_rel =  (sr/m_sr)*m_rel;
  m_dur = (unsigned long) ( (sr/m_sr)*m_dur);
  m_sr = sr;
}

int 
ADSR::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetADSR(value,m_dec,m_sus,m_rel);
    return 1;

  case 22:
    SetADSR(m_att,value,m_sus,m_rel);
    return 1;

  case 23:
    SetADSR(m_att,m_dec,value,m_rel);
    return 1;

  case 24:
    SetADSR(m_att,m_dec,m_sus,value);
    return 1;

  case 25:
    SetMaxAmp(value);
    return 1;

  case 26:
    SetDur(value);
    return 1;

  case 27:
    Release();
    return 1;
	
  case 28:
    Sustain();
    return 1;

  case 29:
    Restart();
    return 1;

  case 1:
    SetSr(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}


short
ADSR::DoProcess()
{
  if(!m_error){
    float a = 0.f;
    for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
	if(m_count == m_dur) m_count=0;

	if(m_count < m_att)
	  a = (m_maxamp/m_att)*m_count;	
	if(m_count >= m_att && m_count < (m_att+m_dec)) 
	  a = ((m_sus - m_maxamp)/m_dec)*(m_count - m_att) + m_maxamp;
	if(m_count >= (m_att+m_dec) && m_count <= (m_dur - m_rel))
	  a = m_sus;
	if (m_count > (m_dur - m_rel)){ 
	  if(!m_sustain){
	    a = ((0 - m_sus)/m_rel)*(m_count - (m_dur - m_rel)) + m_sus;
	    m_count++;
	  }
	  else a = m_sus;
	}
	else m_count++;
		 
	if(m_input) 
	  m_output[m_vecpos] = m_input->Output(m_vecpos)*a;
	else m_output[m_vecpos] = a;
         
      } else m_output[m_vecpos] = 0.f ;
    }
    return 1;
  }
  return 0;
}

