 
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

////////////////////////////////////////////////
// Low-pass resonant filter
//
// VL, 2002
////////////////////////////////////////////////
#ifndef _Lp_H
#define _Lp_H
#include "Reson.h"


class Lp: public Reson {
 protected:

  void inline SetLPparam(float fr, float bw);

 public:

  // constructors / destructor
  Lp();
  Lp(float fr, float BW, SndObj* inObj, SndObj* inputfreq = 0, 
     SndObj* inputBW = 0, int vecisize=DEF_VECSIZE, float sr=DEF_SR);
  ~Lp();

  void SetSr(float sr){
    m_sr = sr;
    SetLPparam(m_fr, m_bw);
  }
  int Set(char* mess, float value);

  short DoProcess();
};

void Lp::SetLPparam(float fr, float bw){
  float Q = fr/bw; 
  m_b1 = (100./Q*sqrt(fr))-1.;
  m_b2 = 100./fr;
  m_a = 1 + m_b1 + m_b2;
}


#endif

