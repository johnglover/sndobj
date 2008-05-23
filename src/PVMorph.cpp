 
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

#include "PVMorph.h"

PVMorph::PVMorph(){


  m_offset2 = 0.f;
  m_interpobj2 = 0;
  AddMsg("frequency morph", 41);
  AddMsg("amplitude morph", 41);
}

PVMorph::PVMorph(float morphfr, float morpha, SndObj* input1, SndObj* input2,
		 SndObj* inmorphfr, SndObj* inmorpha, int vecsize, float sr)
  :SpecInterp(morphfr, input1, input2, inmorphfr, vecsize, sr)
{

  m_offset2 = morpha;
  m_interpobj2 = inmorpha;
  AddMsg("frequency morph", 41);
  AddMsg("amplitude morph", 41);
}

PVMorph::~PVMorph(){

}


int
PVMorph::Connect(char* mess, void* input){

  switch(FindMsg(mess)){

  case 41:
    SetFreqMorph(m_offset, (SndObj*) input);
    return 1;

  case 42:
    SetAmpMorph(m_offset2, (SndObj*) input);
    return 1;

  default:
    return SpecInterp::Connect(mess, input);

  }


}

int
PVMorph::Set(char* mess, float value){

  switch(FindMsg(mess)){

  case 41:
    SetFreqMorph(value, m_interpobj);
    return 1;
    
  case 42:
    SetAmpMorph(value, m_interpobj2);
    return 1;


  default:
    return SpecInterp::Set(mess, value);

  }


}

short
PVMorph::DoProcess(){
	
  if(!m_error){
    if(m_input && m_input2){
      float morphfr,fr1, fr2;
      double ratio;
      float morpha, amp1, amp2;
      morphfr =  m_offset + (m_interpobj ? m_interpobj->Output(0) : 0);
      morpha =  m_offset2 + (m_interpobj2 ? m_interpobj2->Output(0) : 0);
			
      morpha = morpha > 1 ? 1 : (morpha < 0 ? 0 : morpha);
      morphfr = morphfr > 1 ? 1 : (morphfr < 0 ? 0 : morphfr);

      for(m_vecpos = 2; m_vecpos < m_vecsize; m_vecpos+=2) {
	if(m_enable) {     
	  // interpolate amps
	  amp1 =m_input->Output(m_vecpos);
	  amp2 =m_input2->Output(m_vecpos);
	  m_output[m_vecpos] = amp1 + (amp2-amp1)*morpha;
	  // interpolate frs
	  fr1 = m_input->Output(m_vecpos+1);
	  fr2 = m_input2->Output(m_vecpos+1);
	  ratio = fr1 ? fr2/fr1 : HUGE_VAL;
	  ratio = ratio > 0 ? ratio : -ratio;
	  m_output[m_vecpos+1] = fr1 * pow((double)ratio, 
					   (double)morphfr);
	  // fudge against NaN-type result
	  if(!m_output[m_vecpos+1]) 
	    m_output[m_vecpos+1] = (m_vecpos/2)*m_sr/m_vecsize;
	}
	else 
	  m_output[0] = m_output[1] =
	    m_output[m_vecpos+1] = m_output[m_vecpos] = 0.f;
      } 
      amp1 =m_input->Output(0);
      amp2 =m_input2->Output(0);
      m_output[m_vecpos] = amp1 + (amp2-amp1)*morpha;
      amp1 =m_input->Output(1);
      amp2 =m_input2->Output(1);
      m_output[m_vecpos] = amp1 + (amp2-amp1)*morpha;
      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;
	
}
