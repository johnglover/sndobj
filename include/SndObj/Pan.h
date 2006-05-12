// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _PAN_H 
#define _PAN_H 
#include "SndObj.h"
#include <math.h>


const double  squrt2o2 = sqrt(2.) / 2.; 

 class Pan : public SndObj{

               protected:

    SndObj*       m_channel;
	float         m_pan;
	int           m_res;
	float*        m_panpos;
     SndObj*        m_inputpan;
    inline float Panning(float pan, int chan);
   
               public:
   
	SndObj*  left;
	SndObj*  right;
    Pan();                            
    Pan(float pan, SndObj* InObj, SndObj* InPan = 0, int res=1024, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
    ~Pan();
  
    void  SetPan(float pan, SndObj* InPan = 0){
		 m_pan = pan;
		 m_inputpan = InPan;
	}
    int Set(char* mess, float value);
    int Connect(char* mess, void* input);
	
      short DoProcess();          
      char* ErrorMessage();
                             };


#endif
