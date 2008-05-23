 
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

#ifndef _SPECINTERP_H
#define _SPECINTERP_H

#include "SpecMult.h"


class SpecInterp : public SpecMult {
	
 protected:

  float   m_offset;
  SndObj* m_interpobj;

 public:

  SpecInterp();
  SpecInterp(float i_offset, SndObj* input1, SndObj* input2,
	     SndObj* interpobj=0, int vecsize=DEF_FFTSIZE,
	     float sr=DEF_SR);
  ~SpecInterp();

  int Connect(char* mess, void* input);
  int Set(char* mess, float value);
  void SetInterp(float i_offset, SndObj* interpobj=0){
    m_offset = i_offset;
    m_interpobj = interpobj;
  }

  short DoProcess();

};

#endif
