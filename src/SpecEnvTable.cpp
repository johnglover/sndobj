 
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


#include "SpecEnvTable.h"

SpecEnvTable :: SpecEnvTable() : m_pi(8 * atan(1.)){

  double phi = 0.f;
  double delay = (m_L-1)/2;
  double re, im;

  for(int i=2, j=2; i < m_L; i+=2, j++){
    phi = -(delay*j*2*m_pi)/m_L;
    re = m_table[i]*cos(phi);
    im = m_table[i]*sin(phi);
    m_table[i] = (float)re;
    m_table[i+1] = (float)im;
  }
}

SpecEnvTable :: SpecEnvTable(long L, int segments, float start, 
			     float* points, float* lengths, 
			     float type, float nyquistamp) :
  PVEnvTable(L,segments,start,points,lengths,type,44100.f,nyquistamp),
  m_pi(8 * atan(1.)) 
{

  double phi = 0.f;
  double delay = (m_L-1)/2;
  double re, im;

  for(int i=2, j=2; i < m_L; i+=2, j++){
    phi = -(delay*j*2*m_pi)/m_L;
    re = m_table[i]*cos(phi);
    im = m_table[i]*sin(phi);
    m_table[i] = (float)re;
    m_table[i+1] = (float)im;
  }
}


SpecEnvTable::~SpecEnvTable(){
}

short
SpecEnvTable :: MakeTable(){   
  PVEnvTable::MakeTable();

  double phi = 0.f;
  double delay = (m_L-1)/2;
  double re, im;

  for(int i=2, j=2; i < m_L; i+=2, j++){
    phi = -(delay*j*2*m_pi)/m_L;
    re = m_table[i]*cos(phi);
    im = m_table[i]*sin(phi);
    m_table[i] = (float)re;
    m_table[i+1] = (float)im;
  }

  return 1;
}

