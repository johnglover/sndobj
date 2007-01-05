// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  EnvTable.h: interface of the EnvTable class              //
//                                                           //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _EnvTable_H
#define _EnvTable_H

#include "Table.h"

class EnvTable : public Table {

 protected:
  int* m_seglen;
  float* m_segp;
  int m_segments;

  float m_typec;       // type of curve (LOG OR LINEAR)

 public:
  
  void SetEnvelope(int segments, float start, 
		   float* points, float* lengths, 
		   float type);
		  

  char* ErrorMessage();
  short MakeTable();
  EnvTable();
  EnvTable(long L,  int segments, float start, 
	   float* points, float* lengths,float type = 0.f);

  ~EnvTable();

};

#endif
