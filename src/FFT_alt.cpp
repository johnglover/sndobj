 
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
/////////////////////////////////////////////////
// FFT.cpp : implementation of the FFT class
//           short-time fast fourier transform
//           Victor Lazzarini, 2003
/////////////////////////////////////////////////
#include "FFT.h"

FFT::FFT(){

m_table = 0;

// hopsize controls decimation
// we have vecsize/hopsize overlapping frames
// since SndObj has already allocated the output
// we have to de-allocate

m_fftsize = DEF_FFTSIZE;
SetVectorSize(DEF_FFTSIZE);
m_hopsize = DEF_VECSIZE;

delete[] m_output;
if(!(m_output = new float[m_vecsize])){
		m_error = 1;
		cout << ErrorMessage();
		return;
	}

m_frames = m_fftsize/m_hopsize;

m_sigframe = new float*[m_frames];
m_ffttmp = new float[m_fftsize];
m_counter = new int[m_frames];
m_halfsize = m_fftsize/2;

int i;
for(i = 0; i < m_frames; i++){
m_sigframe[i] = new float[m_fftsize];
memset(m_sigframe[i], 0, m_fftsize*sizeof(float));
m_counter[i] = i*m_hopsize;
}

m_plan = rfftw_create_plan(m_fftsize, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);

AddMsg("scale", 21);
AddMsg("fft size", 22);
AddMsg("hop size", 23);
AddMsg("window", 24);
m_scale = 1.f;
m_norm = m_fftsize;
m_cur =0;
}


FFT::FFT(Table* window, SndObj* input, float scale, 
		 int fftsize, int hopsize, int vecsize, float sr):
         SndObj(input, vecsize, sr){

m_table = window;

m_hopsize = hopsize;
m_fftsize = fftsize;
m_frames = m_fftsize/m_hopsize;

m_sigframe = new float*[m_frames];
m_ffttmp = new float[m_fftsize];
m_counter = new int[m_frames];
m_halfsize = m_fftsize/2;

int i;
for(i = 0; i < m_frames; i++){
m_sigframe[i] = new float[m_fftsize];
memset(m_sigframe[i], 0, m_fftsize*sizeof(float));
m_counter[i] = i*m_hopsize;
}

m_plan = rfftw_create_plan(m_fftsize, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);

AddMsg("scale", 21);
AddMsg("fft size", 22);
AddMsg("hop size", 23);
AddMsg("window", 24);
m_scale = scale;
m_norm = m_fftsize/m_scale;
m_cur =0;
}


FFT::~FFT(){
rfftw_destroy_plan(m_plan);
delete[] m_counter;
delete[] m_sigframe;
delete[] m_ffttmp;
}

void
FFT::SetFFTSize(int fftsize){
SetVectorSize(m_fftsize = fftsize);
ReInit();
}

void
FFT::SetHopSize(int hopsize){
m_hopsize = hopsize;
ReInit();
}

void 
FFT::ReInit(){	

rfftw_destroy_plan(m_plan);
delete[] m_counter;
delete[] m_sigframe;
delete[] m_ffttmp;
delete[] m_output;

if(!(m_output = new float[m_vecsize])){
		m_error = 1;
		cout << ErrorMessage();
		return;
	}


m_frames = m_fftsize/m_hopsize;
m_sigframe = new float*[m_frames];
m_ffttmp = new float[m_fftsize];
m_counter = new int[m_frames];
m_halfsize = m_fftsize/2;
int i;
for(i = 0; i < m_frames; i++){
m_sigframe[i] = new float[m_fftsize];
memset(m_sigframe[i], 0, m_fftsize*sizeof(float));
m_counter[i] = i*m_hopsize;
}

m_plan = rfftw_create_plan(m_vecsize, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);
m_cur =0;
m_norm = m_fftsize/m_scale;
}


int
FFT::Set(char* mess, float value){

	switch(FindMsg(mess)){

	case 21:
	SetScale(value);
	return 1;

	case 22:
	SetFFTSize((int) value);
	return 1;

	case 23:
	SetHopSize((int) value);
	return 1;
	
	default:
	return	SndObj::Set(mess, value);

	}
}

int
FFT::Connect(char* mess, void *input){

	switch(FindMsg(mess)){

    case 32:
    SetWindow((Table *) input);
	return 1;

	default:
	return SndObj::Connect(mess, input);

	}

}

