// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  VDelay.h: interface of the VDelay class                   //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _VDELAY_H
#define _VDELAY_H

#include "DelayLine.h"

class VDelay : public DelayLine
              {

	      protected:

      float m_dirgain;
      float m_fdbgain;
      float m_fwdgain;
      float m_vdtime;      
      float m_vrpointer;
    
      SndObj* m_inputvdt;
 	  SndObj* m_inputfdbg; 
      SndObj* m_inputfwdg;
      SndObj* m_inputdirg; 

               public:
       VDelay();           
       VDelay(float maxdelaytime, float fdbgain, float fwdgain, 
              float dirgain, SndObj* InObj, SndObj* InVdtime, 
              SndObj* InFdbgain=0, SndObj* InFwdgain=0,
              SndObj* InDirgain=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
	   VDelay(float maxdelaytime, float delaytime, float fdbgain, float fwdgain, 
              float dirgain, SndObj* InObj, SndObj* InVdtime = 0, 
              SndObj* InFdbgain=0, SndObj* InFwdgain=0,
              SndObj* InDirgain=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
       
       ~VDelay();

       int Set(char* mess, float value);
	   int Connect(char* mess, void* input);

	   void SetMaxDelayTime(float MaxDelaytime){
		   DelayLine::SetDelayTime(MaxDelaytime);
            }
	   void SetDelayTime(float delaytime){
		m_vdtime = delaytime;   
	   }
       void SetVdtInput(SndObj* InVdtime){ m_inputvdt = InVdtime; }
       void SetFdbgain(float fdbgain, SndObj* InFdbgain=0){
		   m_fdbgain = fdbgain;
		   m_inputfdbg = InFdbgain;
	   }
       void SetFwdgain(float fwdgain, SndObj* InFwdgain=0){
		   m_fwdgain = fwdgain;
		   m_inputfwdg = InFwdgain;
	   }
       void SetDirgain(float dirgain, SndObj* InDirgain=0){
		   m_dirgain = dirgain;
		   m_inputdirg = InDirgain;
	   }
       short DoProcess();       
       
	      };

#endif




