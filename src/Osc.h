// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information


#ifndef _OSC_H
#define _OSC_H

#include "FastOsc.h"


class Osc : public FastOsc {

 protected:

  SndObj* m_inputfr;
  SndObj* m_inputamp;

 public:

  Osc();
  Osc(Table* table, float fr, float amp, SndObj* inputfr,
      SndObj* inputamp = 0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);

  ~Osc();
 
  void SetFreq(SndObj* inputfr){ m_inputfr = inputfr; }
  void SetAmp(SndObj* inputamp) { m_inputamp = inputamp; }
  int Connect(char* mess, void* input);
  short DoProcess();


};

#endif
