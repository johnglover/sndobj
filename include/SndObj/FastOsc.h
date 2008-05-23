 
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
// and licensing informationc

#ifndef _FASTOSC_H
#define _FASTOSC_H

#include "SndObj.h"
#include "Table.h"

const long phasemask = 0x0FFFFFFL;
const long maxlength = 0x1000000L;

class FastOsc : public SndObj {

 protected:

 long m_phase;
 long m_size;
 float m_factor;
 long m_lobits;
 float m_amp;
 float m_fr;
 
 Table* m_ptable;


 public:

 FastOsc();
 FastOsc(Table* table, float fr, float amp, 
	 int vecsize=DEF_VECSIZE, float sr=DEF_SR);
 ~FastOsc();

 void SetFreq(float fr) { m_fr = fr;}
 void SetAmp(float amp) { m_amp = amp;}
 void SetPhase(float phase){m_phase = (long)(maxlength*phase);}
 virtual void SetTable(Table* table); 
 int Set(char* mess, float value);
 int Connect(char* mess, void* input);
 void SetSr(float sr);

 short DoProcess();

};

#endif
