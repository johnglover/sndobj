// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Tapi.h: interface of the Tapi class                        //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _TAPI_H
#define _TAPI_H


#include "Tap.h"


class Tapi : public Tap
{


 public:
  Tapi();           
  Tapi(SndObj* delayinput, DelayLine* DLine, int vecsize=DEF_VECSIZE, float sr=DEF_SR);         
  ~Tapi();
  void SetDelayInput(SndObj* delayinput){ m_input = delayinput; }
  int Connect(char* mess, void* input);

  short DoProcess();       


};

#endif
