 
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

#ifndef _PVMask_H
#define _PVMask_H

#include "SpecInterp.h"

class PVMask : public SpecInterp {
	
 protected:
  float   m_maskgain;

 public:

  PVMask();
  PVMask(float maskgain, SndObj* input, SndObj* mask,
	 SndObj* inmaskgobj=0, int vecsize=DEF_FFTSIZE,
	 float sr=DEF_SR);
  PVMask(float maskgain, Table* masktable, SndObj* input,
	 SndObj* inmaskgobj=0, int vecsize=DEF_FFTSIZE,
	 float sr=DEF_SR );
  ~PVMask();

  int Connect(char* mess, void* input);
  int Set(char* mess, float value);

  void SetMaskInput(SndObj* mask){ SetInput2(mask);}
  void SetMaskTable(Table *mask) { SetTable(mask);}

  void SetMaskGain(float maskgain, SndObj* inmaskg=0){
    m_maskgain = maskgain;
    m_interpobj = inmaskg;
  }

  short DoProcess();

};

#endif
