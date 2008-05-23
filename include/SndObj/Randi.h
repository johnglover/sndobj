 
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
//  Randi.: interface of the Randi class                     //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _RANDI_H 
#define _RANDI_H


#include "Randh.h"

class Randi : public Randh {

 protected:
 
  //float m_fr; 
  //long m_period;
  //long m_count;   
  //SndObj* m_inputfr;
  float m_target;
  float m_start;

 public:
   
  Randi();
  Randi(float fr,float amp,SndObj* InFrObj=0,
	SndObj* InAmpObj=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Randi();
 
  short DoProcess();
  
};
#endif 


                        


