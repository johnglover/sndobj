// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ButtLP.cpp : implementation of the ButtLP class           //
//               (2nd order band-pass filter).                //
//                                                            //
//                                                            //
//************************************************************//

#include "ButtLP.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

ButtLP::ButtLP(){
  m_type = 4;
  SetParam(m_fr, 0, m_type);

}

ButtLP::ButtLP(float fr, SndObj* inObj,  SndObj* inputfreq, int vecsize, float sr) 
  : ButtBP (fr, 0.f, inObj, inputfreq, 0, vecsize, sr){
  m_type = 4;
  SetParam(m_fr, 0, m_type);
}

ButtLP::~ButtLP(){

}


