// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Pitch.h: interface of the Pitch class                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _PITCH_H
#define _PITCH_H

#include "DelayLine.h"

class Pitch : public DelayLine 
              {

	      protected:
      float* sintab;
	  float m_pointer1;
	  float m_pointer3;

	   float m_pitch;
       float m_incr;

               public:
       Pitch();           
       Pitch(float delaytime, SndObj* InObj, 
		   float pitch = 1.f, int vecsize=DEF_VECSIZE, float sr=DEF_SR); 
       Pitch(float delaytime, SndObj* InObj, int semitones = 0,
		   int vecsize=DEF_VECSIZE, float sr=DEF_SR);
    
       ~Pitch();
	   void SetPitch(float pitch){ m_pitch = pitch; }
	   void SetPitch(int semitones){
		   m_pitch = (float) pow(2., semitones/12.);
	   }
	   int Set(char* mess, float value);
       short DoProcess();       
      
	      };

#endif







