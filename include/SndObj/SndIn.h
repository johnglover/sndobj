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
