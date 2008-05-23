 
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

// LoPassTable.cpp: implementation of the LoPassTable class.
//
//////////////////////////////////////////////////////////////////////

#include "LoPassTable.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LoPassTable::LoPassTable()
{
  m_sr = 44100.f;
  m_fr = 1000.f;
  m_L = 11;
  m_table = new float[m_L];
  MakeTable();
}

LoPassTable::~LoPassTable()
{
  delete[] m_table;

}

LoPassTable::LoPassTable(int impulsesize, float fr, float sr)
{
  m_sr = sr;
  m_fr = fr;

  // make impulsesize odd
  impulsesize = ((impulsesize/2)*2)+1;

  m_L = impulsesize;
  m_table = new float[m_L];
  MakeTable();
}


short LoPassTable::MakeTable()
{
  double Pi = TWOPI/2.;
  ZeroTable();
  for(int i = 0; i < m_L; i++){

    m_table[i] = (float) ((sin(TWOPI*(i-m_L/2.)*(m_fr/m_sr))
			   / (Pi*(i-m_L/2.)))
			  * (0.54+0.64*cos((Pi*(i-m_L/2.))/m_L)));

  }
  return 1;
}

char* LoPassTable::ErrorMessage()
{
  return "no error";
}
