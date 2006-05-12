// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ButtBR.h: interface of the ButtBR class (2nd order        //
//           butterworth band-reject filter).                 //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _ButtBR_H 
#define _ButtBR_H

#include "ButtBP.h"


class ButtBR : public ButtBP
 
{

protected:

public:

ButtBR();
ButtBR(float fr, float bw, SndObj* inObj, SndObj* inputfreq = 0, 
      SndObj* inputbw = 0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
~ButtBR();

};

#endif
