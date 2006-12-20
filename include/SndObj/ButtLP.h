// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ButtLP.h: interface of the ButtLP class (2nd order        //
//           butterworth low-pass filter).                    //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _ButtLP_H 
#define _ButtLP_H

#include "ButtBP.h"


class ButtLP: public ButtBP
 
{
protected:

public:

ButtLP();
ButtLP(float fr, SndObj* inObj, SndObj* inputfreq = 0,
	   int vecsize=DEF_VECSIZE, float sr=DEF_SR);
~ButtLP();

};

#endif
