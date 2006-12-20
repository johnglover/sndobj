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


                        


