// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information
//
// PVMix.cpp: implementation of the PVMix class.
//
//////////////////////////////////////////////////////////////////////

#include "PVMix.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PVMix::PVMix()
{ }
PVMix::PVMix(SndObj* input, SndObj* input2, 
	     int vecsize,float sr):
  SpecMult(input, input2, vecsize, sr){
}

PVMix::~PVMix()
{
}


short
PVMix::DoProcess(){

  if(!m_error){
    if(m_input && m_input2){

      if(m_enable){	
	float amp1, amp2;

	amp1 = m_input->Output(0);
	amp2 = m_input2->Output(0);
	m_output[0] = amp1 > amp2 ? amp2 : amp1;
	amp1 = m_input->Output(1);
	amp2 = m_input2->Output(1);
	m_output[1] = amp1 > amp2 ? amp2 : amp1;	 
	 

	for(m_vecpos=2;m_vecpos < m_vecsize; m_vecpos+=2){
      
	  amp1 = m_input->Output(m_vecpos);
	  amp2 = m_input2->Output(m_vecpos);

	  if(amp2>amp1){
	    m_output[m_vecpos] = amp2;
	    m_output[m_vecpos+1] = m_input2->Output(m_vecpos+1);
	  }
	  else {
	    m_output[m_vecpos] = amp1;
	    m_output[m_vecpos+1] = m_input->Output(m_vecpos+1);
  	  }
  
	}
      }

      return 1;


    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;



}
