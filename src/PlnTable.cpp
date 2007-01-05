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
