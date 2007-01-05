// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  ButtBR.cpp : implementation of the ButtBR class           //
//               (2nd order band-reject filter).              //
//                                                            //
//                                                            //
//************************************************************//

#include "ButtBR.h"

/////////////// CONSTRUCTION / DESTRUCTION /////////////////////

ButtBR::ButtBR(){ 
  m_type = 2;
  SetParam(m_fr, m_bw, m_type);
}

ButtBR::ButtBR(float fr, float bw, SndObj* inObj,  SndObj* inputfreq, 
	       SndObj* inputbw, int vecsize, float sr) 
  : ButtBP (fr, bw, inObj, inputfreq, inputbw, vecsize, sr){
  m_type = 2;
  SetParam(m_fr, m_bw, m_type);
}

ButtBR::~ButtBR(){
}




  
  
  
   
