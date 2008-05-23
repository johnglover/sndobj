 
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
//  Unit.h: interface of the Unit class.                      //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _UNIT_H
#define _UNIT_H

#include "SndObj.h"

enum {UNIT_SAMPLE, UNIT_STEP, RAMP};

class Unit : public SndObj {

 protected:
  float m_amp;
  short m_mode;
  float m_step;

 public:
   
  Unit();
  Unit(float m_amp,  short mode = UNIT_SAMPLE, float step=0.f, int vecsize=DEF_VECSIZE,
       float sr = DEF_SR);
  ~Unit();

  void SetAmp(float amp){ m_amp = amp;}
  void SetStep(float step){ m_step = step;}
  void SetMode(short mode){ m_mode = mode;}

  int Set(char* mess, float value);

  short DoProcess();

};

#endif
