// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Gain.h: interface of the gain class                       //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _GAIN_H 
#define _GAIN_H
 
#include "SndObj.h"


 class Gain : public SndObj{

               protected:

    float         m_gain;  // gain factor in dB
       
               public:

    Gain();                            
    Gain(float gain, SndObj* InObj, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
    ~Gain();

	int Set(char* mess, float value);
      void  SetGain(float gain);
	void  SetGainM(float gain_multiplier) { m_gain = gain_multiplier; }
    
    float dBToAmp(float amp);      // changes amp in dB to amp multiplier
    short DoProcess();           // change gain

                             };


#endif
