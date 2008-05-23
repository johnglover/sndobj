 
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

#include "EnvTable.h"

EnvTable :: EnvTable(){

  m_L = 512;
  m_segments = 1;
  m_seglen = new int[1];
  m_seglen[0] = 512;
  m_segp = new float[2];
  m_segp[0] = 0.f;
  m_segp[1] = 1.f;

  m_typec = 0.f;
  m_table = new float[m_L+1];

  MakeTable();

}


EnvTable :: EnvTable(long L, int segments, float start, 
		     float* points, float* lengths, 
		     float type){
  int i;
  m_L = L;
  m_typec = type;
  m_segments = segments;
  m_segp = new float[m_segments+1];
  m_seglen = new int[m_segments];
  if( (m_segp[0] = start) <=0.f
      && m_typec != 0.f)
    m_segp[0] = 0.00000001f;

  for(i=0; i < segments; i++){
    if( (m_segp[i+1] = points[i]) <= 0.f
	&& m_typec != 0.f)
      m_segp[i+1] = 0.00000001f;	
  }

  float total=0;
  for(i=0; i < segments; i++)
    total += lengths[i];

  for(i=0; i < segments; i++)
    m_seglen[i] = (int) (m_L*lengths[i]/total);


  m_table = new float [m_L+1];
  MakeTable();

}

void
EnvTable::SetEnvelope(int segments, float start, 
		      float* points, float* lengths, 
		      float type)

{
  int i;
  m_typec = type;
  m_segments = segments;
  m_segp = new float[m_segments+1];
  m_seglen = new int[m_segments];
  if( (m_segp[0] = start) <=0.f
      && m_typec != 0.f)
    m_segp[0] = 0.00000001f;

  for(i=0; i < segments; i++){
    if( (m_segp[i+1] = points[i]) <= 0.f
	&& m_typec != 0.f)
      m_segp[i+1] = 0.00000001f;	
  }

  float total=0;
  for(i=0; i < segments; i++)
    total += lengths[i];

  for(i=0; i < segments; i++)
    m_seglen[i] = (int) (m_L*lengths[i]/total);


  MakeTable();
}

EnvTable::~EnvTable(){

  delete[] m_table;
  delete[] m_segp;
  delete[] m_seglen;

}


short
EnvTable :: MakeTable(){   
  int i, j, tpos;
  float max = 1.f; 
  if(m_typec == 0.f){ 
    for(j=0,i=0,tpos=0;j<m_segments;j++){
      for(i=0;i<m_seglen[j];i++, tpos++){
	m_table[tpos] = ((m_segp[j+1] - m_segp[j])/m_seglen[j])*i 
	  + m_segp[j];
	max = (max < m_table[tpos])? m_table[tpos] : max;   
      }
    } 
  } else {                           // exponential  
    for(j=0,i=0,tpos=0;j<m_segments;j++){
      for(i=0;i<m_seglen[j];i++, tpos++){
	m_table[tpos] = m_segp[j] + (m_segp[j+1]- m_segp[j])*
	  (float)((1 - exp(((double)i/m_seglen[j])*m_typec))
		  /(1.f  - exp((double)m_typec)));
	max = (max < m_table[tpos])? m_table[tpos] : max;   
      }
    }
  }
  if(max)
    for(i = 0; i < m_L; i++) m_table[i] = m_table[i]/max;
  m_table[m_L] = m_table[m_L-1]; 
  return 1;

}
  
////////// ERROR HANDLING //////////////////////////////////////////////

char*
EnvTable::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
    message = "No error.";
    break; 

  case 1:
    message = "MakeTable() failed. Unsupported curve type.";
    break;

  default:
    message = "Undefined error";
    break;
  }

  return message;

}
