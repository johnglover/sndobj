// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  SndTable.h:  interface of the SndTable class              //
//               (soundfile function table)                   //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _SNDTABLE_H
#define _SNDTABLE_H

#include "Table.h"
#include "SndFIO.h"

class SndTable : public Table {
    protected :

   SndFIO* m_input;
   short  m_channel;

      public:
  
  void SetInput(long L, SndFIO* input, short channel=1);
  char* ErrorMessage();
  short MakeTable();
  SndTable();
  SndTable(long L, SndFIO* input, short channel=1);
  ~SndTable();
                             };


#endif
