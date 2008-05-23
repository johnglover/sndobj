 
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
//
// PVBlur.h: interface for the PVBlur class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _PVBlur_H
#define _PVBlur_H


#include "SpecMult.h"

class PVBlur : public SpecMult  
{
 protected:
  float **m_frame;
  float m_time;
  int m_framenos;
  int m_hopsize;
  int m_cur;

 public:
  int Set(char* mess, float value);
  void SetBlurTime(float time);
  void SetHopsize(int hopsize){ m_hopsize = hopsize;
  SetBlurTime(m_time);
  }
  PVBlur();
  PVBlur(SndObj* input, float blurtime, int hopsize=DEF_VECSIZE, 
	 int vecsize=DEF_FFTSIZE, float sr=DEF_SR);
  ~PVBlur();
  short DoProcess();


};

#endif 
