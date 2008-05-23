 
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

/////////////////////////////////////////////////////
// Hilbert Transform filter
//
// VL, 2001
//////////////////////////////////////////////////////
#ifndef _HILB_H
#define _HILB_H
#include "SndObj.h"

const float c1 = -0.190696f;
const float c2 = -0.860735f;
const float c3 = -0.5531f; 

const double poles[12] = {.3609, 2.7412, 11.1573, 44.7581, 179.6242, 798.4578, 
			  1.2524, 5.5671, 22.3423, 89.6271, 364.7914, 2770.1114};


class Hilb : public SndObj 
{
 protected:
  SndObj*       m_channel;

  // pointers to the memory locations
  double*        m_delay1;
  double*        m_delay2;
  double*        m_delay3;
  double*        m_delay4;


  // memory
  double*        m_delay;

  double*        m_coef;

  inline double  allpass(double in, double* delay, double coef);

 public:

  SndObj*       real;
  SndObj*       imag;

  // constructors / destructor
  Hilb();
  Hilb(SndObj* input,
       int vecsize=DEF_VECSIZE, float sr=DEF_SR);

  ~Hilb();
   

  short DoProcess();
  char* ErrorMessage();

};


double	
Hilb::allpass(double in, double* delay, double coef1){

  double out = coef1*(in - delay[1]) + delay[0];
  // recirculate the delay line
  delay[0] = in;
  return (delay[1] = out);
}


#endif

