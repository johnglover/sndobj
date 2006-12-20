// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  SpecEnvTable.h: interface of the SpecEnvTable class       //
//                                                           //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _SpecEnvTable_H
#define _SpecEnvTable_H

#include "PVEnvTable.h"

class SpecEnvTable : public PVEnvTable {
protected:
      const double m_pi;
      public:
		  
  short MakeTable();
  SpecEnvTable();
  SpecEnvTable(long L,  int segments, float start, 
	  float* points, float* lengths,float type = 0.f, 
	  float nyquistamp=0.f);

  ~SpecEnvTable();

        };

#endif
