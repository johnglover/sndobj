// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Allpass.h: interface of the Allpass class                 //
//      (Allpass filter)                                      //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _ALLPASS_H
#define _ALLPASS_H

#include "Comb.h"

class Allpass : public Comb 
              {

	      protected:
      


               public:
       Allpass();           
       Allpass(float gain, float delaytime, SndObj* InObj, 
		   int vecsize=DEF_VECSIZE, float sr=DEF_SR);           
       ~Allpass();


       short DoProcess();       
      
	      };

#endif




