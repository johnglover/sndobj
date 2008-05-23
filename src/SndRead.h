 
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


#ifndef SndRead_h_
#define SndRead_h_

#include "SndObj.h"
#include "SndFIO.h"



class SndRead : public SndObj {

 protected:
  SndFIO* m_ioinput;
  SndObj** m_outobj;
  float m_pitch;
  double m_pos;
  float m_scale;
  int m_channels;
  int m_count;

 public:

  SndObj* Outchannel(int channel){ return m_outobj[channel%m_channels];}

  SndRead();
  SndRead(char* name, float pitch=1.f, float scale=1.f,
	  int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~SndRead();

  void SetInput(char* name);
  void SetScale(float scale){ m_scale = scale; }
  void SetPitch(float pitch) { m_pitch = fabs(pitch); }

  int Set(char* mess, float value);
  short DoProcess();

};



#endif
