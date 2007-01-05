// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Reson.h: interface of the Reson class (2nd order          //
//           band-pass filter).                               //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _RESON_H 
#define _RESON_H

#include "Filter.h"


class Reson : public Filter
 
{
 protected:
  SndObj* m_inputfr;
  SndObj* m_inputbw;

 public:

  Reson();
  Reson(float fr, float bw, SndObj* inObj, SndObj* inputfreq = 0, 
	SndObj* inputbw = 0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  void SetFreq(float fr, SndObj* InFrObj);
  void SetBW(float bw, SndObj* InBWObj);

  ~Reson();

  int Connect(char* mess, void* input);
  short DoProcess();

};

#endif


