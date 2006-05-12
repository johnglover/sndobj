// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//***********************************************************//
//  IADSR.h: interface of the IADSR class                    //
//      ADSR with user-defined init and end values           //
//                                                           //
//                                                           //
//***********************************************************//

#ifndef _IADSR_H 
#define _IADSR_H
 
#include "ADSR.h"

class IADSR : public ADSR{

            protected:

   float m_init;
   float m_end;

            public:

    IADSR();                            
    IADSR(float init, float att, float maxamp, float dec, float sus, 
         float rel, float end, float dur, SndObj* InObj = 0, int vecsize=DEF_VECSIZE,
		 float sr=DEF_SR);
    ~IADSR();
  
    void SetInit(float init){ m_init = init;}
    void SetEnd(float end){ m_end = end; }
    
	int Set(char* mess, float value);

    short DoProcess();           // change gain

                             };


#endif


