 
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
//  Rand.h: interface of the Rand class                       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _RAND_H 
#define _RAND_H

#include "SndObj.h"
#include <stdlib.h>

const float MAXR = float(RAND_MAX/2);



class Rand : public SndObj {

 protected:
  
  float m_amp;
  
 
 public:
   
  Rand();
  Rand(float amp, SndObj* InAmpObj = 0, int vecsize=DEF_VECSIZE, 
       float sr = DEF_SR);
  ~Rand();  
  
  void SetAmp(float amp, SndObj* InAmpObj = 0){ 
    m_amp = amp;
    m_input = InAmpObj;
  }
  
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  short DoProcess();
  
};

#endif






