 
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

#ifndef _SPECMULT_H
#define _SPECMULT_H

#include "SndObj.h"
#include "Table.h"

class SpecMult : public SndObj{

 protected:

  SndObj* m_input2;
  Table*  m_spectable;
  bool m_dynamic;

 public:

  SpecMult();
  SpecMult(SndObj* input1, SndObj* input2, int vecsize=DEF_FFTSIZE,
	   float sr=DEF_SR);
  SpecMult(Table* spectab, SndObj* input1, int vecsize=DEF_FFTSIZE,
	   float sr=DEF_SR);
  ~SpecMult();

  int Connect(char* mess, void* input);
  void SetInput2(SndObj* input2){ m_input2 = input2; m_dynamic = true; }
  void SetTable(Table *spectab) { 
    if(spectab->GetLen() >= m_vecsize){
      m_spectable = spectab;
      m_dynamic = false;
    }
  }

  short DoProcess();



};

#endif
