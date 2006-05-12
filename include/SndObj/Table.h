// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Table.h: interface of the table abstract base class       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _TABLE_H 
#define _TABLE_H
#include <math.h>
const double TWOPI = 8.*atan(1.);
class Table {
  
            protected:

 long  m_L;         // size;
 float* m_table;    // table
 int   m_error;     // error code
 void ZeroTable () 
        {
         int i;
         for(i=0;i<m_L;i++) m_table[i]=0.f;
        }

 
            public:

 long GetLen() { return m_L; }
 float* GetTable(){ return m_table; }
 float Lookup(int pos){
	 return m_table[pos%m_L];
 }

 virtual ~Table(){};
 virtual char* ErrorMessage() = 0;
 virtual short MakeTable() = 0; 
 
         
             };
 
#endif
