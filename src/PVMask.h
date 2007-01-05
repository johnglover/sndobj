// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _PVMask_H
#define _PVMask_H

#include "SpecInterp.h"

class PVMask : public SpecInterp {
	
 protected:
  float   m_maskgain;

 public:

  PVMask();
  PVMask(float maskgain, SndObj* input, SndObj* mask,
	 SndObj* inmaskgobj=0, int vecsize=DEF_FFTSIZE,
	 float sr=DEF_SR);
  PVMask(float maskgain, Table* masktable, SndObj* input,
	 SndObj* inmaskgobj=0, int vecsize=DEF_FFTSIZE,
	 float sr=DEF_SR );
  ~PVMask();

  int Connect(char* mess, void* input);
  int Set(char* mess, float value);

  void SetMaskInput(SndObj* mask){ SetInput2(mask);}
  void SetMaskTable(Table *mask) { SetTable(mask);}

  void SetMaskGain(float maskgain, SndObj* inmaskg=0){
    m_maskgain = maskgain;
    m_interpobj = inmaskg;
  }

  short DoProcess();

};

#endif
