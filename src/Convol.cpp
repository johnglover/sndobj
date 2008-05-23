 
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

///////////////////////////////////////////////
// Convol.cpp: Fast convolution using a tabulated
//             impulse response
//
//           VL, 2003
/////////////////////////////////////////////

#include "Convol.h"

void
Convol::fft(float* in, float* out){

  // FFT function
  rfftw_one(m_fwd, in, out);

}

void 
Convol::ifft(float* in, float* out) {

  // Inverse FFT function
  rfftw_one(m_inv, in, out);

}

void
Convol::mult(float *a, float *b, float *res){
 
  float re1, re2, im1, im2;
  int halfsize = m_fftsize/2;
  for(int i=2, i2=1; i < m_fftsize; i+=2){
    i2 = i/2;
    re1 = a[i2]; re2 = b[i2];
    im1 = a[m_fftsize-(i2)];
    im2 = b[m_fftsize-(i2)];
      
    res[i2] = re1*re2 - im1*im2;
    res[m_fftsize-(i2)]= re1*im2 + im1*re2;

  }
  res[0] = a[0]*b[0];
  res[halfsize] = a[halfsize]*b[halfsize];
}


Convol::Convol(){
  m_table = 0;
  m_impulse = 0;
  m_overlap =0;
  m_sigframe = 0;
  m_outframe = 0;
  m_count = 0; 
  AddMsg("impulse" ,21);
  AddMsg("scale" ,22);
  m_fwd = 0;
  m_inv = 0;
}

Convol::Convol(Table* impulse, SndObj* input, float scale,
	       int vecsize, float sr):
  SndObj(input, vecsize, sr){

  m_table = impulse;
  m_scale = scale;
  m_L = m_table->GetLen();

  for(m_fftsize=1; m_fftsize < 2*m_L - 1; m_fftsize *=2);
 
  m_impulse = new float[m_fftsize];
  m_overlap = new float[m_L-1];
  m_sigframe = new float[m_fftsize];
  m_outframe = new float[m_fftsize];

  m_fwd = rfftw_create_plan(m_fftsize, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);
  m_inv = rfftw_create_plan(m_fftsize, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE);

  for(int i=0; i<m_fftsize; i++){
    if(i < m_L) m_sigframe[i] = m_table->Lookup(i)*m_scale/m_fftsize;
    else m_sigframe[i] = 0.f;

    m_outframe[i] =0.f;
    if(i< m_L-1)m_overlap[i] =0.f;
  }



  fft(m_sigframe, m_impulse);
  m_count = 0;

  AddMsg("impulse" ,21);
  AddMsg("scale" ,22);

}

Convol::~Convol(){

  delete[] m_impulse;
  delete[] m_sigframe;
  delete[] m_overlap;
  delete[] m_outframe;
  rfftw_destroy_plan(m_fwd);
  rfftw_destroy_plan(m_inv);
}

int 
Convol::Connect(char* mess, void* input){

  switch(FindMsg(mess)){

  case 21:
    SetImpulse((Table *) input, m_scale);
    return 1;

  default:
    return SndObj::Connect(mess, input);

  }

}

int 
Convol::Set(char* mess, float value){

  switch(FindMsg(mess)){

  case 21:
    SetImpulse(m_table, value);
    return 1;

  default:
    return SndObj::Set(mess, value);

  }

}

void 
Convol::SetImpulse(Table* impulse, float scale){

  if(impulse == m_table){
    m_scale = scale;
    if(m_table){
      for(int i=0;i<m_L;i++)
	m_impulse[i] *= m_scale;
    }

  }

  if(m_table){
    delete[] m_impulse;
    delete[] m_sigframe;
    delete[] m_overlap;
    delete[] m_outframe;
    rfftw_destroy_plan(m_fwd);
    rfftw_destroy_plan(m_inv);
  }

  m_table = impulse;
  m_L = m_table->GetLen();

  for(m_fftsize=1; m_fftsize < 2*m_L - 1; m_fftsize *=2);

  m_impulse = new float[m_fftsize];
  m_overlap = new float[m_L-1];
  m_sigframe = new float[m_fftsize];
  m_outframe = new float[m_fftsize];

  m_fwd = rfftw_create_plan(m_fftsize, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);
  m_inv = rfftw_create_plan(m_fftsize, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE);

  for(int i=0; i<m_fftsize; i++){
    if(i < m_L) m_sigframe[i] = m_table->Lookup(i)*m_scale/m_fftsize;
    else m_sigframe[i] = 0.f;
   
    m_outframe[i] =0.f;
    if(i< m_L-1)m_overlap[i] =0.f;
  }

  fft(m_sigframe, m_impulse);
  m_count = 0;

}

short
Convol::DoProcess(){

  if(!m_error){
    if(m_input && m_table){
      int i;
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++) {
	if(m_enable) {
	  if(m_count == m_L){
	    // perform the convolution
	    for(i=0;i<m_L-1; i++)
	      m_overlap[i] = m_outframe[i+m_L];
	    // pad with zeros
	    for(i=m_L;i<m_fftsize; i++) m_sigframe[i] = 0.f;
	    // transform
	    fft(m_sigframe, m_outframe);
	    // multiply
	    mult(m_outframe, m_impulse, m_sigframe);
	    ifft(m_sigframe, m_outframe);
     
	    m_count = 0;
	  }
	  m_sigframe[m_count] = m_input->Output(m_vecpos)/m_fftsize;
	  // overlap-add
	  m_output[m_vecpos] = m_outframe[m_count] +
	    (m_count < m_L-1 ? m_overlap[m_count] : 0);
	  m_count++;
	}
	else m_output[m_vecpos] = 0.f;
      } 
      return 1;
    } else {
      m_error = 3;
      return 0;
    }
  }
  else return 0;
}


