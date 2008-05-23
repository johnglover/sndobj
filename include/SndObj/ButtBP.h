 
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
//  ButtBP.h: interface of the ButtBP class (2nd order        //
//           butterworth band-pass filter).                   //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _ButtBP_H 
#define _ButtBP_H

#include "TpTz.h"


class ButtBP: public TpTz
 
{

 protected:

  void inline SetParam(float fr, float bw, int type);
  int m_type;

  SndObj* m_inputbw;
  SndObj* m_inputfr;

 public:

  ButtBP();
  ButtBP(float fr, float bw, SndObj* inObj, SndObj* inputfreq = 0, 
	 SndObj* inputbw = 0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);

  ~ButtBP();

  int Set(char* mess, float value);
  void SetFreq(float fr){ SetFreq(fr,m_inputfr);} 
  void SetBW(float bw){ SetBW(bw,m_inputbw);}

  void SetFreq(float fr, SndObj* InFrObj);
  void SetBW(float bw, SndObj* InBWObj);
  void SetSr(float sr){
    m_sr = sr;
    SetParam(m_fr, m_bw, m_type);
  }
  int Connect(char* mess, void* input);
  short DoProcess();

};

void ButtBP::SetParam(float fr, float bw, int type){

  double C, D;

  switch(type){

  case 1: // BP
    C = 1/(tan(PI*bw/m_sr));
    D = 2*cos((2*PI*fr)/m_sr);
    m_a = (1/(1+C));
    m_a1 = 0.f;
    m_a2 = -m_a;
    m_b1 = -(C*D*m_a);
    m_b2 = (C - 1)*m_a;
    break;

  case 2: // BR
    C = (tan(PI*bw/m_sr));
    D = 2*cos((2*PI*fr)/m_sr);
    m_a = 1/(1+C);
    m_a1 = -(D*m_a);
    m_a2 = m_a;
    m_b1 = -(D*m_a);
    m_b2 = (1 - C)*m_a;
    break;

  case 3: // HP
    C =  tan(PI*fr/m_sr);
    m_a = 1/(1 + sqrt(2.0)*C + (C*C)); // a2 = a0
    m_a1 = - 2*m_a;
    m_a2 = m_a;
    m_b1 = 2*((C*C) - 1)*m_a;
    m_b2 = (1 - sqrt(2.0)*C + (C*C))*m_a;
    break;

  case 4:
    C = 1/(tan(PI*fr/m_sr));
    m_a = 1/(1 + sqrt(2.0)*C + (C*C)); // a2 = a0
    m_a1 = 2*m_a; 
    m_a2 = m_a;
    m_b1 = 2*(1 - (C*C))*m_a;
    m_b2 = (1 - sqrt(2.0)*C + (C*C))*m_a;                  
    break;
    
  }
   
}
#endif
