 
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
//  Interp.h : interface of the Interp Class
//            (interpolation object) 
//
//***********************************************************//

#ifndef _INTERP_H
#define _INTERP_H
#include "SndObj.h"

class Interp : public SndObj {

 protected:

  float m_initial; // initial value 
  float m_fin;  // fin value
  float m_typec;  // type of curve  0 = LINEAR, EXP < 0 < INV EXP
  unsigned long m_dur;
  unsigned long m_count;

 public:

  Interp();
  Interp(float initial, float fin,
	 float dur, float type = 0.f, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Interp();

  int Set(char* mess, float value);
  void SetSr(float sr);
  void  Restart(){ m_count = 0; };
  void  SetCurve(float initial, float fin, 
		 float m_typec = 0.f);
  void  SetDur(float dur){
    m_dur = (unsigned long) (m_sr*dur);
    m_count = 0;
  }
  short DoProcess();

};

#endif
