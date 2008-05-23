 
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
//  IADSR.h: interface of the IADSR class                    //
//      ADSR with user-defined init and end values           //
//                                                           //
//                                                           //
//***********************************************************//

#ifndef _IADSR_H 
#define _IADSR_H
 
#include "ADSR.h"

class IADSR : public ADSR{

 protected:

  float m_init;
  float m_end;

 public:

  IADSR();                            
  IADSR(float init, float att, float maxamp, float dec, float sus, 
	float rel, float end, float dur, SndObj* InObj = 0, int vecsize=DEF_VECSIZE,
	float sr=DEF_SR);
  ~IADSR();
  
  void SetInit(float init){ m_init = init;}
  void SetEnd(float end){ m_end = end; }
    
  int Set(char* mess, float value);

  short DoProcess();           // change gain

};


#endif


