// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  HammingTable.h: interface of the HammingTable class       //
//  (Generalized hamming window function table)               //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _HAMMINGTABLE_H 
#define _HAMMINGTABLE_H
#include "Table.h"

class HammingTable : public Table {
  protected :
 
    float  m_alpha;

 public:
  
  void SetParam(long L, float alpha=.54);
  char* ErrorMessage();
  short MakeTable();
  HammingTable();
  HammingTable(long L, float alpha);
  ~HammingTable();
};


#endif
