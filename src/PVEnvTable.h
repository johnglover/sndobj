// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  PVEnvTable.h: interface of the PVEnvTable class              //
//                                                           //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _PVEnvTable_H
#define _PVEnvTable_H

#include "Table.h"

class PVEnvTable : public Table {

 protected:
  int* m_seglen;
  float* m_segp;
  int m_segments;

  float m_typec;       // type of curve (LOG OR LINEAR)
  float m_sr;
	 
 public:
  
  void
    SetEnvelope(int segments, float start, 
		float* points, float* lengths, 
		float type, float nyquistamp=0.f);
		  
  void SetSr(float sr);
  char* ErrorMessage();
  short MakeTable();
  PVEnvTable();
  PVEnvTable(long L, int segments, float start, 
	     float* points, float* lengths,float type = 0.f, 
	     float sr=44100.f,float nyquistamp=0.f);

  ~PVEnvTable();

};

#endif
