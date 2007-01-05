// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  HarmTable.cpp: implemenation of the HarmTable class       //
//                 (harmonic function table).                 //
//                                                            //
//                                                            //
//************************************************************//

#include "HarmTable.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

HarmTable :: HarmTable(){

  m_L = 1024;
  m_harm = 1;
  m_typew = SINE;
  m_phase  = 0.f;
  m_table = new float[m_L+1];
  MakeTable();

}


HarmTable :: HarmTable(long L, int harm, int type, float phase){

  m_L = L;
  m_harm = harm;
  m_typew = type;
  m_phase = (float)(phase*TWOPI);

  m_table = new float [m_L+1];
  MakeTable();

}


HarmTable :: ~HarmTable(){

  delete[] m_table;

}


///////////// OPERATIONS ////////////////////////////////////

void
HarmTable::SetHarm(int harm, int type)
{
  m_harm = harm;
  m_typew = type;
  MakeTable();
}

short
HarmTable :: MakeTable(){
  
  float max = 1.f;	
  int n = 1, harm = m_harm, i;       

  switch (m_typew){
  case SINE:
    for(i=0; i < m_L; i++)
      m_table[i] = (float)(sin(i*TWOPI/m_L + m_phase)); 
    break;

  case SAW:
    ZeroTable();
    for(i=0; i < m_L; i++){
      for(n = 1 ; n <= harm ; n++)
	m_table[i] += (float)((1/(float)n)*sin(n*i*TWOPI/m_L + m_phase));
      max = (fabs((double)max) < fabs((double)m_table[i])) ? m_table[i] : max;
    }
    break;

  case SQUARE:
    ZeroTable();
    for(i=0; i < m_L; i++){
      for(n = 1 ; n <= harm ; n+=2)
	m_table[i] += (float)((1/(float)n)*sin(n*TWOPI*i/m_L + m_phase));		 
      max = (fabs((double)max) < fabs((double)m_table[i])) ? m_table[i] : max;
    }
    break;

  case BUZZ:
    ZeroTable();
    for(i=0; i < m_L; i++){
      for(n = 1 ; n <= harm ; n++)
	m_table[i] += (float) sin(n*TWOPI*i/m_L + m_phase);			
      max = (fabs((double)max) < fabs((double)m_table[i])) ? m_table[i] : max;
    }
    break;

  default:
    ZeroTable();
    m_error = 1;          
    return 0;
    break;
  } 

  //normalize:
  if(m_typew!=SINE)
    for(n = 0; n < m_L; n++)
      m_table[n] = m_table[n]/max;
  m_table[m_L] = m_table[0];  // guard point
  return 1;            
}

///////////////// ERROR HANDLING ///////////////////////////////

char*
HarmTable::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
    message = "No error.";
    break; 

  case 1:
    message = "MakeTable() failed. Unsupported wave type.";
    break;

  default:
    message = "Undefined error";
    break;
  }

  return message;

}






