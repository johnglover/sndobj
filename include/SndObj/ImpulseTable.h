 
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
//  ImpulseTable.h: interface of the ImpulseTable class       //
//                                                           //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _ImpulseTable_H
#define _ImpulseTable_H

#include "SpecEnvTable.h"
#include <rfftw/rfftw.h>

class ImpulseTable : public SpecEnvTable {
 protected:
  Table*  m_window;
  rfftw_plan m_plan; // FFTW initialisation
  float* m_ffttmp;
 public:
		
  void SetWindow(Table* window){
    m_window = window->GetLen() == m_L ? window : 0;
    MakeTable();
  }
  short MakeTable();
  ImpulseTable();
  ImpulseTable(long L,
	       int segments, float start, 
	       float* points, float* lengths,float type = 0.f,
	       Table* window=0,
	       float nyquistamp=0.f);
  
  ~ImpulseTable();

};

#endif
