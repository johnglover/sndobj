 
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
//  StringFlt.cpp: Implementation of the StringFlt Object    //
//                                                           //
//                                                           //
//                                                           //
//***********************************************************//

#include "StringFlt.h"

//////////CONSTRUCTION /////////////////////

StringFlt::StringFlt(){
	
  m_vdtime = 0.f;
  m_decay = 0.f;
  m_fdbgain = 0.f;
  m_fr = 0.f;
  m_a = 0.f;
  m_delaytime = .05f;
  m_size = (long) 2205;
  if(!(m_delay = new float[m_size])){
    m_error = 13;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  m_s = 0.5f;
  m_APDelay = m_LPDelay = 0.f;
  Reset();
	
  AddMsg("feedback gain", 31);
  AddMsg("frequency", 32);
  AddMsg("decay factor", 33);
	
}

StringFlt::StringFlt(float fr, float fdbgain, SndObj* inObj, 
		     SndObj* InFrObj, int vecsize, float sr) :
  DelayLine(.05f, inObj, vecsize, sr)
{
	
  m_decay = 0.f;
  m_inputfr = InFrObj;
  m_fr = fr;
  if(fr && fr < 20) m_fr = 20.f;
	
  m_s = 0.5f;
  float tdelay = m_sr/m_fr;     
  int delay = (int)tdelay;
  delay = ((delay+m_s) > (tdelay) ? delay - 1: delay);
  float fracdelay = (tdelay  - (delay + m_s));
  m_vdtime = m_size - tdelay;
  m_a = (1-fracdelay)/(1+fracdelay);
	
	
  m_rpointer = 0;
  m_fdbgain = fdbgain;
	
  m_APDelay = m_LPDelay = 0.f;
	
  AddMsg("feedback gain", 31);
  AddMsg("frequency", 32);
  AddMsg("decay factor", 33);
	
}

StringFlt::StringFlt(float fr, SndObj* inObj, float decay, 
		     SndObj* InFrObj, int vecsize, float sr) :
  DelayLine(.05f, inObj, vecsize, sr)
{
  m_s = 0.5f;
  m_inputfr = InFrObj;
  m_fr = fr;
  if(fr && fr < 20) m_fr = 20.f;
	
  m_decay = decay;
	
  double gf = pow(10., (double)(-m_decay/(20*m_fr)));
  double g = cos(PI*fr/m_sr);
	
  if(gf <= g) m_fdbgain = gf/g;
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
	   
  float tdelay = m_sr/m_fr;     
  int delay = (int)tdelay;
  delay = ((delay+m_s) > (tdelay) ? delay - 1: delay);
  float fracdelay = (tdelay  - (delay + m_s));
  m_vdtime = m_size - tdelay;
  m_a = (1-fracdelay)/(1+fracdelay);
	
  m_rpointer = 0;	
  m_APDelay = m_LPDelay = 0.f;
	
  AddMsg("feedback gain", 31);
  AddMsg("frequency", 32);
  AddMsg("decay factor", 33);
	
}


StringFlt::~StringFlt()
{
	
}

//////////////////OPERATIONS //////////////////////
void StringFlt::SetDecay(float decay){
	
  m_decay = decay;
  double gf = pow(10., (double)(-m_decay/(20*m_fr)));
  double g = cos(PI*m_fr/m_sr);
	
  if(gf <= g) m_fdbgain = gf/g;
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
	   
  float tdelay = m_sr/m_fr;     
  int delay = (int)tdelay;
  delay = ((delay+m_s) > (tdelay) ? delay - 1: delay);
  float fracdelay = (tdelay  - (delay + m_s));
  m_vdtime = m_size - tdelay;
  m_a = (1-fracdelay)/(1+fracdelay);
}


void
StringFlt::SetSr(float sr){
  m_sr = sr;
  if(m_decay){
    double gf = pow(10., (double)(-m_decay/(20*m_fr)));
    double g = cos(PI*m_fr/m_sr);
		
    if(gf <= g) m_fdbgain = gf/g;
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
  } else m_s = 0.5f;	   
  float tdelay = m_sr/m_fr;
  int delay = (int)tdelay;
  delay = ((delay+m_s) > (tdelay) ? delay - 1: delay);
  // delay = (int)(tdelay - .5); 
  // fracdelay = (tdelay  - (delay +.5f));
	
  float fracdelay = (tdelay  - (delay + m_s));
  m_vdtime = m_size - tdelay;
  m_a = (1-fracdelay)/(1+fracdelay);
	
	
	
  if(m_delay)delete[] m_delay;
  if(!(m_delay = new float[m_size])){
    m_error = 13;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
  }
  return;
}


void
StringFlt::SetFreq(float fr, SndObj* InFrObj){
  m_fr = fr;     
  if(fr < 20)m_fr = 20.f;  
  m_inputfr = InFrObj;  
	
  if(m_decay){
    double  gf = pow(10., (double)(-m_decay/(20*m_fr)));
    double  g = cos(PI*m_fr/m_sr);
		
    if(gf <= g) m_fdbgain = gf/g;
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
  } else m_s = 0.5f;
  float tdelay = m_sr/m_fr;
  int delay = (int)tdelay;
  delay = ((delay+m_s) > (tdelay) ? delay - 1: delay);
  // delay = (int)(tdelay - .5); 
  // fracdelay = (tdelay  - (delay +.5f));
	
  float fracdelay = (tdelay  - (delay + m_s));
  m_vdtime = m_size - tdelay;
  m_a = (1-fracdelay)/(1+fracdelay);
	
	
	
}


int
StringFlt::Set(char* mess, float value){
	
  switch (FindMsg(mess)){
		
  case 31:
    SetFdbgain(value);
    return 1;
		
  case 32:
    SetFreq(value);
    return 1;
		
  case 33:
    SetDecay(value);
    return 1;
		
  case 1:
    SetSr(value);
    return 1;
		
  default:
    return DelayLine::Set(mess,value);
		
  }
	
	
}

int
StringFlt::Connect(char* mess, void* input){
	
  switch (FindMsg(mess)){
		
  case 32:
    m_inputfr = (SndObj *) input;
    return 1;
		
  default:
    return SndObj::Connect(mess,input);
		
  }
	
	
}


short
StringFlt::DoProcess(){
  if(!m_error){
    if(m_input){
      float fr, pos, tdelay, fracdelay, w, y, output;
      float g, gf;
      int delay;
      for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){
	if(m_enable){
	  if(m_inputfr){
	    fr = m_fr + m_inputfr->Output(m_vecpos);
	    if(fr < 20.f) fr = 20.f;
	    tdelay = m_sr/fr;
						
	    if(m_decay){
	      gf = pow(10., (double)(-m_decay/(20*m_fr)));
	      g = cos(PI*fr/m_sr);
							
	      if(gf <= g) m_fdbgain = gf/g;
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
	  w = GetSample(pos) + m_input->Output(m_vecpos);
	  y = m_LPDelay*(1-m_s) + w*m_s;
	  m_LPDelay = w;
	  output = m_APDelay + y*(m_a);
	  m_APDelay = y + output*(-m_a);
	  PutSample(output*m_fdbgain); 
	  m_output[m_vecpos] = output;  
					
	} 
	else m_output[m_vecpos] = 0.f;
      }
      return 1;
    }
    else { m_error =11;
    return 0;
    }
  }
  else return 0;
}











