// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Comb.h: interface of the comb class                       //
//      (comb filter)                                         //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _COMB_H
#define _COMB_H

#include "DelayLine.h"

class Comb : public DelayLine 
              {

	      protected:
      
       float m_gain; // comb gain

               public:
       Comb();           
       Comb(float gain, float delaytime, SndObj* InObj, 
		   int vecsize=DEF_VECSIZE, float sr=DEF_SR);         
       ~Comb();

       void SetGain(float gain);
       int Set(char* mess, float value);
       short DoProcess();       
      
	      };

#endif




