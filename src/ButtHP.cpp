// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ButtHP.cpp : implementation of the ButtHP class           //
//               (2nd order band-pass filter).                //
//                                                            //
//                                                            //
//************************************************************//

#include "ButtHP.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

ButtHP::ButtHP(){
m_type = 3;
SetParam(m_fr, 0, m_type);

                 }

ButtHP::ButtHP(float fr, SndObj* inObj,  SndObj* inputfreq, int vecsize, float sr) 
: ButtBP (fr, 0.f, inObj, inputfreq, 0, vecsize, sr){
m_type = 3;
SetParam(m_fr, 0, m_type);
}

ButtHP::~ButtHP(){

}

