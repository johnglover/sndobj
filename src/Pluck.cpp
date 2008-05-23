 
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
//  Pluck.cpp: Implementation of the Pluck Object            //
//                                                           //
//                                                           //
//                                                           //
//***********************************************************//

#include "Pluck.h"

//////////CONSTRUCTION /////////////////////

Pluck::Pluck(){ 
	
  m_inputfr = 0;
  m_amp = 1.f;
  m_fr= 440.f;
  m_maxscale = 32767.f;
	
  m_s = 0.5f;
  float tdelay = m_sr/m_fr;     
  int delay = (int)tdelay;
  delay = ((delay+m_s) > (tdelay) ? delay - 1: delay);
  float fracdelay = (tdelay  - (delay + m_s));
  m_vdtime = m_size - tdelay;
  m_a = (1-fracdelay)/(1+fracdelay);
	
  m_input = new Randh((m_amp*10000.f/m_maxscale), m_amp, 0, 0, 1, m_sr);
  m_fdbgain = 0.9f;
	
  AddMsg("amplitude", 41);
  AddMsg("maxscale", 42);
  AddMsg("repluck", 43);
	
} 

Pluck::Pluck(float fr, float amp, float fdbgain, 
	     SndObj* InFrObj, float maxscale, int vecsize, float sr)
  :StringFlt(fr, fdbgain, 0, InFrObj, vecsize, sr)
{
	
  m_amp = amp;
  m_maxscale = maxscale;
  m_input = new Randh((m_amp*10000.f/m_maxscale), m_amp, 0, 0, 1, m_sr);
  FillDelay();
  AddMsg("amplitude", 41);
  AddMsg("maxscale", 42);;
  AddMsg("repluck", 43);
}

Pluck::Pluck(float fr, float amp, SndObj* InFrObj, 
	     float decay, float maxscale, int vecsize, float sr)
  :StringFlt(fr, 0, decay, InFrObj, vecsize, sr)
{
	
  m_amp = amp;
  m_maxscale = maxscale;
  m_input = new Randh((m_amp*10000.f/m_maxscale), m_amp, 0, 0, 1, m_sr);
  FillDelay();
  AddMsg("amplitude", 41);
  AddMsg("maxscale", 42);;
  AddMsg("repluck", 43);
}



Pluck::~Pluck()
{
  delete m_input;
}

//////////////////OPERATIONS //////////////////////
void
Pluck::FillDelay(){
  for(int n=0; n< m_size;n++){
    m_input->DoProcess();
    PutSample(m_input->Output(0));
  }
  m_wpointer = 0;
}

int
Pluck::Set(char* mess, float value){
	
  switch (FindMsg(mess)){
		
  case 41:
    SetAmp(value, m_maxscale);
    return 1;
		
  case 42:
    SetAmp(m_amp, value);
    return 1;
		
  case 43:
    RePluck();
    return 1;
		
		
  default:
    return StringFlt::Set(mess,value);
		
  }
	
	
}
void 
Pluck::RePluck(){
  Disable();
  FillDelay();
  Enable();
}

short
Pluck::DoProcess(){
	
  if(!m_error){
		
    float fr, pos, tdelay, fracdelay, w, s, output;
    float g, gf;
    int delay;
    for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){
      if(m_enable){
				
	/*if(m_inputfr){
	  fr = m_fr + m_inputfr->Output(m_vecpos);
	  if(fr < 20.f) fr = 20.f;
	  tdelay = m_sr/fr;
	  delay = (int)(tdelay - .5);
	  fracdelay = (tdelay  - (delay +.5f));
	  m_vdtime = m_size - tdelay;
	  m_a = (1-fracdelay)/(1+fracdelay);
	  } */

	if(m_inputfr){
	  fr = m_fr + m_inputfr->Output(m_vecpos);
	  if(fr < 20.f) fr = 20.f;
	  tdelay = m_sr/fr;
						
	  if(m_decay){
	    gf = pow(10., (double)(-m_decay/(20*m_fr)));
	    g = cos(PI*fr/m_sr);
							
	    if(gf < g) m_fdbgain = gf/g;
	    else {
	      double a,b,c,d,s1,s2;
	      double icosfun = cos(2*PI*m_fr/m_sr);
	      a = 2 - 2*icosfun;
	      b = 2*icosfun - 2;
	      c = 1 - gf*gf ;
	      d = sqrt(b*b - 4*a*c);
	      s1 = (-b + d)/(a*2);
	      s2 = (-b - d)/(a*2);
	      m_s = (s1 < s2 ? s1 : s2);
	    }
	  }
						
	  delay = Ftoi(tdelay);
	  delay = ((delay+m_s) > (tdelay) ? delay - 1: delay);
	  // delay = (int)(tdelay - .5); 
	  // fracdelay = (tdelay  - (delay +.5f));
						
	  fracdelay = (tdelay  - (delay + m_s));
	  m_vdtime = m_size - tdelay;
	  m_a = (1-fracdelay)/(1+fracdelay);
						
	} 
				
	pos = m_wpointer + m_vdtime;
	while(pos >= m_size) pos -= m_size;
	while(pos < 0) pos += m_size;
				
	w = GetSample(pos); 
	s = m_LPDelay*(1-m_s) + w*m_s;
	m_LPDelay = w;
	output = m_APDelay + s*(m_a);
	m_APDelay = s + output*(-m_a);
	PutSample(output*m_fdbgain); 
	m_output[m_vecpos] = output;  
      } 
      else m_output[m_vecpos] = 0.f;
    }
    return 1;
  }
  else return 0;
	
}










