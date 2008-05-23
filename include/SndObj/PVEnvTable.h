 
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
//  PVEnvTable.h: interface of the PVEnvTable class              //
//                                                           //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _PVEnvTable_H
#define _PVEnvTable_H

#include "Table.h"

class PVEnvTable : public Table {

 protected:
  int* m_seglen;
  float* m_segp;
  int m_segments;

  float m_typec;       // type of curve (LOG OR LINEAR)
  float m_sr;
	 
 public:
  
  void
    SetEnvelope(int segments, float start, 
		float* points, float* lengths, 
		float type, float nyquistamp=0.f);
		  
  void SetSr(float sr);
  char* ErrorMessage();
  short MakeTable();
  PVEnvTable();
  PVEnvTable(long L, int segments, float start, 
	     float* points, float* lengths,float type = 0.f, 
	     float sr=44100.f,float nyquistamp=0.f);

  ~PVEnvTable();

};

#endif
