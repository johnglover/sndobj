// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information


#ifndef _OSCI_H
#define _OSCI_H

#include "Osc.h"


class Osci : public Osc {

 protected:
 
 long m_lomask;
 float m_lodiv;

 public:

 Osci();
 Osci(Table* table, float fr, float amp, SndObj* inputfr,
      SndObj* inputamp = 0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);

 ~Osci();
 void SetTable(Table *table);
 int Connect(char* mess, void* input);

 short DoProcess();


};

#endif
