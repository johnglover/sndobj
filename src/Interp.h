// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//***********************************************************//
//  Interp.h : interface of the Interp Class
//            (interpolation object) 
//
//***********************************************************//

#ifndef _INTERP_H
#define _INTERP_H
#include "SndObj.h"

class Interp : public SndObj {

     protected:

float m_initial; // initial value 
float m_fin;  // fin value
float m_typec;  // type of curve  0 = LINEAR, EXP < 0 < INV EXP
unsigned long m_dur;
unsigned long m_count;

     public:

Interp();
Interp(float initial, float fin,
        float dur, float type = 0.f, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
~Interp();

int Set(char* mess, float value);
void SetSr(float sr);
void  Restart(){ m_count = 0; };
void  SetCurve(float initial, float fin, 
                  float m_typec = 0.f);
void  SetDur(float dur){
        m_dur = (unsigned long) (m_sr*dur);
		m_count = 0;
}
short DoProcess();

};

#endif
