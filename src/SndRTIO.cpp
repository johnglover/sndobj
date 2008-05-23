 
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

/////////////////////////////////////////////////////
//  SndRTIO.cpp: implementation of the SndRTIO class
//  realtime audio IO 
//  currently supported on Irix, Linux (with OSS), Mac OSX (CoreAudio)
//  and Windows
//

#ifndef NO_RTIO
#if defined (SGI) || defined (OSS) || defined (WIN) || defined (ALSA)

#include "SndRTIO.h"
void
SndRTIO :: SndRTIO_init(short channels, int mode, int buffsize,
#if defined (WIN) || defined (ALSA)
			int buffno,
#endif
#ifdef SGI
			int DACQueue,
#endif
#ifdef OSS
			int DMAbuffsize,
#endif
			int encoding, 
			SndObj** inputs, 
			int vecsize, float sr,
#if defined (WIN) || defined (SGI)
			int dev)
#endif
#if defined (OSS) || defined (ALSA)
  char* device) 
#endif
{

m_mode = mode;

#ifdef WIN
short bytes_per_sample = encoding;
int n;
m_buffsize = buffsize;
m_buffno = buffno;
m_encoding = encoding;
m_ndx = 0;
m_dev = dev;
m_firsttime = true;
		
m_items = buffsize*m_channels;
m_count = buffsize*m_channels;

m_wfx = new WAVEFORMATEX;
m_hData = new HANDLE[m_buffno];
m_pwhdr = new WAVEHDR*[m_buffno];
m_hwhdr = new HGLOBAL[m_buffno];
m_buffer = new void*[m_buffno];

  for(n = 0; n < m_buffno; n++){
 	m_hData[n] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, buffsize*bytes_per_sample*m_channels); 

	if(!(m_buffer[n] = GlobalLock(m_hData[n]))){
     m_error = 14;
     return; 
	}	
	m_hwhdr[n] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, sizeof(WAVEHDR)); 

    if(!(m_pwhdr[n] = (WAVEHDR *)GlobalLock(m_hwhdr[n]))){
    m_error = 14;
    return; 
	}
	m_pwhdr[n]->lpData =  (char *) m_buffer[n];
	m_pwhdr[n]->dwBufferLength = m_buffsize*bytes_per_sample*m_channels;
	m_pwhdr[n]->dwLoops = 0;
	m_pwhdr[n]->dwFlags = 0;
    memset(m_buffer[n], 0, m_pwhdr[n]->dwBufferLength);

  }
	
  m_sp = (short *) m_buffer[m_ndx]; 
  m_cp = (char *) m_buffer[m_ndx]; 	 


 // fill formatex structure
 m_wfx->wFormatTag = WAVE_FORMAT_PCM;
 m_wfx->nChannels = m_channels;
 m_wfx->nSamplesPerSec = (long) m_sr; 
 m_wfx->nBlockAlign = (unsigned short)(m_channels*m_encoding);
 m_wfx->nAvgBytesPerSec = (long)(m_sr*m_encoding*m_channels);
 m_wfx->wBitsPerSample = m_encoding*8;



 if(m_mode == SND_INPUT){

	 
MMRESULT result;
m_cur = 0;

 // open output and prepare header
 if(result = 
	 waveInOpen(&m_hwi, m_dev, m_wfx, 0, 0, CALLBACK_NULL))
             
	 switch (result){

 case MMSYSERR_NOERROR:
	 break;

 case MMSYSERR_ALLOCATED:	//Specified resource is already allocated.
 m_error = 21;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 case MMSYSERR_BADDEVICEID:	//Specified device identifier is out of range.
 m_error = 22;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;
 
 case MMSYSERR_NODRIVER:	//No device driver is present.
 m_error = 23;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 case MMSYSERR_NOMEM:	    //Unable to allocate or lock memory.
 m_error = 24;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 case WAVERR_BADFORMAT:  	//Attempted to open with an unsupported waveform-audio format.
 m_error = 25;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 default:
 return;
                 }
 
 
 for(int n = 0; n < m_buffno; n++){

     if(result = 
	   waveInPrepareHeader(m_hwi, m_pwhdr[n], sizeof(WAVEHDR)))
               
	          switch (result){
 
 case MMSYSERR_NODRIVER:	//No device driver is present.
 m_error = 23;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 case MMSYSERR_NOMEM:	    //Unable to allocate or lock memory.
 m_error = 24;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 default:
 return ;
                 } //switch
	       
    } //for

 waveInStart(m_hwi);

	}
 else {  // if OUTPUT


MMRESULT result;

 // open output and prepare header
 if(result = 
	 waveOutOpen(&m_hwo, m_dev, m_wfx, 0, 0, CALLBACK_NULL))
             
	 switch (result){

 case MMSYSERR_NOERROR:
	 break;

 case MMSYSERR_ALLOCATED:	//Specified resource is already allocated.

 m_error = 21; 
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 case MMSYSERR_BADDEVICEID:	//Specified device identifier is out of range.
 
 m_error = 22;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;
 
 case MMSYSERR_NODRIVER:	//No device driver is present.
 
 m_error = 23;cout << ErrorMessage();
 return ;

 case MMSYSERR_NOMEM:	    //Unable to allocate or lock memory.
 m_error = 24;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 case WAVERR_BADFORMAT:  	//Attempted to open with an unsupported waveform-audio format.

 m_error = 25;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 default:
 return;
	}
 
 
 for(int n = 0; n < m_buffno; n++){

     if(result = 
	   waveOutPrepareHeader(m_hwo, m_pwhdr[n], sizeof(WAVEHDR)))
               
	          switch (result){
 
 case MMSYSERR_NODRIVER:	//No device driver is present. 
 m_error = 23;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 case MMSYSERR_NOMEM:	    //Unable to allocate or lock memory.

 m_error = 24;
#ifdef DEBUG
	cout << ErrorMessage();
#endif
 return ;

 default:
 return ;
                 } //switch
	       
        } //for


 }



