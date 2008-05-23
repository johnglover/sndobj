 
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
//  filter.h: interface of the Filter abstract base class     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _FILTER_H
#define _FILTER_H

#include "SndObj.h"

class Filter : public SndObj {

 protected:
  
  float m_fr; 
  float m_bw;


    
  double* m_delay;        // filter delay
  void inline SetParam(float fr, float bw);

  double m_a;
  double m_b1;
  double m_b2;


 public:
  Filter();
  Filter(float fr, float bw, SndObj* inObj, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Filter();

  virtual void SetFreq(float fr);
  virtual void SetBW(float bw);
   
  int Set(char* mess, float value);

  void SetSr(float sr){
    m_sr = sr;
    SetParam(m_fr, m_bw);
  }
  char* ErrorMessage();
  short DoProcess();

 

  
};

void 
Filter::SetParam(float fr, float bw){

  double R, thecos, rsq, rr; // coefficient vars      
    
  rr = 2*(R = (1 - PI*(bw/m_sr)));
  rsq = R*R;
  thecos = (rr/(1+(rsq)))*cos(PI*(fr/(m_sr/2))); 
  m_a = (1 - (rsq))*sin(acos(thecos));
  m_b1 = rr*thecos;
  m_b2 = rsq;

}


#endif
