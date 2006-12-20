// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Balance.h: interface of the Balance class                 //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _BALANCE_H
#define _BALANCE_H

#include "SndObj.h"


class Balance : public SndObj {

                       protected: 

  float m_fr; 
  double m_pow;
  double m_pow1;
  double m_pow2;
  double m_a0, m_a1, m_b1, m_b2;
  double* m_delay2;
  double* m_delay;
  SndObj* m_comp;

  float rectify(float val){
	return (val < 0 ? val*-1 : val); 
  }
  double filter(double in, double* delay);

			 public:
  
  void SetInput(SndObj* input1, SndObj* input2){
                m_comp = input2;
                m_input = input1;
               }
  void  SetLPFreq(float fr);
  void SetSr(float sr);
  int Set(char* mess, float value);

  Balance();
  Balance(SndObj* input1, SndObj* input2, float fr=10.f,
	  int vecsize=DEF_VECSIZE, float sr = DEF_SR);
  ~Balance();
  char* ErrorMessage();
  short DoProcess();
  int Connect(char* mess, void* input);

                              };

double inline
Balance::filter(double in, double* delay)
                 { 
    double out = 0.f;          // output
    // filtering 
    out = m_a0*in + m_a1*delay[2] + m_a0*delay[3] 
           - m_b1*delay[0] - m_b2*delay[1];  
    // recirculate the delay line
    delay[3] = delay[2];       // past inputs
    delay[2] = in;
    delay[1] = delay[0];       // past outputs
    delay[0] = out;    
    return(out);               // output the float value
		  
                 }  
#endif




















