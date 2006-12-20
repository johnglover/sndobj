// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  UsrHarmTable.h: interface of the UsrHarmTable class       //
//        (User-defined harmonic function table)              //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _USRHARMTABLE_H
#define _USRHARMTABLE_H

#include "Table.h"

class UsrHarmTable : public Table {
    protected :

  int m_harm;
  float* m_amp;
         
      public:
 
  void SetHarm(int harm, float* amps);

  char* ErrorMessage();
  short MakeTable();
  UsrHarmTable();
  UsrHarmTable(long L, int harm, float* amps);
  ~UsrHarmTable();
                             };

#endif
