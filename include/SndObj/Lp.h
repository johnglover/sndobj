// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

////////////////////////////////////////////////
// Low-pass resonant filter
//
// VL, 2002
////////////////////////////////////////////////
#ifndef _Lp_H
#define _Lp_H
#include "Reson.h"


class Lp: public Reson {
 protected:

  void inline SetLPparam(float fr, float bw);

 public:

  // constructors / destructor
  Lp();
  Lp(float fr, float BW, SndObj* inObj, SndObj* inputfreq = 0, 
     SndObj* inputBW = 0, int vecisize=DEF_VECSIZE, float sr=DEF_SR);
  ~Lp();

  void SetSr(float sr){
    m_sr = sr;
    SetLPparam(m_fr, m_bw);
  }
  int Set(char* mess, float value);

  short DoProcess();
};

void Lp::SetLPparam(float fr, float bw){
  float Q = fr/bw; 
  m_b1 = (100./Q*sqrt(fr))-1.;
  m_b2 = 100./fr;
  m_a = 1 + m_b1 + m_b2;
}


#endif

