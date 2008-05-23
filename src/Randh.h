 
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
//  Randh.h: interface of the Randh class                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _RANDH_H 
#define _RANDH_H


#include "Rand.h"

class Randh : public Rand {

 protected:
 
  float m_fr; 
  long m_period;
  long m_count;
  SndObj* m_inputfr;
  
 public:
   
  Randh();
  Randh(float fr,float amp,SndObj* InFrObj=0,
	SndObj* InAmpObj=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Randh();

  int Connect(char* mess, void* input);
  void SetSr(float sr);
  void SetFreq(float fr, SndObj* InFrObj = 0){
  
    m_fr = fr;
    m_period = (long) (m_fr > .1 ? m_sr/m_fr : m_sr/.1); 
    m_count = m_period;
    m_inputfr = InFrObj;
         
  }
  int Set(char* mess, float value);
  short DoProcess();
  
};
#endif 


                        


