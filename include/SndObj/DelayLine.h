// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  DelayLine.h: interface of the Delayline class             //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _DELAYLINE_H
#define _DELAYLINE_H


#include "SndObj.h"


class DelayLine : public SndObj 
{

 protected:
  float*     m_delay;    // delay line
  float      m_delaytime; // delay time
  long       m_size;      // delay line size in samples
  long       m_wpointer; // write pointer
  long       m_rpointer; // read pointer

  void   PutSample(float sample){
    m_delay[m_wpointer] = sample;
    m_wpointer = (m_wpointer != m_size-1 ? m_wpointer+1 : 0);
  }

		  
  float   GetSample(){
    float out;
    out = m_delay[(m_rpointer%=m_size)];
    m_rpointer++;
    return out;
  }

  float  GetSample(float pos){
    int p = (int) pos, pp1 = (p == m_size-1 ? 0 : p+1);
    float frac = pos - p; 
    return  m_delay[p] + frac*(m_delay[pp1] - m_delay[p]);
  }

  float  GetSample(long pos){
    return m_delay[pos];
  }
     

 public:
  DelayLine();           
  DelayLine(float delaytime, SndObj* InObj, int vecsize=DEF_VECSIZE, float sr=DEF_SR);         
  ~DelayLine();

  float* Buffer() { return m_delay; } 

  long GetWritePointerPos() { return m_wpointer; }
  float GetDelayTime() { return m_size/m_sr; }

  void SetSr(float sr);
  void Reset();
  virtual void SetDelayTime(float delaytime);
	   
  int Set(char* mess, float value);

  short DoProcess();       
  char* ErrorMessage();

};

#endif




