// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Ring.h: interface of the ring class                       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _RING_H 
#define _RING_H
 
#include "SndObj.h"

 class Ring : public SndObj{

               protected:
    SndObj* m_input2;
          
               public:

    Ring();                            
    Ring(SndObj* InObj1, SndObj* InObj2, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
    ~Ring();
  
    void  SetInput1(SndObj* InObj){m_input=InObj; }
    void  SetInput2(SndObj* InObj){m_input2=InObj;}
  
    short DoProcess();           // ring modulator
    int Connect(char* mess, void* input);

                             };

#endif
