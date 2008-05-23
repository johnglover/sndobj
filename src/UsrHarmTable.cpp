 
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
//  UsrHarmTable.cpp: implementationof the UsrHarmTable obj   //
//        (User-defined harmonic function table)              //
//                                                            //
//                                                            //
//************************************************************//
#include "UsrHarmTable.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

UsrHarmTable :: UsrHarmTable(){

  m_L = 1024;
  m_harm = 1;
  m_amp = new float[1];
  m_amp[0] = 1.f;

  m_table = new float[m_L+1];
  MakeTable();

}


UsrHarmTable :: UsrHarmTable(long L, int harm, float* amps){

  m_L = L;
  m_harm = harm;
  m_amp = new float[harm];

  for(int i = 0; i < harm; i++)
    m_amp[i] = amps[i];

  m_table = new float [m_L+1];
  MakeTable();

}

UsrHarmTable :: ~UsrHarmTable(){

  delete[] m_table;
  delete[] m_amp;
}


///////////// OPERATIONS ////////////////////////////////////

void
UsrHarmTable::SetHarm(int harm, float* amps)
{
  delete[] m_amp;
  m_harm = harm;
  m_amp = new float[harm];

  for(int i = 0; i < harm; i++)
    m_amp[i] = amps[i];

  MakeTable();
}

short
UsrHarmTable :: MakeTable(){
  
  float max = 1.f;	       
  int n;	

  ZeroTable();
  for(int i=0; i < m_L; i++){
    for(n = 0 ; n < m_harm ; n++)
      m_table[i] += (float)(m_amp[n]*sin((n+1)*i*TWOPI/m_L));
    max = (fabs((double)max) < fabs((double)m_table[i])) ? m_table[i] : max;
  }
	     
  //normalize:
  for(n = 0; n < m_L; n++)
    m_table[n] = m_table[n]/max;
  m_table[m_L] = m_table[0];
  return 1;            
}

///////////////// ERROR HANDLING ///////////////////////////////

char*
UsrHarmTable::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
    message = "No error.";
    break; 

  case 1:
    message = "";
    break;

  default:
    message = "Undefined error";
    break;
  }

  return message;

}
