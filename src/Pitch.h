 
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
//  Pitch.h: interface of the Pitch class                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _PITCH_H
#define _PITCH_H

#include "DelayLine.h"

class Pitch : public DelayLine 
{

 protected:
  float* sintab;
  float m_pointer1;
  float m_pointer3;

  float m_pitch;
  float m_incr;

 public:
  Pitch();           
  Pitch(float delaytime, SndObj* InObj, 
	float pitch = 1.f, int vecsize=DEF_VECSIZE, float sr=DEF_SR); 
  Pitch(float delaytime, SndObj* InObj, int semitones = 0,
	int vecsize=DEF_VECSIZE, float sr=DEF_SR);
    
  ~Pitch();
  void SetPitch(float pitch){ m_pitch = pitch; }
  void SetPitch(int semitones){
    m_pitch = (float) pow(2., semitones/12.);
  }
  int Set(char* mess, float value);
  short DoProcess();       
      
};

#endif







