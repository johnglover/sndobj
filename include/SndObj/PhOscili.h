// Copyright (c)Frank Barknecht, 2003
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  PhOscili.h: interface of the PhOscili class (interpolating  //
//           oscillator with phase input).                    //
//                                                            //
//  Frank Barknecht <fbar@footils.org>, 2002                  //
//                                                            //
//************************************************************//
#ifndef _PhOscili_H
#define _PhOscili_H

#include "Oscil.h"

class PhOscili : public Oscil
 
{
protected:
  SndObj* m_inputphase;
	
public:

PhOscili();

PhOscili(
		Table* table, 
		float fr, 
		float amp,  
		SndObj* inputfreq = 0, 
		SndObj* inputamp = 0, 
		SndObj* inputphase = 0, 
		int vecsize= DEF_VECSIZE,
		float sr=DEF_SR
	);

~PhOscili();

int Connect(char* mess, void* input);
short DoProcess();

};
#endif
