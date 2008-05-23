 
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
//  ADSR.h: interface of the ADSR class                      //
//                                                           //
//                                                           //
//                                                           //
//***********************************************************//

#ifndef _ADSR_H 
#define _ADSR_H
 
#include "SndObj.h"


class ADSR : public SndObj{

 protected:

  unsigned long m_count; // keeps track of the time in samples
  float         m_att;   // attack time
  float         m_maxamp; // max amplitude
  float         m_dec;   // decay time
  float         m_sus;   // sustain amplitude
  float         m_rel;   // release time
  unsigned long m_dur;   // env duration
  short         m_sustain;  // sustain flag: 1= ON, 0= OFF
    
 public:

  ADSR();                            
  ADSR(float att, float maxamp, float dec, float sus, float rel,
       float dur, SndObj* InObj = 0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~ADSR();
  
  void SetSr(float sr); 
  void  SetMaxAmp (float maxamp){ m_maxamp = maxamp; }
  void  Sustain(){ m_sustain = 1; }
  void  Release(){ 
    m_sustain = 0;
    m_count = (unsigned long)(m_dur - m_rel) + 1;
  }
  void  Restart() { m_count = 0; }
  void  SetADSR(float att, float dec, float sus, float rel);
  void  SetDur(float dur){
    m_dur = (unsigned long) (m_sr*dur);
    m_count = 0;
  }  
	
  int Set(char* mess, float value);
   
  short DoProcess();           

};


#endif


