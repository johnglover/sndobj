 
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
//  PVTable.h: interface of the PVTable class              //
//                                                          //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _PVTable_H
#define _PVTable_H

#include "Table.h"
#include "SndIn.h"
#include "PVA.h"
#include "SndFIO.h"

class PVTable : public Table {
 protected:
  double* m_amps;
  double* m_freqs;
  SndFIO* m_file;
  SndIn* m_in;
  PVA* m_analysis;
  unsigned long m_framecount;
  float m_start;
  unsigned long m_end;
  int m_vecsize;
  float m_sr;

 public:
		  
  void SetTable(SndFIO* soundfile, Table* window, 
		float start, float end);
  short MakeTable();
  PVTable();
  PVTable(int L, SndFIO* soundfile, Table* window, 
	  float start, float end);

  ~PVTable();
  char*
    ErrorMessage();
};

#endif
