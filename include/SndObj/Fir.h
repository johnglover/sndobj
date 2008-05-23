 
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

#ifndef _FIR_H
#define _FIR_H

#include "DelayLine.h"
#include "Table.h"

class FIR : public DelayLine {

 protected:
  Table*   m_table;
  bool     m_newtable;      

 public:
  int Connect(char* mess, void* input);
  int Set(char* mess, float value);
  FIR();
  FIR(Table* coeftable, SndObj* input, 
      int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  FIR(float* impulse, int impulsesize, SndObj* input, 
      int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~FIR();

  void SetTable(Table* coeftable){ m_table = coeftable; m_newtable = false;
  SetDelayTime(m_table->GetLen()/m_sr);}
  void SetImpulse(float* impulse, int impulsesize);
  void SetDelayTime(float dtime){
    if(m_newtable) DelayLine::SetDelayTime(dtime);
    else return;
  }

  short DoProcess();

};

#endif
