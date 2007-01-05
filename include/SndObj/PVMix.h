// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information
//
// PVMix.h: interface for the PVMix class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _PVMix_H
#define _PVMix_H

#include "SpecMult.h"

class PVMix : public SpecMult  
{
 protected:

 public:

  PVMix();
  PVMix(SndObj* input, SndObj* input2=0, 
	int vecsize=DEF_FFTSIZE, float sr=DEF_SR);
  ~PVMix();
  short DoProcess();


};

#endif 
