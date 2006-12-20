// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  LowPass.h: 1st order lowpass  filter        
//                                                            //
//                                                            //
//************************************************************//
#ifndef _LOWPASS_H 
#define _LOWPASS_H

#include "Filter.h"


class LoPass : public Filter
 
{
protected:

public:

LoPass();
LoPass(float freq, SndObj* inObj, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
~LoPass();

void SetFreq(float fr){
m_fr = fr;
double  C = 2 - cos(2*PI*m_fr/m_sr);	
m_b1 = sqrt((C*C) - 1) - C; 
m_a = 1 + m_b1;
}

void SetSr(float sr){
m_sr = sr;
double  C = 2 - cos(2*PI*m_fr/m_sr);	
m_b1 = sqrt((C*C) - 1) - C; 
m_a = 1 + m_b1;	
}

int Set(char* mess, float value);

short DoProcess();

};

#endif
