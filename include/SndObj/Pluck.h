// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Pluck.h: interface of the Pluck class                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _PLUCK_H
#define _PLUCK_H

#include "StringFlt.h"
#include "Randh.h"

class Pluck : public StringFlt
              {

	      protected:
       

       float m_amp;
	   float m_maxscale;
       void FillDelay();
       
      
               public:
       Pluck();           
       Pluck(float fr, float amp, float fdbgain, SndObj* InFrObj=0,
             float maxscale=32767.f, int vecsize=DEF_VECSIZE, 
			 float sr=DEF_SR);
	     Pluck(float fr, float amp, SndObj* InFrObj=0, float decay=20.f,
             float maxscale=32767.f, int vecsize=DEF_VECSIZE, 
			 float sr=DEF_SR);
       
       ~Pluck();
	   void RePluck();
	   int Set(char* mess, float value);
       void SetAmp(float amp, float maxscale=32767.f){
		m_amp = amp;
		((Randh*)m_input)->SetFreq((m_amp*10000.f/maxscale), 0);
		((Randh*)m_input)->SetAmp(m_amp);
		m_APDelay = m_LPDelay = 0.f;
		FillDelay(); 
	   }
        short DoProcess();       
       

	      };

#endif








