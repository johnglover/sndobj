 
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

/***************************************************/
// Bend.cpp: implementation of the Bend class,      /
//           MIDI pitchbend input processing        /
//                                                  /
/***************************************************/

#ifndef _BEND_H
#define _BEND_H

#include "MidiIn.h"

class Bend : public MidiIn {

 protected:

  float m_bend;
  float m_range;

 public:

  Bend();
  Bend(SndObj* InObj, SndMidiIn* input, float range, short channel = 1, 
       int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Bend();

  void SetRange(float range){ m_range = range;}

  int Set(char* mess, float value);

  short DoProcess();

};

#endif


