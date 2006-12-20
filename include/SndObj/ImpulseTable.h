// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ImpulseTable.h: interface of the ImpulseTable class       //
//                                                           //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _ImpulseTable_H
#define _ImpulseTable_H

#include "SpecEnvTable.h"
#include <rfftw.h>

class ImpulseTable : public SpecEnvTable {
protected:
  Table*  m_window;
  rfftw_plan m_plan; // FFTW initialisation
  float* m_ffttmp;
      public:
		
  void SetWindow(Table* window){
			  m_window = window->GetLen() == m_L ? window : 0;
			  MakeTable();
		  }
  short MakeTable();
  ImpulseTable();
  ImpulseTable(long L,
	  int segments, float start, 
	  float* points, float* lengths,float type = 0.f,
	  Table* window=0,
	  float nyquistamp=0.f);
  
  ~ImpulseTable();

        };

#endif
