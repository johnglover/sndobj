// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  UsrDefTable.h: interface of the UsrDefTable class         //
//        (User-defined function table)                       //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _USRDEFTABLE_H
#define _USRDEFTABLE_H

#include "Table.h"

class UsrDefTable : public Table {
    protected :
  float* m_pvalues;     
    
    public:
 
  void SetTable(long L, float* values);
  char* ErrorMessage();
  short MakeTable();
  UsrDefTable();
  UsrDefTable(long L, float* values);
  ~UsrDefTable();
                             };

#endif
