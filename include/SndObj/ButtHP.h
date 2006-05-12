// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ButtHP.h: interface of the ButtHP class (2nd order        //
//           butterworth high-pass filter).                   //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _ButtHP_H 
#define _ButtHP_H

#include "ButtBP.h"


class ButtHP: public ButtBP
 
{
protected:

public:

ButtHP();

ButtHP(float fr, SndObj* inObj, SndObj* inputfreq = 0,
	   int vecsize=DEF_VECSIZE, float sr=DEF_SR);

 ~ButtHP();

};

#endif