#endif  // if defined WIN !!!!!!!!!!!!!!!
 
#ifdef SGI

int wsize, fmt;
m_channels = channels;
m_encoding = encoding;

  // set the encoding format

switch(m_encoding)
  {

  case FLOATSAM:
  fmt = AL_SAMPFMT_FLOAT; 
  m_buffsize = buffsize;
  if(!(m_buffer = new float[m_buffsize*m_channels])){
   m_error = 14;
   return;
  }
  m_fp = (float *)m_buffer;
  break;

  case BYTESAM:
  fmt = AL_SAMPFMT_TWOSCOMP;
  wsize =  AL_SAMPLE_8; 
  m_buffsize = buffsize;
  if(!(m_buffer = new char[m_buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_cp = (char *)m_buffer;
  break;

  case SHORTSAM:
  fmt =  AL_SAMPFMT_TWOSCOMP;
  wsize =  AL_SAMPLE_16; 
  m_buffsize = buffsize;
  if(!(m_buffer = new short[m_buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_sp = (short *)m_buffer; 
  break;

  case LONGSAM:
  fmt =  AL_SAMPFMT_TWOSCOMP;
  wsize = AL_SAMPLE_24; 
  m_buffsize = buffsize;
  if(!(m_buffer = new long[m_buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_lp = (long *)m_buffer;
 
  break;

  default:
    m_error = 12; //bad sample encoding
    return;

  }

m_dev = dev;

// get new config

if(!(m_config = alNewConfig())) 
   {
m_error = 13; // message = "alNewConfig() failed."
    return;
   }

// set the new config

if (alSetQueueSize(m_config, DACqueue) < 0) 
{
 m_error = 14; // message = "alSetQueueSize() failed."
 return;
	}

if (alSetChannels(m_config, m_channels) < 0) 
{
m_error = 15; // message = "alSetChannels() failed."
return;   
	}

if (alSetSampFmt(m_config, fmt) < 0) 
{
m_error = 16; // message = "alSetSampFmt() failed."
 return;
	}



if(m_encoding){

if (alSetWidth(m_config, wsize) < 0) {
 m_error = 17; // message = "alSetWidth() failed"
 return;   
	}

}


ALpv rpv[2];
rpv[0].param = AL_RATE;
rpv[0].value.ll = alDoubleToFixed((double)m_sr);
rpv[1].param = AL_MASTER_CLOCK;
rpv[1].value.i = AL_CRYSTAL_MCLK_TYPE;


 
if(m_mode == SND_INPUT){
  if(m_dev == AL_DEFAULT) m_dev = AL_DEFAULT_INPUT;

 if(alSetDevice(m_config, m_dev) < 0) {
 m_error = 18; // message = "alSetDevice() failed"
 return;   
	}
 if (alSetParams(m_dev, rpv, 2) < 0) {
 m_error = 19; // message = "alSetParams() failed"
 return;            
	        }

  m_port = alOpenPort("SndIO audio input", "r", m_config);
  if (!m_port) {
  m_error = 21; // message = "alOpenPort() failed"
  return;      
	}
 m_items = buffsize*m_channels;
 m_count = buffsize*m_channels;
	}
 else {
 
 if(alSetDevice(m_config, m_dev) < 0) {
 m_error = 18; // message = "alSetDevice() failed"
 return;   
	}

 if (alSetParams(m_dev, rpv, 2) < 0) {
 m_error = 19; // message = "alSetParams() failed"
 return;            
	        }

  m_port = alOpenPort("SndIO audio output", "w", m_config);
  if (!m_port) {
  m_error = 21; // message = "alOpenPort() failed"
  return;      
	}

 m_items = buffsize*m_channels;
 m_count = 0;

 }
#endif // if defined SGI !!!!!!!!!!!!!!!!

#ifdef OSS

int fmt, param;
m_channels = channels;

m_encoding = encoding;

  // set the encoding format

 switch(m_encoding) 
  {

  case BYTESAM:
  fmt = AFMT_U8;
  m_buffsize = buffsize*m_channels;
  if(!(m_buffer = new char[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_cp = (char *)m_buffer;
  break;

  case SHORTSAM_LE:
  fmt =  AFMT_S16_LE;
  m_buffsize = buffsize*2*m_channels;
  if(!(
  m_buffer = new short[buffsize*m_channels])){
  m_error = 11;
  return;
   }
  m_sp = (short *)m_buffer; 
  break;

  case SHORTSAM_BE:
  fmt =  AFMT_S16_BE;
  m_buffsize = buffsize*2*m_channels;
  if(!(m_buffer = new short[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_sp = (short *)m_buffer;
  break;

  default:
    m_error = 10; //bad sample encoding
    return;

  }
 

if(m_mode == SND_INPUT){
  
if((m_dev = open(device, O_RDONLY)) == -1){
   m_error = 12; // open failed
   return;
 }
m_items = buffsize*m_channels;
m_count = buffsize*m_channels;
} else
{
if((m_dev = open(device, O_WRONLY)) == -1){
   m_error = 12; // open failed
   return;
 }
m_items = buffsize*m_channels;
m_count = 0;
}


int fragsize = 1;
param  = 0;
while (fragsize < DMAbuffsize){
   fragsize <<= 1;
   param++;
 }
param |= 0x00ff0000;

if(ioctl(m_dev, SNDCTL_DSP_SETFRAGMENT, &param) == -1){
  m_error = 13; // couldn't set the DMA buffer size
  return;
 };
 



param = fmt;
if(ioctl(m_dev, SNDCTL_DSP_SETFMT, &param) == -1)
{
m_error = 15; // couldn't set the output format
return; 
	}



param = m_channels;
if(
ioctl(m_dev, SNDCTL_DSP_CHANNELS, &param) == -1)
{
m_error = 14; // couldn't set the output channel number
return;   
	}


param = (int) m_sr;
if(ioctl(m_dev, SNDCTL_DSP_SPEED, &param) == -1)
{
m_error = 16; // couldn't st the output sample rate
return;   
	}

#endif  // if defined OSS !!!!!!!!!!!!!!!!!!!

#ifdef ALSA // alsa IO
snd_pcm_format_t fmt;
snd_pcm_stream_t stream;
snd_pcm_hw_params_t *hwparams; 

m_channels = channels;
m_encoding = encoding;

  // set the encoding format

 switch(m_encoding) 
  {

  case BYTESAM:
  fmt = SND_PCM_FORMAT_U8;
  m_buffsize = buffsize*m_channels;
  if(!(m_buffer = new char[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_cp = (char *)m_buffer;
  break;

  case SHORTSAM_LE:
  fmt =  SND_PCM_FORMAT_S16_LE;
  m_buffsize = buffsize*2*m_channels;
  if(!(
  m_buffer = new short[buffsize*m_channels])){
  m_error = 11;
  return;
   }
  m_sp = (short *)m_buffer; 
  m_encoding = SHORTSAM;
  break;

  case SHORTSAM_BE:
  fmt =   SND_PCM_FORMAT_S16_BE;
  m_buffsize = buffsize*2*m_channels;
  if(!(m_buffer = new short[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_sp = (short *)m_buffer;
  m_encoding = SHORTSAM;
  break;

  case TWENTYFOUR_LE:
  fmt =   SND_PCM_FORMAT_S24_LE;
  m_buffsize = buffsize*4*m_channels;
  if(!(m_buffer = new short[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_lp = (long *)m_buffer;
  break;

  case TWENTYFOUR_BE:
  fmt =   SND_PCM_FORMAT_S24_BE;
  m_buffsize = buffsize*4*m_channels;
  if(!(m_buffer = new short[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_lp = (long *)m_buffer;
  break;

  case LONGSAM_LE:
  fmt =   SND_PCM_FORMAT_S32_LE;
  m_buffsize = buffsize*4*m_channels;
  if(!(m_buffer = new short[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_lp = (long *)m_buffer;
  break;

  case LONGSAM_BE:
  fmt =   SND_PCM_FORMAT_S32_BE;
  m_buffsize = buffsize*4*m_channels;
  if(!(m_buffer = new short[buffsize*m_channels])){
   m_error = 11;
   return;
  }
  m_lp = (long *)m_buffer;
  break;

  default:
    m_error = 10; //bad sample encoding
    return;

  }


if(m_mode == SND_INPUT){

stream =  SND_PCM_STREAM_CAPTURE;

if((snd_pcm_open(&m_dev, device, stream, 0)) < 0){
   m_error = 12; // open failed
   return;
 }
m_items = buffsize*m_channels;
m_count = buffsize*m_channels;
} else
{

stream = SND_PCM_STREAM_PLAYBACK;
if((snd_pcm_open(&m_dev, device, stream, 0)) < 0){
   m_error = 12; // open failed
   return;
 }
m_items = buffsize*m_channels;
m_count = 0;
}

snd_pcm_hw_params_alloca(&hwparams);

if(snd_pcm_hw_params_any(m_dev, hwparams) < 0){
  cerr << "cannot configure device\n";
  return;
}


if(snd_pcm_hw_params_set_access(m_dev, hwparams, 
   SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
{
m_error = 18; // couldn't st the access
return;   

	}

if(snd_pcm_hw_params_set_format(m_dev, hwparams, fmt) < 0)
{
m_error = 15; // couldn't set the output format
//return; 
	}

if(snd_pcm_hw_params_set_rate(m_dev, hwparams, (int)m_sr, 0) < 0)
{
m_error = 16; // couldn't st the output sample rate
//return;   
	}


if(
snd_pcm_hw_params_set_channels(m_dev, hwparams, m_channels) < 0)
{
m_error = 14; // couldn't set the output channel number
//return;   
	}


if(snd_pcm_hw_params_set_periods(m_dev, hwparams, buffno, 0) < 0){
  m_error = 13;
  //return;
 }
 
// buffsize is number of buffer frames !
if(snd_pcm_hw_params_set_buffer_size(m_dev, hwparams, 
       buffsize*buffno) < 0)
{
m_error = 17; // couldn't set the buffer size
//return;   
	}


if(snd_pcm_hw_params(m_dev, hwparams) < 0)
{
m_error = 19; // couldn't st the params
return;   
	}
/*
snd_pcm_sw_params_t *swparams;
snd_pcm_sw_params_current(m_dev, swparams);
snd_pcm_sw_params_set_start_threshold(m_dev,swparams,buffsize);
snd_pcm_sw_params_set_avail_min(m_dev,swparams, buffsize);
snd_pcm_sw_params_set_xfer_align(m_dev,swparams,1);
snd_pcm_sw_params(m_dev,swparams);
*/
#endif // if defined ALSA !!!!!!!!!!!!!!!!!!!
m_error  = 0;


} 


SndRTIO::~SndRTIO(){

#ifdef WIN

	if(m_mode == SND_INPUT){
	waveInStop(m_hwi);
	waveInReset(m_hwi);
    for(int n = 0; n < m_buffno; n++){
    // while(!(m_pwhdr[n]->dwFlags & WHDR_DONE)) Sleep(1);
	waveInUnprepareHeader(m_hwi,m_pwhdr[n], sizeof(WAVEHDR));
    GlobalFree(m_hData[n]);
	GlobalFree(m_hwhdr[n]);
    }	
    waveInClose(m_hwi);
	} else {

    for (int n = 0; n < m_buffno; n++){
    // while(!(m_pwhdr[n]->dwFlags & WHDR_DONE)) Sleep(1);
	waveOutUnprepareHeader(m_hwo,m_pwhdr[n], sizeof(WAVEHDR));
    GlobalFree(m_hData[n]);
	GlobalFree(m_hwhdr[n]);
    }
    waveOutReset(m_hwo);
	waveOutClose(m_hwo);
	}	
	delete[] m_hwhdr;
    delete[] m_pwhdr;
	delete[] m_hData;
    delete[] m_buffer;

#endif // WIN

#ifdef SGI
alClosePort(m_port);
 delete[] m_buffer;

#endif // SGI

#ifdef OSS

close(m_dev);
if(m_encoding == BYTESAM)
 delete[] m_cp;
 else delete[] m_sp;
 
#endif // OSS

#ifdef ALSA
if(m_encoding == SND_OUTPUT)
   snd_pcm_drain(m_dev);
snd_pcm_close(m_dev);
 delete[] (char *)m_buffer;
 
#endif // alsa


}


#ifdef WIN

void inline
SndRTIO::Reads(){

if(m_count == m_items){


if(m_firsttime || (m_pwhdr[m_cur]->dwFlags & WHDR_DONE)){
waveInAddBuffer(m_hwi, m_pwhdr[m_cur], sizeof(WAVEHDR));
m_cur++;
if(m_cur == m_buffno)
	m_cur = 0;
}
m_sp = (short *) m_buffer[m_ndx];
m_ndx++;
m_count = 0;
if(m_ndx == m_buffno){
	m_ndx = 0;
	m_firsttime = false;
}
}

if(!m_firsttime)
while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE))
    Sleep(1);
for(int n = 0; n < m_channels; n++)
		m_output[m_vecpos+n] =  (float) m_sp[n+m_count];	 
	

return;

}

void inline
SndRTIO::Readc(){

  if(m_count == m_items){

    if(m_firsttime || (m_pwhdr[m_cur]->dwFlags & WHDR_DONE)){
      waveInAddBuffer(m_hwi, m_pwhdr[m_cur], sizeof(WAVEHDR));
      m_cur++;
      if(m_cur == m_buffno)
	m_cur = 0;
    }
    m_cp = (char *) m_buffer[m_ndx];
    m_ndx++;
    m_count = 0;
    if(m_ndx == m_buffno){
      m_ndx = 0;    
      m_firsttime = false;
    }	
  }

  if(!m_firsttime)
    while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE))
      Sleep(1);
  for(int n = 0; n < m_channels; n++)
    m_output[m_vecpos+n] = (float) m_cp[n+m_count];	 
  return;

}


short 
SndRTIO::Read(){ // remember: m_vecsize is measured in frames!
  if(!m_error && m_mode == SND_INPUT){
    for(m_vecpos = 0; m_vecpos < m_samples; m_vecpos+=m_channels){
      (m_encoding == SHORTSAM ? Reads() : Readc());
      m_count+=m_channels;
    }
    return 1;
  } else return 0;
}


void inline
SndRTIO::Writes(){
	 
  if(m_count == m_items){
    if(!m_firsttime)
      while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE)) Sleep(1);
    waveOutWrite(m_hwo, m_pwhdr[m_ndx], sizeof(WAVEHDR));
    m_count = 0;
    m_ndx++;
    if(m_ndx == m_buffno) {
      m_ndx = 0;
      m_firsttime = false;
    }
    m_sp = (short *)m_buffer[m_ndx];

    if(!m_firsttime)
      while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE)) Sleep(1);
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);
  }

  else{
    if(!m_firsttime)
      while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE)) Sleep(1);
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] =  (short) m_IOobjs[n]->Output(m_vecpos);
    return;
  }
}

void inline
SndRTIO::Writec(){ 
	 
  if(m_count == m_items){
    if(!m_firsttime)
      while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE)) Sleep(1);
    waveOutWrite(m_hwo, m_pwhdr[m_ndx], sizeof(WAVEHDR));
    m_count = 0;
    m_ndx++;
    if(m_ndx == m_buffno) {
      m_ndx = 0;
      m_firsttime = false;
    }
    m_cp = (char *) m_buffer[m_ndx];

    if(!m_firsttime)
      while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE)) Sleep(1);
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] = (char) m_IOobjs[n]->Output(m_vecpos);
  }

  else {
    if(!m_firsttime)
      while(!(m_pwhdr[m_ndx]->dwFlags & WHDR_DONE)) Sleep(1);
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] =  (char) m_IOobjs[n]->Output(m_vecpos);	 
  }

  return;
}

short 
SndRTIO::Write(){

  if(!m_error && m_mode == SND_OUTPUT){
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      (m_encoding == SHORTSAM ? Writes() : Writec());
      m_count+=m_channels;
    }
    return 1;
  }
  else return 0;
}

#endif // WIN

#ifdef SGI 

void inline
SndRTIO::Readf(){

  if(m_count == m_items){
    alReadFrames(m_port, m_fp, m_buffsize);
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = m_fp[n+m_count];
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = m_fp[n+m_count]; 
 	

  
}


void inline
SndRTIO::Readc(){

  if(m_count == m_items){
    alReadFrames(m_port, m_cp, m_buffsize);
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_cp[n+m_count];
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_cp[n+m_count];  
}



void inline
SndRTIO::Reads(){

 
  if(m_count == m_items){
    alReadFrames(m_port, m_sp, m_buffsize);
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_sp[n+m_count];
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_sp[n+m_count]; 
    
    
  
}


void inline
SndRTIO::Readl(){

 
  if(m_count == m_items){
    alReadFrames(m_port, m_lp, m_buffsize);
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_lp[n+m_count];
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_lp[n+m_count]; 
    
   
}

short
SndRTIO::Read(){
  
  if(!m_error && m_mode == SND_INPUT){
    // remember: m_vecsize is measured in frames!
    for(m_vecpos = 0; m_vecpos < m_samples; m_vecpos+=m_channels){
      (m_encoding == FLOATSAM ? Readf() : 
       (m_encoding == SHORTSAM ?  Reads() :
	(m_encoding == LONGSAM ?  Readl() : Readc())));  
      m_count+=m_channels;      
    } 
    return 1;
  }
  else return 0;
}
void inline
SndRTIO::Writef(){

  if(m_count == m_items){
    alWriteFrames(m_port, m_fp, m_buffsize);
    m_count = 0;

    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_fp[n+m_count] = m_IOobjs[n]->Output(m_vecpos);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_fp[n+m_count] = m_IOobjs[n]->Output(m_vecpos);
}


void inline
SndRTIO::Writec(){

  if(m_count == m_items){
    alWriteFrames(m_port, m_cp, m_buffsize);
    m_count = 0;
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] = (char)m_IOobjs[n]->Output(m_vecpos);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] = (char)m_IOobjs[n]->Output(m_vecpos);
}

void inline
SndRTIO::Writes(){
  
  if(m_count == m_items){
    alWriteFrames(m_port, m_sp, m_buffsize);
    m_count = 0;
 
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);
          
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);
                   
}

void inline
SndRTIO::Writel(){

  if(m_count == m_items){
    alWriteFrames(m_port, m_lp, m_buffsize);
    m_count = 0;
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_lp[n+m_count] = (long) m_IOobjs[n]->Output(m_vecpos);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_lp[n+m_count] = (long) m_IOobjs[n]->Output(m_vecpos);
}

short
SndRTIO::Write(){

  if(!m_error && m_mode == SND_OUTPUT){
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      (m_encoding == FLOATSAM ? Writef() : 
       (m_encoding == SHORTSAM ?  Writes() :
        (m_encoding == LONGSAM ?  Writel() : Writec())));
      m_count+=m_channels;
    }
    return 1;
  }
  else return 0;

}

#endif // SGI

#ifdef OSS


void inline
SndRTIO::Readc(){
  
  if(m_count == m_items){
    m_items  = read(m_dev, m_cp, m_buffsize);
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) (m_cp[n+m_count] - 128);
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) (m_cp[n+m_count] - 128); 
    

  
}



void inline
SndRTIO::Reads(){   
  if(m_count == m_items){
    m_items = read(m_dev, m_sp, m_buffsize);
    m_items /= 2;
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_sp[n+m_count];
          
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float)  m_sp[n+m_count]; 
       
}


short
SndRTIO::Read(){
  
  if(!m_error && m_mode == SND_INPUT){
    for(m_vecpos = 0; m_vecpos < m_samples; m_vecpos+=m_channels){
      (m_encoding == BYTESAM ?  Readc() : Reads());
      m_count+=m_channels;   
    }
    return 1; 
  }
  else return 0;	
     
}
void inline
SndRTIO::Writec(){

  if(m_count == m_items){
    write(m_dev, m_cp, m_buffsize);
    m_count = 0;
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] = (char) (m_IOobjs[n]->Output(m_vecpos) + 128);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] = (char)( m_IOobjs[n]->Output(m_vecpos) + 128);
           
}

void inline
SndRTIO::Writes(){

  if(m_count == m_items){
    write(m_dev, m_sp, m_buffsize);
    m_count = 0;
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);

}


short
SndRTIO::Write(){
  
  if(!m_error && m_mode == SND_OUTPUT){
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      (m_encoding == BYTESAM ?  Writec() : Writes() );
      m_count+=m_channels; 
    }
    return 1;
  }
  else return 0;	     
}

#endif // OSS

#ifdef ALSA


void inline
SndRTIO::Readc(){
  
  if(m_count == m_items){
    int err;
    while((err = snd_pcm_readi(m_dev, m_cp, m_items/m_channels))< 0){
      if (err == -EPIPE) {
	err = snd_pcm_prepare(m_dev);
	if(err<0){
	  m_error = 100;
	  return;
	}
	else continue;
      }
      else if (err == -ESTRPIPE) {
	while (snd_pcm_resume(m_dev) == -EAGAIN) sleep(1);
	snd_pcm_prepare(m_dev);
      }
      else if(err == -EAGAIN) continue;
    }
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) (m_cp[n+m_count] - 128);
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) (m_cp[n+m_count] - 128); 
}



void inline
SndRTIO::Reads(){   
  if(m_count == m_items){
    int err;
    while((err = snd_pcm_readi(m_dev, m_sp, m_items/m_channels))< 0){
      if (err == -EPIPE) {
	err= snd_pcm_prepare(m_dev);
	if(err<0){
	  m_error = 100;
	  return;
	}
	else continue;
      }
      else if (err == -ESTRPIPE) {
	while (snd_pcm_resume(m_dev) == -EAGAIN) sleep(1);
	snd_pcm_prepare(m_dev);
      }
      else if(err == -EAGAIN) continue;
    }
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_sp[n+m_count];
          
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float)  m_sp[n+m_count]; 
       
}

void inline
SndRTIO::Readl(){   
  if(m_count == m_items){
    int err;
    while((err = snd_pcm_readi(m_dev, m_lp, m_items/m_channels))< 0){
      if (err == -EPIPE) {
	int err = snd_pcm_prepare(m_dev);
	if(err<0){
	  m_error = 100;
	  return;
	}
	else continue;
      }
      else if (err == -ESTRPIPE) {
	while (snd_pcm_resume(m_dev) == -EAGAIN) sleep(1);
	snd_pcm_prepare(m_dev);
      }
      else if(err == -EAGAIN) continue;
    }
    m_count = 0;         
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float) m_lp[n+m_count];
          
  }
  else
    for(int n = 0; n < m_channels; n++)
      m_output[n+m_vecpos] = (float)  m_lp[n+m_count]; 
       
}


short
SndRTIO::Read(){
  
  if(!m_error && m_mode == SND_INPUT){
    for(m_vecpos = 0; m_vecpos < m_samples; m_vecpos+=m_channels){
      m_encoding == BYTESAM ?  Readc() : 
	(m_encoding == SHORTSAM ?
	 Reads() : Readl() );
      m_count+=m_channels;   
    }
    return 1; 
  }
  else return 0;	
     
}
void inline
SndRTIO::Writec(){
  int err;
  if(m_count == m_items){
    while((err = snd_pcm_writei(m_dev, m_cp, m_items/m_channels)) < 0){
      if (err == -EPIPE) {
	err = snd_pcm_prepare(m_dev);
        if(err<0){
	  m_error = 100;
	  return;     
	}
	else continue; 
      }
      else if (err == -ESTRPIPE) {
	while (snd_pcm_resume(m_dev) == -EAGAIN) usleep(1);
	snd_pcm_prepare(m_dev);
      }
      else if(err == -EAGAIN) continue;
    }	   
    
    m_count = 0;
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] = (char) (m_IOobjs[n]->Output(m_vecpos) + 128);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_cp[n+m_count] = (char)( m_IOobjs[n]->Output(m_vecpos) + 128);
           
}

void inline
SndRTIO::Writes(){
  int err;
  if(m_count == m_items){
    while((err = snd_pcm_writei(m_dev, m_sp, m_items/m_channels)) < 0){
      if (err == -EPIPE) {
	err = snd_pcm_prepare(m_dev);
        if(err<0){
	  m_error = 100;
	  return;     
	}
	else continue; 
      }
      else if (err == -ESTRPIPE) {
	while (snd_pcm_resume(m_dev) == -EAGAIN) usleep(1);
	snd_pcm_prepare(m_dev);
      }
      else if(err == -EAGAIN) continue;
    }

    m_count = 0;
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);

}

void inline
SndRTIO::Writel(){
  int err;
  if(m_count == m_items){
    while((err = snd_pcm_writei(m_dev, m_lp, m_items/m_channels)) < 0){
      if (err == -EPIPE) {
	err = snd_pcm_prepare(m_dev);
        if(err<0){
	  m_error = 100;
	  return;     
	}
	else continue; 
      }
      else if (err == -ESTRPIPE) {
	while (snd_pcm_resume(m_dev) == -EAGAIN) usleep(1);
	snd_pcm_prepare(m_dev);
      }
      else if(err == -EAGAIN) continue;
    }    
    m_count = 0;
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);
  }
  else
    for(int n = 0; n < m_channels; n++)
      if(m_IOobjs[n])
	m_sp[n+m_count] = (short) m_IOobjs[n]->Output(m_vecpos);

}



short
SndRTIO::Write(){
  
  if(!m_error && m_mode == SND_OUTPUT){
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      m_encoding == BYTESAM ?  Writec() : 
	(m_encoding == SHORTSAM ?
	 Writes() : Writel() );
      m_count+=m_channels; 
    }
    return 1;
  }
  else return 0;	     
}


#endif // !!!!!!! ALSA


char* SndRTIO::ErrorMessage(){

  char* message;

  switch(m_error){

#ifdef WIN
  case 14:
    message = "Memory allocation error. \n";
    break;
  case 21:
    message = "Device is already allocated.\n";
    break;
  case 22:
    message = "Bad device ID. \n";
    break;
  case 23:
    message = "No driver. \n";
    break;
  case 24:
    message = "No memory.\n";
    break;
  case 25:
    message = "Bad audio format. \n";
    break;
#endif
#ifdef SGI
  case 11:
    message = "Error allocating DAC buffer memory.\n";
    break;

  case 12:
    message = "Bad encoding format\n";
    break;
  
  case 13:
    message = "alNewConfig() failed.\n";
    break;

  case 14:
    message =  "alSetQueueSize() failed.\n";
    break;

  case 15:
    message = "alSetChannels() failed.\n";
    break;

  case 16:
    message = "alSetSampFmt() failed.\n";
    break;

  case 17:
    message = "alSetWidth() failed.\n";
    break;

  case 18:
    message = "alSetDevice() failed.\n";
    break;

  case 19:
    message = "alSetParams() failed.\n";
    break;

  case 21:
    message = "Error opening audio device.\n";
    break;

#endif
#ifdef OSS
  
  case 10:
    message = "Bad output format.";
    break;  

  case 11:
    message = "Error allocating buffer memory.";
    break;

  case 12:
    message = "device open error.";
    break;

  case 13:
    message =  "DMA buffer size error";
    break;

  case 14:
    message = "could not select number of output channels.";
    break;

  case 15:
    message = "could not set output format";
    break;

  case 16:
    message = "could not set output SR";
    break;

#endif

#ifdef ALSA
  
  case 10:
    message = "Bad output format.";
    break;  

  case 11:
    message = "Error allocating buffer memory.";
    break;

  case 12:
    message = "device open error.";
    break;

  case 13:
    message =  "error setting periods";
    break;

  case 14:
    message = "could not select number of output channels.";
    break;

  case 15:
    message = "could not set output format";
    break;

  case 16:
    message = "could not set output SR";
    break;

  case 17:
    message = "error setting buffersize";
    break;


  case 18:
    message = "error setting access";
    break;

#endif

  default:
    message  = SndIO::ErrorMessage();
    break;

  }
  return message;
}
#ifdef WIN

void
ListDevices(){
  WAVEOUTCAPS outcaps;
  WAVEINCAPS  incaps;
  unsigned int j;
  cout << "Input devices:\ndevice ID: device name\n";
  for(j = 0; j < waveInGetNumDevs(); j++){
    waveInGetDevCaps(j, &incaps, sizeof(incaps)); 
    cout << j << "        : "<< incaps.szPname;
    if(incaps.wChannels == 2)  cout << " stereo\n";
    else {
      if(incaps.wChannels == 1) cout << " mono\n";
      else cout << "\n";
    }
  }

  cout << "Output devices:\ndevice ID: device name\n";
  for(j = 0; j < waveOutGetNumDevs(); j++){
    waveOutGetDevCaps(j, &outcaps, sizeof(outcaps)); 
    cout << j << "        : "<< outcaps.szPname;
    if(outcaps.wChannels == 2)  cout << " stereo\n";
    else {
      if(outcaps.wChannels == 1) cout << " mono\n";
      else cout << "\n";
    }
  }

}

char* InputDeviceName(int dev, char* name){

  WAVEINCAPS  incaps;

  if(dev >= 0 &&  dev < (int)waveInGetNumDevs()){
    waveInGetDevCaps(dev, &incaps, sizeof(incaps));
    return strcpy(name, incaps.szPname);
  } else return 0;

}
char* OutputDeviceName(int dev, char* name){
  WAVEOUTCAPS outcaps;
  if(dev >= 0 &&  dev < (int)waveOutGetNumDevs()){
    waveOutGetDevCaps(dev, &outcaps, sizeof(outcaps));
    return strcpy(name, outcaps.szPname);
  } else return 0;
}


#endif // alsa

#endif // win sgi oss alsa

#endif  // NO_RTIO


