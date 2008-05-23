 
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
//  Ap.h: interface of the Ap class (2nd order        //
//           butterworth band-pass filter).                   //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _AP_H 
#define _AP_H

#include "TpTz.h"


class Ap: public TpTz
 
{

 protected:

  void inline SetAPParams(float fr, float R);
  SndObj* m_inputR;
  SndObj* m_inputfr;

 public:

  Ap();
  Ap(float fr, float R, SndObj* inObj, SndObj* inputfreq = 0, 
     SndObj* inputR=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);

  ~Ap();

  void SetFreq(float fr, SndObj* InFrObj);
  void SetR(float r, SndObj* InRObj=0);
  void SetSr(float sr){
    m_sr = sr;
    SetAPParams(m_fr, m_bw);
  }

  int Set(char* mess, float value);
  int Connect(char* mess, void* input);

  short DoProcess();
  char* ErrorMessage();
};

void 
Ap::SetAPParams(float fr, float R){
  R= 1.f/R;
  double thecos = cos((2*PI*fr)/m_sr); 
  m_a1 = -2*R*thecos;
  m_a2 = R*R;
  m_b1 = (-2/R)*thecos;
  m_b2 = 1/m_a2;
  m_a = 1;
}

#endif
