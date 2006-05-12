// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  HammingTable.cpp:  implementation of the HammingTable     //
//   object (Generalized Hamming Window function table)       //
//                                                            //
//                                                            //
//************************************************************//
#include "HammingTable.h"
//////////construction / destruction ///////////////////////
HammingTable :: HammingTable(){

m_L = 1024;
m_alpha = .54f;
m_table = new float[m_L+1];
MakeTable();

                        }

HammingTable :: HammingTable(long L, float alpha){

m_L = L;
m_alpha = alpha;
m_table = new float [m_L+1];
MakeTable();

        }


HammingTable :: ~HammingTable(){

delete[] m_table;

                         }


///////////// OPERATIONS ////////////////////////////////////
void 
HammingTable :: SetParam(long L, float alpha){
           
           m_alpha = alpha;
           m_L = L;
           delete[] m_table;
           m_table = new float[m_L+1];
  }

short
HammingTable :: MakeTable(){
for(long n = 0; n < m_L; n++)
       m_table[n]= (float)(m_alpha - (1-m_alpha)*
           cos(n*TWOPI/(m_L-1.)));
 m_table[m_L] = m_table[m_L-1];   
 return 1;            
      

 }

///////////////// ERROR HANDLING ///////////////////////////////

char*
HammingTable::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
  message = "No error.";
  break; 

  case 1:
  break;

  default:
  message = "Undefined error";
  break;
  }

 return message;

}
