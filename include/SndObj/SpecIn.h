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
