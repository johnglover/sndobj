 
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
//  Phase.h: interface of the Phase class.                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _Phase_H
#define _Phase_H

#include "SndObj.h"


class Phase : public SndObj {

 protected:
  float m_freq;
  float m_offset;

 public:
   
  Phase();
  Phase(float freq, SndObj* FreqInput = 0 , float offset = 0.f,
	int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Phase();

  void SetFreq(float freq, SndObj* FreqInput = 0){
    m_freq = freq;
    m_input = FreqInput;
  }
    
  void SetPhase(float offset){ m_offset = offset; }
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  short DoProcess();

};

#endif
 
