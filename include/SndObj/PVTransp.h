 
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
// PVTransp.h: interface for the PVTransp class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _PVTRANSP_H
#define _PVTRANSP_H

enum { NORMAL_TRANSP=0, KEEP_FORMANT};

#include "SpecMult.h"

class PVTransp : public SpecMult  
{
 protected:
  float m_base;
  float m_pitch;
  float m_keepform;

 public:
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  void SetPitch(float pitch, SndObj* inpitch=0);
  void SetMode(int mode){ m_keepform= mode ? true : false;}
  PVTransp();
  PVTransp(SndObj* input, float pitch, int mode=NORMAL_TRANSP,
	   SndObj* inpitch=0, 
	   int vecsize=DEF_FFTSIZE, float sr=DEF_SR);
  ~PVTransp();
  short DoProcess();


};

#endif 
