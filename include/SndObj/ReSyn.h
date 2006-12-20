// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _RESYN_H
#define _RESYN_H

#include "SinSyn.h"

class ReSyn : public SinSyn {

 protected:

 float m_pitch;
 float m_tscal;

 public:

 ReSyn();
 ReSyn(SinAnal* input, int maxtracks, Table* table, float pitch=1.f, 
	    float scale=1.f, float tscal=1.f, int vecsize=DEF_VECSIZE, 
		float sr=DEF_SR);
  void SetPitch(float pitch){ m_pitch = pitch; }
  void SetTimeScale(float scale) { m_tscal = scale; }
  int Set(char* mess, float value);
 ~ReSyn();
  short DoProcess();


};

#endif
