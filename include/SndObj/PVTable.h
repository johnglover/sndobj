// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  PVTable.h: interface of the PVTable class              //
//                                                          //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _PVTable_H
#define _PVTable_H

#include "Table.h"
#include "SndIn.h"
#include "PVA.h"
#include "SndFIO.h"

class PVTable : public Table {
protected:
	double* m_amps;
	double* m_freqs;
	SndFIO* m_file;
	SndIn* m_in;
	PVA* m_analysis;
	unsigned long m_framecount;
	float m_start;
	unsigned long m_end;
	int m_vecsize;
	float m_sr;

      public:
		  
  void SetTable(SndFIO* soundfile, Table* window, 
				  float start, float end);
  short MakeTable();
  PVTable();
  PVTable(int L, SndFIO* soundfile, Table* window, 
				 float start, float end);

  ~PVTable();
char*
ErrorMessage();
        };

#endif
