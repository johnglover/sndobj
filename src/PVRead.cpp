 
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

#include "PVRead.h"

PVRead::PVRead(){
	
  m_ioinput = 0;
  m_plan = 0;
  m_fftsize = 0;
  m_winsize = 0;
  m_channels = 0;
  m_hopsize = 0;
  m_maxbuffs =0;
  m_hopsize = 0;
  delete[] m_counter;
  delete[] m_ffttmp;
  m_count = 0;
  m_rotcount = 0;
  m_first = 0;
  m_last = 0;
  delete[] m_sigframe;
  m_outobj = 0;
  m_win = 0;
  AddMsg("timescale", 41);
	
}

PVRead::PVRead(char* name, float timescale, int vecsize,
	       float sr):
  PVS(0, 0, 0, vecsize, sr)
{
		
  m_ioinput = new SndPVOCEX(name, READ);
  if(m_ioinput->IsPvocex()){
    m_fftsize = m_ioinput->GetFFTSize();
    m_winsize = m_ioinput->GetWindowLength();
    m_channels = m_ioinput->GetChannels();
    m_hopsize = m_ioinput->GetHopSize();
    m_maxbuffs = 4*(m_winsize/m_hopsize);
    m_hopsize = (int)(m_hopsize/timescale);
    m_count = 0;
    m_ffttmp = new float[m_fftsize];
    m_counter = new int[m_channels*m_maxbuffs];
    m_halfsize = m_fftsize/2;
    m_fund = m_sr/m_fftsize;
    m_first = new int[m_channels];
    m_last = new int[m_channels];	
    m_phases = new float[m_halfsize];
    memset(m_phases, 0, sizeof(float)*m_halfsize);
    m_sigframe = new float*[m_channels*m_maxbuffs];
    m_outobj = new SndObj*[m_channels];
    m_win = new float[m_winsize];
    m_plan = rfftw_create_plan(m_fftsize, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE);
    int i;
    for(i =0; i < m_channels*m_maxbuffs; i++){
      m_sigframe[i] = new float[m_fftsize];
      memset(m_sigframe[i], 0, sizeof(float)*m_fftsize);
    }
    for(i=0; i < m_channels; i++){
      m_first[i] = m_last[i] = i*m_maxbuffs;
      m_outobj[i] = new SndObj(0, vecsize, sr);
    }
    m_rotcount = 0;
    m_factor = (m_hopsize*TWOPI)/m_sr;
		
    float alpha = (m_ioinput->GetWindowType() == HAMMING ?
		   0.54f : 0.5f);
		
    m_table = new HammingTable(m_winsize, alpha);
		
    float x = - (m_winsize-1)/2.;
    for(i=0; i<m_winsize;i++,x += 1.)
      m_win[i] = m_table->Lookup(i)*
	((m_winsize > m_fftsize) && ( x != 0.) ? 
	 (m_hopsize*sin(PI*x/m_hopsize)/(PI*x)): 1.) ;
	 	

  } 
  else {
    m_error = 41;
    delete m_ioinput;
    m_ioinput = 0;
  }
  AddMsg("timescale", 41);

}

PVRead::~PVRead(){
  if(m_ioinput) {	
    delete m_ioinput;
    delete[] m_first;
    delete[] m_last;
    delete[] m_outobj;
    delete[] m_table;
    delete[] m_win;

  }

}

int
PVRead::Set(char* mess, float value){
	
  switch (FindMsg(mess)){
		
  case 41:
    SetTimescale(value);
    return 1;
		
  default:
    return SndObj::Set(mess,value);
		
  }
	
	
}

void
PVRead:: SetTimescale(float timescale){
  if(m_ioinput){
    m_hopsize = (int)(m_ioinput->GetHopSize()/timescale);
    m_factor = (m_hopsize*TWOPI)/m_sr;
    if(m_winsize > m_fftsize){
      float* tmp = m_win;
      float x = - (m_winsize-1)/2.;
      float* newin = new float[m_winsize];
      for(int i=0; i<m_winsize;i++, x += 1.)
	tmp[i] = m_table->Lookup(i)*
	  ((m_winsize > m_fftsize) && ( x != 0.) ? 
	   (m_hopsize*sin(PI*x/m_hopsize)/(PI*x)): 1.);
      m_win = newin;
      delete[] tmp;
			
    }
  }
}

