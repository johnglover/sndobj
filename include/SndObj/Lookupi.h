// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//*******************************************************//
//     Lookupi.h : interface of the Lookup class
//                  interpolated table lookup 
//
//
//*******************************************************//
#ifndef _LOOKUPI_H
#define _LOOKUPI_H

#include "Lookup.h"
#include "Table.h"

class Lookupi : public Lookup {

		       public:
  Lookupi();
  Lookupi(Table* table, long offset, SndObj* InObj, 
	  int mode = WRAP_AROUND,
	  int normal=RAW_VALUE, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Lookupi();
  short DoProcess();
  
                              };

#endif
