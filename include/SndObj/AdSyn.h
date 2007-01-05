// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _ADSYN_H
#define _ADSYN_H

#include "ReSyn.h"

class AdSyn : public ReSyn {

 public:

  AdSyn();
  AdSyn(SinAnal* input, int maxtracks, Table* table,
	float pitch = 1.f, float scale=1.f, 
	int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~AdSyn();
  short DoProcess();


};

#endif