short
FFT::DoProcess(){

if(!m_error){
 if(m_input){
	 if(m_enable){
	 int i; float sig = 0.f;
	 for(m_vecpos = 0; m_vecpos < m_hopsize; m_vecpos++) {
        // signal input
		sig = m_input->Output(m_vecpos);		
		// distribute to the signal fftframes and apply the window
		// according to a time pointer (kept by counter[n])
      for(i=0;i < m_frames; i++){
	   m_sigframe[i][m_counter[i]]= sig*m_table->Lookup(m_counter[i]);
       m_counter[i]++;		   
	  }  
	 } 
 // every hopsize samples
 // set the current sigframe to be transformed
 m_cur--; if(m_cur<0) m_cur = m_frames-1;  
 // transform it and fill the output buffer
 fft(m_sigframe[m_cur]); 
 // zero the current sigframe time pointer
 m_counter[m_cur] = 0;
 return 1;

	 } else { // if disabled
		   for(m_vecpos=0; m_vecpos < m_hopsize; m_vecpos++)
			  m_output[m_vecpos] = 0.f;
              return 1;
			  }
 } else {
	m_error = 3;
	return 0;
 }
}
else 
return 0;
}


void
FFT::fft(float* signal){

// FFT function
for(int i=0; i < m_fftsize; i++)
     m_output[i] = signal[i]/m_norm;
rfft(signal, m_fftsize/2, 1);

}


void bitreverse(float x[], int N){

float rtemp, itemp;
int i, j, m;
for(i = j = 0 ; i < N ; i += 2 , j += m) {


if(j > i) {

rtemp = x[j]; itemp = x[j+1];  /*complex exchange*/
x[j] = x[i] ; x[j+1] = x[i+1];
x[i] = rtemp ; x[i+1] = itemp; 


}
for (m = N>>1; m >= 2 && j >= m; m >>= 1 )
j -= m ;
}
}

void
cfft(float x[], int NC, int  forward){


float  wr, wpr, wi, wpi, theta, scale;
int mmax, ND, m, i, j, delta;
ND = NC << 1;

bitreverse(x, ND);
for(mmax = 2; mmax < ND; mmax = delta)
{
delta = mmax<<1;
theta = TWOPI/(forward? mmax : -mmax);
wpr = (float) (-2.*pow(sin(0.5*theta), 2.));
wpi = (float)sin(theta);
wr = 1. ;
wi = 0. ;
for(m = 0; m< mmax ; m += 2){

float rtemp, itemp;

for(i = m; i < ND; i += delta){

j = i + mmax;
rtemp = wr*x[j] - wi*x[j+1];
itemp = wr*x[j+1]+ wi*x[j];
x[j] = x[i] - rtemp;
x[j+1] = x[i+1] - itemp;
x[i] += rtemp;
x[i+1] += itemp;

}

wr = (rtemp = wr)*wpr - wi*wpi + wr;
wi = wi*wpr + rtemp*wpi + wi;

}
}
/*
*
*scale output
*
*
*/

scale = (float)(forward ? 1./ND : 1.) ;
for (i=0; i < ND; i++)
x[i] *= scale;
}


/**********************************************/
/* FFT function                               */
/**********************************************/

void
FFT::rfft(float x[], int N, int forward){
float c1, c2, h1r, h1i, h2r, h2i, wr, wi, wpr;
float   wpi, temp, theta, xr, xi;

int i, i1, i2, i3, i4, N2p1 ;

theta = PI/N;
wr= 1. ;
wi = 0. ;
c1 = 0.5 ;

if (forward){

c2 = -0.5 ;

cfft(x, N, forward);

xr = x[0];
xi = x[1];

}else {

c2 = 0.5 ;
theta = -theta ;
xr = x[1] ;
xi = 0. ;
x[1] = 0. ;

}

wpr = (float)(-2.*pow(sin(0.5*theta), 2.));
wpi = (float)sin(theta);
N2p1 = (N<<1) + 1;

for(i=0; i<= N>>1 ; i++){

i1 = i<<1 ;
i2 = i1 + 1 ;
i3 = N2p1 - i2 ;
i4 = i3 + 1;

if(i == 0){

h1r = c1*(x[i1] + xr);
h1i = c1*(x[i2] - xi);
h2r = -c2*(x[i2] + xi);
h2i = c2*(x[i1] - xr);
x[i1] = h1r + wr*h2r - wi*h2i ;
x[i2] = h1i + wr*h2i + wi*h2r ;
xr = h1r - wr*h2r + wi*h2i;
xi = -h1i + wr*h2i + wi*h2r;
}

else {

h1r = c1*(x[i1] + x[i3] ) ;
h1i = c1*(x[i2] - x[i4] ) ;
h2r = -c2*(x[i2] + x[i4] ) ;
h2i = c2*(x[i1] - x[i3] ) ;
x[i1] = h1r + wr*h2r - wi*h2i ; 
x[i2] = h2i + wr*h2i + wi*h2r ;
x[i3] = h1r - wr*h2r + wi*h2i ;
x[i4] = -h1i + wr*h2i + wi*h2r ;

}

wr = (temp = wr)*wpr - wi*wpi + wr ;
wi = wi*wpr + temp*wpi + wi;

}
if(forward)
x[1] = xr ;

else
cfft(x, N, forward);
}

