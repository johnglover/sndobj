// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Loop.h: interface of the SndLoop class                       //
//      (comb filter)                                         //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _LOOP_H
#define _LOOP_H

#include "DelayLine.h"

class SndLoop : public DelayLine 
              {

	      protected:
      
       float m_xfade; // crossfade time in samples
	   float m_count; // count
	   short m_sample; // sample on/off
	   float m_point;
	   float m_pitch;


               public:
       SndLoop();           
       SndLoop(float xfadetime, float looptime, SndObj* InObj, 
		   float pitch = 1.f, int vecsize=DEF_VECSIZE, float sr=DEF_SR);         
       ~SndLoop();

       void SetXFade(float xfadetime){
          m_xfade = (xfadetime*m_sr);
	   }

	   void SetPitch(float pitch){ m_pitch = pitch; }
	   void ReSample(){
		               m_sample = 1; 
	                   m_count = 0;
						}

	   int Set(char* mess, float value);

       short DoProcess();       
      
	      };

#endif