void
PVRead:: SetInput(char* name){
  if(m_ioinput){
    delete[] m_table;
    delete[] m_win;
    delete[] m_ffttmp;
    delete[] m_first;
    delete[] m_last;
    delete[] m_counter;
    delete[] m_outobj;
    delete m_ioinput;
    rfftw_destroy_plan(m_plan);
  }
	
  m_ioinput = new SndPVOCEX(name, READ);
  if(m_ioinput->IsPvocex()){
    m_enable = 1;
    m_fftsize = m_ioinput->GetFFTSize();
    m_winsize = m_ioinput->GetWindowLength();
    m_channels = m_ioinput->GetChannels();
    m_hopsize = m_ioinput->GetHopSize();
    m_maxbuffs = 4*(m_winsize/m_hopsize);
    m_hopsize = (int)(m_hopsize);
    m_count = 0;
    m_ffttmp = new float[m_fftsize];
    m_counter = new int[m_channels*m_maxbuffs];
    m_halfsize = m_fftsize/2;
    m_fund = m_sr/m_fftsize;
    m_phases = new float[m_halfsize];
    memset(m_phases, 0, sizeof(float)*m_halfsize);
    m_first = new int[m_channels];
    m_last = new int[m_channels];

    m_sigframe = new float*[m_channels*m_maxbuffs];
    m_outobj = new SndObj*[m_channels];
    m_win = new float[m_winsize];
    m_plan = rfftw_create_plan(m_fftsize, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE);
    int i;
    for(i =0; i < m_channels*m_maxbuffs; i++){
      m_sigframe[i] = new float[m_winsize];
      memset(m_sigframe[i], 0, sizeof(float)*m_fftsize);
    }
    for(i=0; i < m_channels; i++){
      m_first[i] = m_last[i] = i*m_maxbuffs;
      m_outobj[i] = new SndObj(0, m_vecsize, m_sr);
    }
    m_rotcount = 0;
    m_factor = (m_hopsize*TWOPI)/m_sr;
		
    float alpha = (m_ioinput->GetWindowType() == HAMMING ?
		   0.54f : 0.5f);
		
    m_table = new HammingTable(m_winsize, alpha);
		
    float x = - (m_winsize-1)/2.;
    for(i=0; i<m_winsize;i++, x += 1.)
      m_win[i] = m_table->Lookup(i)*
	((m_winsize > m_fftsize) && ( x != 0.) ? 
	 (m_hopsize*sin(PI*x/m_hopsize)/(PI*x)): 1.) ;
  } else{
    m_error = 41;
    delete m_ioinput;
    m_ioinput = 0;
  }
}

void
PVRead::synthesis(float* signal){
  double pha;
  int i2;

  m_ffttmp[0] = signal[0]; 
  m_ffttmp[m_halfsize] = signal[1];

  for(int i=0;i<m_fftsize; i+=2){ 
    i2 = i/2;
    m_phases[i2] += signal[i+1] - m_fund*i2; 
    pha = m_phases[i2]*m_factor;
    m_ffttmp[i2] = signal[i]*cos(pha);
    m_ffttmp[m_fftsize-(i2)] = signal[i]*sin(pha);
  }

  rfftw_one(m_plan, m_ffttmp, signal);
}

short
PVRead::DoProcess(){
  if(!m_error) {
    if(m_ioinput){
      int i, chan; float out=0.f, outsum=0.f;
		
      // for every sample
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
	if(m_enable){
	  // if we completed a hop period
	  if(m_count == m_hopsize) m_count = 0;
				
	  // for each input channel
	  for(chan=0; chan < m_channels; chan++){
					
	    // if we are starting a hop period
	    if(m_count==0){
	      // set the last frame to the next in the circular buffer
	      m_last[chan]++;
	      if(m_last[chan] == m_maxbuffs*(chan+1)) 
		m_last[chan] = m_maxbuffs*chan;
	      // read the input frame for this channel
	      m_ioinput->Read();
	      for(i=0; i < m_fftsize; i++)  
		m_sigframe[m_last[chan]][i] = m_ioinput->Output(i*(chan+1));
	      // re-synthesise
	      synthesis(m_sigframe[m_last[chan]]);
	      // set the frame counter to 0;
	      m_counter[m_last[chan]] = 0;
	    } 
	    // overlap-add, using the time index pointer
	    // to unrotate the frame into the output
	    // multiplying it by the synthesis window
	    // and unfolding it
	    for(i=m_first[chan]; ; i++){
	      if(i == m_maxbuffs*(chan+1)) i = m_maxbuffs*chan;
	      out +=  m_sigframe[i][m_rotcount]*m_win[m_counter[i]];
	      m_counter[i]++;
	      if(i == m_last[chan]) break;
						
	    }
	    // frame counter counts up to the
	    // window size. If the window size is
	    // larger than the fftsize, then the
	    // frame will be unfolded (basically windowed
	    // by a sync window and written)
					
	    if(m_counter[m_first[chan]] == m_winsize){
	      m_first[chan]++;
	      if(m_first[chan] == m_maxbuffs*(chan+1)) 
		m_first[chan] = m_maxbuffs*chan;
	    }
	    *(m_outobj[chan]) << out;
	    outsum += out;
	    out = 0.f;
					
	  }
				
	  m_count++;
	  m_rotcount++;
	  if(m_rotcount==m_fftsize) m_rotcount=0;
	  m_output[m_vecpos] = outsum;
	  outsum = 0.f;
	} else {
	  for(chan=0; chan < m_channels; chan++) *(m_outobj[chan]) << 0.f;
	  m_output[m_vecpos] = 0.f;
				
	}
      }
      return 1;
    }
    m_error =1;
  }
  return 0;
}





















