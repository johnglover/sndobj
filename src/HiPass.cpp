// Copyright (c)Rory Walsh, 2003
// See License.txt for a disclaimer of all warranties
// and licensing information

//*************************************************************//
// HiPass.cpp : implementation of a High Pass filter 
//                                			      //
//         Rory Walsh May 2003   			      //
//                                          		      //
//*************************************************************//

#include "HiPass.h"

HiPass::HiPass()
{
double  C = 2 - cos(2*PI*m_fr/m_sr);	
m_b1 = C - sqrt((C*C) - 1); 
m_a = 1 - m_b1;
}

HiPass::HiPass(float freq, SndObj* inObj, int vecsize, float sr):
  LoPass(freq, inObj,vecsize,sr)
{
double  C = 2 - cos(2*PI*m_fr/m_sr);	
m_b1 = C - sqrt((C*C) - 1); 
m_a = 1 - m_b1;
}

HiPass::~HiPass(){
}

int HiPass::Set(char* mess, float value){

	switch (FindMsg(mess)){

	case 21:
    SetFreq(value);
	return 1;

    case 23:
	SetSr(value);
	return 1;

	default:
    return SndObj::Set(mess,value);
     
	}


}
