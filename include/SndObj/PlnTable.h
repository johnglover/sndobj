// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  PlnTable.h: interface of the PlnTable class               //
//        (Polynomial function table)                         //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _PLNTABLE_H
#define _PLNTABLE_H

#include "Table.h"

class PlnTable : public Table {
    protected :

  int m_order;
  double* m_coefs;
  float m_range;       
      public:
 
  void SetPln(int order, double* coefs, float range=1.f);
  char* ErrorMessage();
  short MakeTable();
  PlnTable();
  PlnTable(long L, int order, double* coefs, float range=1.f);
  ~PlnTable();
                             };

#endif
