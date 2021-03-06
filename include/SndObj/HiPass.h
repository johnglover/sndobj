 
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
// Copyright (c)Rory Walsh May 2003  
// See License.txt for a disclaimer of all warranties
// and licensing information

//*************************************************************//
// HiPass.h : 1st order high pass filter                       //
//                                			      //
//         Rory Walsh May 2003   			      //
//                                          		      //
//*************************************************************//
#ifndef _HIPASS_H 
#define _HIPASS_H

#include "LowPass.h"


class HiPass : public LoPass
 
{
 protected:


 public:

  HiPass();
  HiPass(float freq, SndObj* inObj, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~HiPass();

  void SetFreq(float fr){
    m_fr = fr;
    double  C = 2 - cos(2*PI*m_fr/m_sr);	
    m_b1 = C - sqrt((C*C) - 1); 
    m_a = 1 - m_b1;
  }

  void SetSr(float sr){
    m_sr = sr;
    double  C = 2 - cos(2*PI*m_fr/m_sr);	
    m_b1 = C - sqrt((C*C) - 1); 
    m_a = 1 - m_b1;	
  }

  int Set(char* mess, float value);

};

#endif
