// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  StringFlt.h: interface of the StringFlt class                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _StringFlt_H
#define _StringFlt_H

#include "DelayLine.h"


class StringFlt : public DelayLine
              {

	      protected:
       float m_vdtime;
       float m_fdbgain;
       float m_fr;
       float m_a;
       float m_LPDelay;
       float m_APDelay;
	   float m_s;
	   float m_decay;
     
       SndObj* m_inputfr;

               public:
       StringFlt();           
       StringFlt(float fr, float fdbgain, SndObj* inObj, 
			SndObj* InFrObj=0, 
			int vecsize=DEF_VECSIZE, float sr=DEF_SR); 
        StringFlt(float fr, SndObj* inObj, float decay,
			SndObj* InFrObj=0, 
			int vecsize=DEF_VECSIZE, float sr=DEF_SR); 
       
       ~StringFlt();
       
	   void SetSr(float sr);
	   void SetDecay(float decay);
	   void SetFreq(float fr, SndObj* InFrObj=0);
       void SetFdbgain(float fdbgain){ 
		   if(m_decay == 0.f)
                      m_fdbgain = fdbgain; } 
	   int Set(char* mess, float value);
	   int Connect(char* mess, void* input);
       short DoProcess();       


	      };

#endif







