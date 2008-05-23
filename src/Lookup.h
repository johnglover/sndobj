 
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

//*******************************************************//
//     Lookup.h : interface of the Lookup class
//                  truncated table lookup 
//
//*******************************************************//

#ifndef _LOOKUP_H
#define _LOOKUP_H

#include "SndObj.h"
#include "Table.h"

enum { RAW_VALUE=0, NORMALISED};
enum { LIMIT=0, WRAP_AROUND};

class Lookup : public SndObj {

 protected:

  Table* m_ptable;         // reference to a Table obj    
  
  long m_offset;
  long m_size; 
  int m_mode;
  int m_normal;

 public:
  Lookup();
  Lookup(Table* table, long offset, SndObj* InObj, 
	 int mode = WRAP_AROUND,
	 int normal=RAW_VALUE, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  void SetMode(int mode, int normal){ m_mode = mode; m_normal = normal; }
  ~Lookup();
  void Offset(long offset){ m_offset = offset; }  
  void SetTable(Table* table);

  int Set(char* mess, float value);
  int Connect(char* mess, void* input);

  short DoProcess();
  
};

#endif
