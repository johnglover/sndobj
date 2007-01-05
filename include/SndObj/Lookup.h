// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//*******************************************************//
//     Lookup.h : interface of the Lookup class
//                  truncated table lookup 
//
//*******************************************************//

#ifndef _LOOKUP_H
#define _LOOKUP_H

#include "SndObj.h"
#include "Table.h"

enum { RAW_VALUE=0, NORMALISED};
enum { LIMIT=0, WRAP_AROUND};

class Lookup : public SndObj {

 protected:

  Table* m_ptable;         // reference to a Table obj    
  
  long m_offset;
  long m_size; 
  int m_mode;
  int m_normal;

 public:
  Lookup();
  Lookup(Table* table, long offset, SndObj* InObj, 
	 int mode = WRAP_AROUND,
	 int normal=RAW_VALUE, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  void SetMode(int mode, int normal){ m_mode = mode; m_normal = normal; }
  ~Lookup();
  void Offset(long offset){ m_offset = offset; }  
  void SetTable(Table* table);

  int Set(char* mess, float value);
  int Connect(char* mess, void* input);

  short DoProcess();
  
};

#endif
