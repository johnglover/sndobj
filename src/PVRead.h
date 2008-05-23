 
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


#ifndef PVRead_h_
#define PVRead_h_

#include "PVS.h"
#include "HammingTable.h"
#include "SndPVOCEX.h"


class PVRead : public PVS {

 protected:

  SndPVOCEX* m_ioinput;
  int* m_last;
  int* m_first;
  int m_count;
  int m_channels;
  int m_winsize;
  int m_maxbuffs;

  float* m_win;

  SndObj** m_outobj;

 private:
  void inline synthesis(float* signal);

 public:

  SndObj* Outchannel(int channel){ return m_outobj[channel%m_channels];}

  int Set(char* mess, float value);
  void SetInput(char* name);
  void SetTimescale(float timescale);

  PVRead();
  PVRead(char* name, float timescale=1.0,int vecsize=DEF_VECSIZE,
	 float sr=DEF_SR);
  ~PVRead();

  short DoProcess();

};


#endif
