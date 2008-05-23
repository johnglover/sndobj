 
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
//  TrisegTable.cpp: implementation of the TrisegTable class  //
//                   (three-segment function table).          //
//                                                            //
//                                                            //
//************************************************************//

#include "TrisegTable.h"

//////////// CONSTRUCTION / DESTRUCTION ////////////////////////

TrisegTable :: TrisegTable(){

  m_L = 512;
  m_initial = 0.f; 
  m_point1 = 1.f;
  m_point2 = 1.f;
  m_fin  = 0.f;

  m_seg1   = .25f;   
  m_seg2   = .5f;
  m_seg3   = .25f;


  m_typec = 0.f;

  m_table = new float[m_L+1];
  MakeTable();

}


TrisegTable :: TrisegTable(long L, float init, float seg1, 
			   float p1, float seg2, float p2,
			   float seg3, float fin, float type){

  m_L = L;
  m_typec = type;

  m_initial = init; 
  m_point1 = p1;
  m_point2 = p2;
  m_fin  = fin;

  m_seg1   = seg1;   
  m_seg2   = seg2;
  m_seg3   = seg3;



  m_table = new float [m_L+1];
  MakeTable();

}

 
TrisegTable::TrisegTable(long L, float* TSPoints, float type)
{
  m_L = L;
  m_typec = type;

  m_initial = TSPoints[0]; 
  m_point1 = TSPoints[2];
  m_point2 = TSPoints[4];
  m_fin  = TSPoints[6];

  m_seg1   = TSPoints[1];   
  m_seg2   = TSPoints[3];
  m_seg3   = TSPoints[5];

  m_table = new float [m_L+1];
  MakeTable();

}

TrisegTable::~TrisegTable(){

  delete[] m_table;

}

void
TrisegTable::SetCurve(float init, float seg1, 
		      float p1, float seg2, float p2,
		      float seg3, float fin, float type)
{
		      
  m_initial = init; 
  m_point1 = p1;
  m_point2 = p2;
  m_fin  = fin;

  m_seg1   = seg1;   
  m_seg2   = seg2;
  m_seg3   = seg3;

  m_typec = type;

  MakeTable();
		    
}

////////////// OPERATIONS //////////////////////////////////////

void
TrisegTable::SetCurve(float* TSPoints, float type){

  m_typec = type;

  m_initial = TSPoints[0]; 
  m_point1 = TSPoints[2];
  m_point2 = TSPoints[4];
  m_fin  = TSPoints[6];

  m_seg1   = TSPoints[1];   
  m_seg2   = TSPoints[3];
  m_seg3   = TSPoints[5];

  m_table = new float [m_L+1];

  MakeTable();
}

short
TrisegTable :: MakeTable(){   
  int i;
  float max = 1.f; 
  // normalize the seg lenghts to the table lenght:  
  float total=m_seg1+m_seg2+m_seg3;
  int seg1 = (int)((m_seg1/total)*m_L);
  int seg2 = (int)((m_seg2/total)*m_L);
  int seg3 = (int)((m_seg3/total)*m_L);   

  if(m_typec == 0.f){             //LINEAR    
    for(i=0;i<seg1;i++)           // first segment
      {
	m_table[i] = ((m_point1 - m_initial)/seg1)*i + m_initial;
	max = (max < m_table[i])? m_table[i] : max;   
      }
    for(i=seg1;i<(seg1+seg2);i++) // second segment
      {
	m_table[i] = ((m_point2 - m_point1)/seg2)*(i - seg1) + m_point1;    
	max = (max < m_table[i])? m_table[i] : max;
      }
    for(i=seg1+seg2;i<m_L;i++)    // third segment
      {
	m_table[i] = ((m_fin - m_point2)/seg3)*(i - (seg1 + seg2)) + m_point2;
	max = (max < m_table[i])? m_table[i] : max;   
      }
  }
  else {                           // exponential  
    for(i=0;i<seg1;i++){           // first segment     
      m_table[i] = m_initial + (m_point1- m_initial)*
	(float)((1 - exp(((double)i/seg1)*m_typec))/(1.f  - exp((double)m_typec)));    
      max = (max < m_table[i])? m_table[i] : max;
    }     
    for(i=seg1;i<(seg2+seg1);i++){ // second segment
      m_table[i] = m_point1 + (m_point2 - m_point1)*(float)(
							    (1.f-exp(((double)(i-seg1)/seg2)*m_typec))/
							    (1.f-exp((double)m_typec)));                
      max = (max < m_table[i])? m_table[i] : max;   
    }
    for(i=seg2+seg1;i<m_L;i++){    // third segment
      m_table[i] = m_point2 + (m_fin - m_point2)*(float)(
							 (1.f-exp(((double)(i-(seg1+seg2))/seg3)*m_typec))/
							 (1.f-exp((double)m_typec)));     
      max = (max < m_table[i])? m_table[i] : max;       
    }    
  }
  if(max)
    for(i = 0; i < m_L; i++) m_table[i] = m_table[i]/max;
  m_table[m_L] = m_table[m_L-1]; 
  return 1;
}


////////// ERROR HANDLING //////////////////////////////////////////////

char*
TrisegTable::ErrorMessage(){
  
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




