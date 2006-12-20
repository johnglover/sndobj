// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Oscilt.h: interface of the Oscilt class (truncating       //
//           oscillator).                                     //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _OSCILT_H 
#define _OSCILT_H

#include "Oscil.h"

class Oscilt : public Oscil
 
{

public:

Oscilt();

Oscilt(Table* table, float fr=440.f, 
      float amp=1.f,  SndObj* inputfreq = 0, 
      SndObj* inputamp = 0, int vecsize = DEF_VECSIZE,
	  float sr=DEF_SR);

~Oscilt();


short DoProcess();


};

#endif
