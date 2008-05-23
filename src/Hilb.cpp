 
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

////////////////////////////////////////////////
// Hilbert Transform filter implementation
//
// VL, 2001
/////////////////////////////////////////////////

#include "Hilb.h"

Hilb::Hilb(){

  if(!(m_channel = new SndObj[2])){
    m_error = 11;
    return;
  }
  real = &m_channel[0];
  imag = &m_channel[1];
  m_channel[0].SetInput(this);
  m_channel[1].SetInput(this);

  if(!(m_delay = new double[24])){
    m_error = 12;
    return;
  }
	
  if(!(m_coef = new double[12])){
    m_error = 12;
    return;
  }


  for(int i = 0; i<24; i++) m_delay[i] = 0.0;

  m_delay1 = m_delay;     // first allpass delay
  m_delay2 = &m_delay[4];  // second allpass delay
  m_delay3 = &m_delay[8];  // 1-sample delay
  m_delay4 = &m_delay[12];  // third allpass delay



  double polefreq[12], rc[12], alpha[12];;

  // calculate coefficients for allpass filters, 
  // based on sampling rate 
  for(int j=0; j<12; j++) {
    polefreq[j] = poles[j] * 15.0;
    rc[j] = 1.0 / (2.0 * PI * polefreq[j]);
    alpha[j] = 1.0 / rc[j];
    m_coef[j] = - (1.0 - (alpha[j] / (2.0 * m_sr))) /
      (1.0 + (alpha[j] / (2.0 * m_sr)));
  }
}

Hilb::Hilb(SndObj* input, int vecsize, float sr):
  SndObj(input, vecsize, sr){

  if(!(m_channel = new SndObj[2])){
    m_error = 11;
    return;
  }
  real = &m_channel[0];
  imag = &m_channel[1];

  if(vecsize != DEF_VECSIZE){
    m_channel[0].SetVectorSize(vecsize);
    m_channel[1].SetVectorSize(vecsize);
  }

  m_channel[0].SetInput(this);
  m_channel[1].SetInput(this);
    	
  if(!(m_coef = new double[12])){
    m_error = 12;
    return;
  }

  if(!(m_delay = new double[24])){
    m_error = 12;
    return;
  }



  for(int i = 0; i<24; i++) m_delay[i] = 0.0;

  m_delay1 = m_delay;     // first allpass delay
  m_delay2 = &m_delay[4];  // second allpass delay
  m_delay3 = &m_delay[8];  // 1-sample delay
  m_delay4 = &m_delay[12];  // third allpass delay



  double polefreq[12], rc[12], alpha[12];
  
  // calculate coefficients for allpass filters, 
  // based on sampling rate 
  
  for(int j=0; j<12; j++) {
    polefreq[j] = poles[j] * 15.0;
    rc[j] = 1.0 / (2.0 * PI * polefreq[j]);
    alpha[j] = 1.0 / rc[j];
    m_coef[j] = - (1.0 - (alpha[j] / (2.0 * m_sr))) /
      (1.0 + (alpha[j] / (2.0 * m_sr)));

  }
}

Hilb::~Hilb(){

  delete[] m_delay;
  delete[] m_coef;
  delete[] m_channel;
}

short
Hilb::DoProcess(){

  if(!m_error){
    if(m_input){
      int i, j;
      double sig;
      if(m_enable) { 
	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++) { 
	  sig = (double) m_input->Output(m_vecpos);
	  for(i=j=0; i<6; i++, j = i*2){
	    sig = allpass(sig,&m_delay[j],m_coef[i]);
	  }
	  m_output[m_vecpos] = (float) sig;

	}
	real->DoProcess();

	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++) { 
	  sig = m_input->Output(m_vecpos);
	  for(i=6,j=12; i<12; i++, j=i*2){
	    sig = allpass(sig,&m_delay[j],m_coef[i]);
	  }	
	  m_output[m_vecpos] += (float) sig;
	}
	imag->DoProcess();
      }

      else { // if !m_enable
	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++) 
	  m_output[m_vecpos] = 0.0; 
	real->DoProcess();
	imag->DoProcess();
      } 

      return 1;

    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;
}

char*
Hilb::ErrorMessage(){
 
  char* message;
   
  switch(m_error){

    // handle your error codes here 

  case 11:
    message = "Error allocating SndObj memory\n";
    break;

  case 12:
    message = "Error allocating memory \n";
    break;

  default:
    message = SndObj::ErrorMessage();
    break;
  
  }

  return message;

}
