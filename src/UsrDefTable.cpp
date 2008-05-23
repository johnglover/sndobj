 
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
//  UsrDefTable.cpp: implementationof the UsrDefTable obj     //
//        (User-defined function table)                       //
//                                                            //
//                                                            //
//************************************************************//
#include "UsrDefTable.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

UsrDefTable :: UsrDefTable(){

  m_L = 8;
  m_pvalues = 0;
  m_table = new float[m_L+1];
  MakeTable();

}

UsrDefTable :: UsrDefTable(long L, float* values){
  m_L = L;
  m_pvalues = values;
  m_table = new float[m_L+1];
  MakeTable();
}

UsrDefTable :: ~UsrDefTable(){

  delete[] m_table;

}


///////////// OPERATIONS ////////////////////////////////////

void
UsrDefTable::SetTable(long L, float* values)
{
  if(m_L != L){
    m_L = L;
    delete[] m_table;
    m_table = new float[m_L+1];
  }
  m_pvalues = values;
  MakeTable();
}

short
UsrDefTable :: MakeTable(){
  for(long n = 0; n < m_L; n++) m_table[n] = m_pvalues[n];
  m_table[m_L] = m_pvalues[m_L-1];
  return 1;
}

///////////////// ERROR HANDLING ///////////////////////////////

char*
UsrDefTable::ErrorMessage(){
  
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


