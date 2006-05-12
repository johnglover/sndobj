// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

////////////////////////////////////////////////
// TpTz.h: interface for the TpTz class
//        two-pole two-zero filter.
//
///////////////////////////////////////////////

#ifndef _TPTZ_H
#define _TPTZ_H

#include "Filter.h"

class TpTz: public Filter {

protected:


double m_a1;
double m_a2;


public:

TpTz();
TpTz(double a, double a1, double a2,
     double b1, double b2, SndObj* input,
	 int vecsize=DEF_VECSIZE, float sr=DEF_SR);

~TpTz();

void
SetParam(double a, double a1, double a2,
		 double b1, double b2){
m_a = a;
m_a1 = a1;
m_a2 = a2;
m_b2 = b2;
m_b1 = b1;
}

int Set(char* mess, float value);

short DoProcess();

};

#endif










