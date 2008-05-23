 
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
//  PlnTable.cpp: implementationof the PlnTable obj           //
//        (Polynomial function table)                         //
//                                                            //
//                                                            //
//************************************************************//
#include "PlnTable.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

PlnTable :: PlnTable(){

  m_L = 1024;
  m_order = 1;
  m_coefs = new double[1];
  m_coefs[0] = 1.;
  m_range = 1.f;
  m_table = new float[m_L+1];
  MakeTable();

}


PlnTable :: PlnTable(long L, int order, double* coefs,
                     float range){

  m_L = L;
  m_order = order;
  m_coefs = new double[m_order+1];
  m_range = range;
  for(int i = 0; i <= m_order; i++)
    m_coefs[i] = coefs[i];

  m_table = new float[m_L+1];
  MakeTable();

}

PlnTable :: ~PlnTable(){

  delete[] m_table;
  delete[] m_coefs;
}


///////////// OPERATIONS ////////////////////////////////////

void
PlnTable::SetPln(int order, double* coefs, float range)
{
  delete[] m_coefs;
  m_order = order;
  m_coefs = new double[m_order+1];
  m_range = range;
  for(int i = 0; i <= m_order; i++)
    m_coefs[i] = coefs[i];

  MakeTable();
}

short
PlnTable :: MakeTable(){
  double x = 2.*m_range/m_L;
  ZeroTable();
  for(int n=0; n <= m_L; n++){
    m_table[n] = (float) m_coefs[0]; 
    for(int i=1; i <= m_order; i++)
      m_table[n] += (float)(m_coefs[i]*pow((x*n)-m_range, (double)i));
  }
  return 1;
}

///////////////// ERROR HANDLING ///////////////////////////////

char*
PlnTable::ErrorMessage(){
  
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
