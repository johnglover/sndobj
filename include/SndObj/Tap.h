// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Tap.h: interface of the Tap class                         //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _TAP_H
#define _TAP_H


#include "DelayLine.h"


class Tap : public DelayLine
              {

	         protected:
       DelayLine* m_DLine;
       long     m_delaysamples;

               public:
       Tap();           
       Tap(float delaytime, DelayLine* DLine, int vecsize=DEF_VECSIZE, 
		    float sr=DEF_SR);         
       ~Tap();
       void SetDelayTime(float delaytime);
       void SetDelayTap(DelayLine* DLine);
       int Set(char* mess, float value);
       int Connect(char* mess, void *input);

       short DoProcess();       
       char* ErrorMessage();

	      };

#endif
