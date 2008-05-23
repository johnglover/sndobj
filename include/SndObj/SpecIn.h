 
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
//  SpecIn.h: interface of the SpecIn class.                    //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _SpecIn_H
#define _SpecIn_H

#include "SndObj.h"
#include "SndFIO.h"

class SpecIn : public SndObj {

 protected:

  SndIO* m_ioinput;
  short  m_channel;
  int m_initpos;

 public:
   
  SpecIn();
  SpecIn(SndFIO *input, short channel=1, int vecsize=DEF_FFTSIZE, float sr=DEF_SR);
  ~SpecIn();

  void SetInput(SndIO *input, short channel=1){
    m_ioinput = input;
    m_channel = channel;
    m_initpos = (m_channel-1)*m_vecsize;
  }
  int Connect(char* mess, void* input);
  int Set(char* mess, float value);
  short DoProcess();
  char* ErrorMessage();

};

#endif
