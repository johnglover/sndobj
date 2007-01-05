// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SPECINTERP_H
#define _SPECINTERP_H

#include "SpecMult.h"


class SpecInterp : public SpecMult {
	
 protected:

  float   m_offset;
  SndObj* m_interpobj;

 public:

  SpecInterp();
  SpecInterp(float i_offset, SndObj* input1, SndObj* input2,
	     SndObj* interpobj=0, int vecsize=DEF_FFTSIZE,
	     float sr=DEF_SR);
  ~SpecInterp();

  int Connect(char* mess, void* input);
  int Set(char* mess, float value);
  void SetInterp(float i_offset, SndObj* interpobj=0){
    m_offset = i_offset;
    m_interpobj = interpobj;
  }

  short DoProcess();

};

#endif
