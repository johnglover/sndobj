// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  HarmTable.h: interface of the HarmTable class (harmonic   //
//           function table).                                 //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _HARMTABLE_H 
#define _HARMTABLE_H

#include "Table.h"

enum { SINE=1, SAW, SQUARE, BUZZ };

class HarmTable : public Table {
    protected :

  int m_harm;
  float m_phase;
  int m_typew;
         
      public:
 
  void SetHarm(int harm, int type);

  char* ErrorMessage();
  short MakeTable();
  HarmTable();
  void SetPhase(float phase){ m_phase = (float)(phase*TWOPI); }
  HarmTable(long L, int harm, int type, float phase=0.f);
  ~HarmTable();
                             };


#endif








