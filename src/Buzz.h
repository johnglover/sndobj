 
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

#ifndef _BUZZ_H
#define _BUZZ_H

#include "SndObj.h"
#include "HarmTable.h"
#include "Oscili.h"

class Buzz : public SndObj {

 protected:

  
  HarmTable* m_ptable;         // reference to a Table obj

  Oscili* oscil1;
  Oscili* oscil2; 

  float m_fr; 
  float m_amp;
  short m_harm; 
  
  SndObj* m_inputamp;  

 public:
  Buzz();  
  Buzz(float fr, float amp, short harms, SndObj* InFrObj=0,
       SndObj* InAmpObj=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Buzz();
  void SetFreq(float fr, SndObj* InFrObj=0);
  void SetAmp(float amp, SndObj* InAmpObj=0){
    m_amp = amp;
    m_inputamp = InAmpObj;
  }
  void SetSr(float sr);
  void SetHarm(int harm);
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  char* ErrorMessage();
  short DoProcess();
  
};

#endif

