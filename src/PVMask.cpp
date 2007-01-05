// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "PVMask.h"

PVMask::PVMask(){
	
  m_maskgain = 0.f;
  m_dynamic = false;
  AddMsg("mask gain", 41);
  AddMsg("mask input", 42);
  AddMsg("mask table", 43);
}

PVMask::PVMask(float maskgain, SndObj* input, SndObj* mask,
	       SndObj* inmaskgobj, int vecsize, float sr)
  :SpecInterp(maskgain, input, inmaskgobj, 
	      inmaskgobj, vecsize, sr)
{
	
  m_maskgain = maskgain;
  m_dynamic = true;
  AddMsg("mask gain", 41);
  AddMsg("mask input", 42);
  AddMsg("mask table", 43);
}

PVMask::PVMask(float maskgain, Table* masktable, SndObj* input,
	       SndObj* inmaskgobj, int vecsize, float sr)
  :SpecInterp(maskgain, input, 0, 
	      inmaskgobj, vecsize, sr)
{
	
  m_maskgain = maskgain;
  if(masktable->GetLen() >= vecsize){
    m_dynamic = false;
    m_spectable = masktable;
  }
  else m_dynamic = true;

  AddMsg("mask gain", 41);
  AddMsg("mask input", 42);
  AddMsg("mask table", 43);
}


PVMask::~PVMask(){
	
}


int
PVMask::Connect(char* mess, void* input){
	
  switch(FindMsg(mess)){
		
  case 41:
    SetMaskGain(m_maskgain, (SndObj*) input);
    return 1;
		
  case 42:
    SetMaskInput((SndObj*)input);
    return 1;

  case 43:
    SetMaskTable((Table*)input);
    return 1;
  default:
    return SpecInterp::Connect(mess, input);
		
  }
	
}

int
PVMask::Set(char* mess, float value){
	
  switch(FindMsg(mess)){
		
  case 41:
    SetMaskGain(value, m_interpobj);
    return 1;
		
  default:
    return SpecInterp::Set(mess, value);
		
  }
	
	
}

short
PVMask::DoProcess(){
	
  if(!m_error){
    if(m_input && (m_input2 || !m_dynamic)){

      float mag, magmask, freq, maskgain;
      maskgain = m_maskgain + (m_interpobj ? m_interpobj->Output(0) : 0.f);

      mag = m_input->Output(0);
      if(m_dynamic)
	magmask = m_input2->Output(0);
      else
	magmask = m_spectable->Lookup(0);

      m_output[m_vecpos] = (mag > magmask ? 
			    mag : mag*maskgain);
      if(m_dynamic)
	magmask = m_input2->Output(1);
      else 
	magmask = m_spectable->Lookup(1);

      mag = m_input->Output(1);
      m_output[m_vecpos] = (mag > magmask ? 
			    mag : mag*maskgain);
					
      for(m_vecpos=2; m_vecpos < m_vecsize; m_vecpos+=2){
			
	mag = m_input->Output(m_vecpos);
	freq = m_input->Output(m_vecpos+1);
	if(m_dynamic) 
	  magmask = m_input2->Output(m_vecpos);
	else
	  magmask = m_spectable->Lookup(m_vecpos);

	m_output[m_vecpos] = (mag > magmask ? 
			      mag : mag*maskgain);
	m_output[m_vecpos+1] = freq;
			
      }
      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;

}


