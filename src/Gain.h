 
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
//  Gain.h: interface of the gain class                       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _GAIN_H 
#define _GAIN_H
 
#include "SndObj.h"


class Gain : public SndObj{

 protected:

  float         m_gain;  // gain factor in dB
       
 public:

  Gain();                            
  Gain(float gain, SndObj* InObj, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Gain();

  int Set(char* mess, float value);
  void  SetGain(float gain);
  void  SetGainM(float gain_multiplier) { m_gain = gain_multiplier; }
    
  float dBToAmp(float amp);      // changes amp in dB to amp multiplier
  short DoProcess();           // change gain

};


#endif
