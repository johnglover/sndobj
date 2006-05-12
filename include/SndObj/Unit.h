// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Unit.h: interface of the Unit class.                      //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _UNIT_H
#define _UNIT_H

#include "SndObj.h"

enum {UNIT_SAMPLE, UNIT_STEP, RAMP};

class Unit : public SndObj {

protected:
     float m_amp;
	 short m_mode;
	 float m_step;

public:
   
   Unit();
   Unit(float m_amp,  short mode = UNIT_SAMPLE, float step=0.f, int vecsize=DEF_VECSIZE,
	   float sr = DEF_SR);
   ~Unit();

   void SetAmp(float amp){ m_amp = amp;}
   void SetStep(float step){ m_step = step;}
   void SetMode(short mode){ m_mode = mode;}

   int Set(char* mess, float value);

   short DoProcess();

};

#endif
