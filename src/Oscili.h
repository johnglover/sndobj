// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Oscili.h: interface of the Oscili class (interpolating    //
//           oscillator).                                     //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _OSCILI_H
#define _OSCILI_H

#include "Oscil.h"

class Oscili : public Oscil
 
{

 public:

  Oscili();

  Oscili(Table* table, float fr=440.f, 
	 float amp=1.f,  SndObj* inputfreq = 0, 
	 SndObj* inputamp = 0, int vecsize= DEF_VECSIZE, float sr=DEF_SR);

  ~Oscili();
  short DoProcess();

};

#endif
