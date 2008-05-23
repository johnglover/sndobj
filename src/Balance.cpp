 
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

//************************************************************//
//  Balance.cpp: Implemenation of the balance object          //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#include "Balance.h"

Balance::Balance(){

  m_comp = 0;
  m_fr = 10.f;
  m_pow = m_pow1 = m_pow2 = 0.;

  if(!(m_delay = new double[4])){
    m_error = 12;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  if(!(m_delay2 = new double[4])){
    m_error = 12;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  m_delay[0] = m_delay[1]= m_delay[2] = m_delay [3] = 0.;
  m_delay2[0] = m_delay2[1]= m_delay2[2] = m_delay2[3] = 0.;
  
  // coeff vars                          
  double C = 1/(tan(PI*m_fr/m_sr));
  m_a0 = 1/(1 + sqrt(2.0)*C + (C*C)); 
  m_a1 = 2*m_a0; 
  m_b1 = 2*(1 - (C*C))*m_a0;
  m_b2 = (1 - sqrt(2.0)*C + (C*C))*m_a0;

  AddMsg("lowpass frequency", 21);
  AddMsg("comparator", 23);

}

Balance::Balance(SndObj* input1, SndObj* input2, 
                 float fr, int vecsize, float sr):
  SndObj(input1, vecsize, sr){

  m_comp = input2;
  m_fr = fr;

  m_pow = m_pow1 = m_pow2 = 0.;

  if(!(m_delay = new double[4])){
    m_error = 12;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  if(!(m_delay2 = new double[4])){
    m_error = 12;
#ifdef DEBUG
    cout << ErrorMessage();
#endif
    return;
  }
  m_delay[0] = m_delay[1]= m_delay[2] = m_delay2[3] = 0.;
  m_delay2[1] = m_delay2[1]= m_delay2[2] = m_delay2[3] = 0.;

  // coef vars                                   
  double C = 1/(tan(PI*m_fr/m_sr));
  m_a0 = 1/(1 + sqrt(2.0)*C + (C*C)); 
  m_a1 = 2*m_a0; 
  m_b1 = 2*(1 - (C*C))*m_a0;
  m_b2 = (1 - sqrt(2.0)*C + (C*C))*m_a0;

  AddMsg("lowpass frequency", 21);
  AddMsg("comparator", 23);
}

Balance::~Balance(){

  delete[] m_delay;
  delete[] m_delay2;

}

//////////////////// OPERATIONS ////////////////////////////
void
Balance::SetLPFreq(float fr){
  m_fr = fr;
  // coef vars                          
  double C = 1/(tan(PI*m_fr/m_sr));
  m_a0 = 1/(1 + sqrt(2.0)*C + (C*C)); 
  m_a1 = 2*m_a0; 
  m_b1 = 2*(1 - (C*C))*m_a0;
  m_b2 = (1 - sqrt(2.0)*C + (C*C))*m_a0;
}


void
Balance::SetSr(float sr){
  m_sr = sr;
  // coef vars
  double C = 1/(tan(PI*m_fr/m_sr));
  m_a0 = 1/(1 + sqrt(2.0)*C + (C*C)); 
  m_a1 = 2*m_a0; 
  m_b1 = 2*(1 - (C*C))*m_a0;
  m_b2 = (1 - sqrt(2.0)*C + (C*C))*m_a0;
}

int
Balance::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetLPFreq(value);
    return 1;

  case 1:
    SetSr(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}

int
Balance::Connect(char* mess, void* input){

  switch (FindMsg(mess)){

  case 23:
    m_comp = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess,input);
     
  }


}

short
Balance::DoProcess(){
  if(!m_error){
    if(m_input && m_comp){
      for(m_vecpos=0;m_vecpos < m_vecsize; m_vecpos++){
	if(m_enable){
	  m_pow2 = filter(rectify(m_input->Output(m_vecpos)), m_delay);
	  m_pow1 = filter(rectify(m_comp->Output(m_vecpos)), m_delay2);    
	  if(m_pow2>0){
	    m_pow  = m_pow1/m_pow2; 
	  }
	  else m_pow = HUGE_VAL;  
	  m_output[m_vecpos] = (float) (m_input->Output(m_vecpos)*m_pow);
	}
        else m_output[m_vecpos] = 0.f;
  
      }  
      return 1;
    }
    else {
      m_error = 11;
      return 0;
    }
  }
  else return 0;
}


char*
Balance::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 11:
    message = "DoProcess() failed. No input object(s).\n";
    break;

  case 12:
    message = "Error allocating memory.\n";
    break;

  default:
    message = SndObj::ErrorMessage();
    break;
  }

  return message;

}
