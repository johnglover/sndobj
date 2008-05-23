 
////////////////////////////////////////////////////////////////////////
// This file is part of the SndObj library
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
//
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




  
  
  
   
