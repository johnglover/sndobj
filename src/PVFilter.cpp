 
////////////////////////////////////////////////////////////////////////
// This file is part of the SndObj library
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
//
// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "PVFilter.h"

PVFilter::PVFilter(){
	
  m_amnt = 0.f;
  m_dynamic = false;
  AddMsg("amount", 41);
  AddMsg("filter", 42);
  AddMsg("filter table", 43);
}

PVFilter::PVFilter(SndObj* input, SndObj* filspec, float amnt,
		   SndObj* amntobj, int vecsize, float sr)
  :SpecInterp(amnt, input, filspec, 
	      amntobj, vecsize, sr)
{
	
  m_amnt = amnt;
  m_dynamic = true;
  AddMsg("amount", 41);
  AddMsg("filter", 42);
  AddMsg("filter table", 43);
}

PVFilter::PVFilter(Table* filtable, SndObj* input, float amnt,
		   SndObj* amntobj, int vecsize, float sr)
  :SpecInterp(amnt, input, 0, 
	      amntobj, vecsize, sr)
{
	
  m_amnt = amnt;
  if(filtable->GetLen() >= vecsize){
    m_dynamic = false;
    m_spectable = filtable;
  }
  else m_dynamic = true;

  AddMsg("mask gain", 41);
  AddMsg("mask input", 42);
  AddMsg("mask table", 43);
}


PVFilter::~PVFilter(){
	
}


int
PVFilter::Connect(char* mess, void* input){
	
  switch(FindMsg(mess)){
		
  case 41:
    SetAmount(m_amnt, (SndObj*) input);
    return 1;
		
  case 42:
    SetFilterInput((SndObj*)input);
    return 1;

  case 43:
    SetFilterTable((Table*)input);
    return 1;
  default:
    return SpecInterp::Connect(mess, input);
		
  }
	
}

int
PVFilter::Set(char* mess, float value){
	
  switch(FindMsg(mess)){
		
  case 41:
    SetAmount(value, m_interpobj);
    return 1;
		
  default:
    return SpecInterp::Set(mess, value);
		
  }
	
	
}

short
PVFilter::DoProcess(){
	
  if(!m_error){
    if(m_input && (m_input2 || !m_dynamic)){

      float mag, fil, freq, amnt;
      amnt = m_amnt + (m_interpobj ? m_interpobj->Output(0) : 0.f);

      amnt = amnt > 1 ? 1.f : (amnt ? amnt : 0.f);

      if(m_dynamic){
	fil = m_input2->Output(0);
      }
      else
	fil = m_spectable->Lookup(0);

      mag = m_input->Output(0);
      m_output[m_vecpos] = mag*(1-amnt)+mag*fil*amnt;

      if(m_dynamic){
	fil = m_input2->Output(1);
      }
      else
	fil = m_spectable->Lookup(1);

      mag = m_input->Output(1);
      m_output[m_vecpos] = mag*(1-amnt)+mag*fil*amnt;
					
      for(m_vecpos=2; m_vecpos < m_vecsize; m_vecpos+=2){
			
	mag = m_input->Output(m_vecpos);
	freq = m_input->Output(m_vecpos+1);
	if(m_dynamic) {
	  fil = m_input2->Output(m_vecpos);
	}
	else
	  fil = m_spectable->Lookup(m_vecpos);

	m_output[m_vecpos] = mag*(1-amnt)+mag*fil*amnt;
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


