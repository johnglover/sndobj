 
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
//  SndIn.h: interface of the SndIn class.                    //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _SNDIN_H
#define _SNDIN_H

#include "SndObj.h"
#include "SndIO.h"

class SndIn : public SndObj {

 protected:

  SndIO* m_ioinput;
  short  m_channel;

 public:
   
  SndIn();
  SndIn(SndIO *input, short channel=1, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~SndIn();

  void SetInput(SndIO *input, short channel=1){
    m_ioinput = input;
    m_channel = channel;
  }

  int Connect(char* mess, void* input);
  int Set(char* mess, float value);
  short DoProcess();
  char* ErrorMessage();

};

#endif
