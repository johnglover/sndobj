 
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
// Copyright (c)Frank Barknecht, 2003
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  PhOscili.h: interface of the PhOscili class (interpolating  //
//           oscillator with phase input).                    //
//                                                            //
//  Frank Barknecht <fbar@footils.org>, 2002                  //
//                                                            //
//************************************************************//
#ifndef _PhOscili_H
#define _PhOscili_H

#include "Oscil.h"

class PhOscili : public Oscil
 
{
 protected:
  SndObj* m_inputphase;
	
 public:

  PhOscili();

  PhOscili(
	   Table* table, 
	   float fr, 
	   float amp,  
	   SndObj* inputfreq = 0, 
	   SndObj* inputamp = 0, 
	   SndObj* inputphase = 0, 
	   int vecsize= DEF_VECSIZE,
	   float sr=DEF_SR
	   );

  ~PhOscili();

  int Connect(char* mess, void* input);
  short DoProcess();

};
#endif
