 
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

// LoPassTable.h: interface for the LoPassTable class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _LOPASSTABLE_H
#define _LOPASSTABLE_H



#include "Table.h"


class LoPassTable : public Table  
{	
 protected:

  float m_fr;
  float m_sr;
 public:
  char* ErrorMessage();
  short MakeTable();
        
  void SetFreq(float fr) { m_fr=fr ; }
  void SetSr(float sr) { m_sr =sr; }
        
  LoPassTable(int impulsesize, float fr, float sr=44100);
  LoPassTable();
  virtual ~LoPassTable();

};

#endif 
