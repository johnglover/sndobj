// SndCoreAudio.cpp:
// Core Audio Realtime IO implementation
//
//
#ifdef MACOSX
#include "SndCoreAudio.h"

OSStatus
SndCoreAudio::ADIOProc(AudioDeviceID indev,
                        const AudioTimeStamp *inN, const AudioBufferList *input,
		        const AudioTimeStamp *inT, AudioBufferList *output,
			const AudioTimeStamp *inOT, void* p){

  SndCoreAudio *cdata = (SndCoreAudio *)p;  
  int chans = cdata->m_channels;
  int buff = cdata->m_iocurbuff;
  float *ibufp = cdata->m_inbuffs[buff];
  float *obufp = cdata->m_outbuffs[buff];

  if(!cdata->m_interleaved) {
    int items = cdata->m_buffitems,i,maxi;
    maxi = input->mBuffers[0].mDataByteSize/sizeof(float);
    output->mNumberBuffers = 1;
    output->mBuffers[0].mDataByteSize = cdata->m_buffsize;
    output->mBuffers[0].mNumberChannels = chans;
    float *outp = (float *) output->mBuffers[0].mData;
    float *inp = (float *) input->mBuffers[0].mData;
    for(i = 0; i < items; i++){
      outp[i]  = obufp[i];
      if(i < maxi) ibufp[i] = inp[i];
      else ibufp[i] = 0.f;
      obufp[i] = 0;
    }
  }
  else {
    int  nibuffs = input->mNumberBuffers, buffs, i, j, cnt;
    int  nobuffs = output->mNumberBuffers;
    int items = cdata->m_bufframes * chans;
    buffs = nibuffs > nobuffs ? nibuffs : nobuffs;
    output->mNumberBuffers = buffs;
    chans = chans > buffs ? buffs : chans;
    float *outp, *inp;
    for (j = 0; j < chans; j++) {
      outp = (float *) output[0].mBuffers[j].mData;
      inp = (float *) input[0].mBuffers[j].mData;
      for (i = j, cnt = 0; i < items; i += chans, cnt++) {
	outp[cnt] = obufp[i];
	obufp[i] = 0.0f;
	ibufp[i] = inp[cnt];
      }
      output->mBuffers[j].mDataByteSize = input[0].mBuffers[j].mDataByteSize;
      output->mBuffers[j].mNumberChannels = 1;
    }
  }
    
  cdata->m_outused[buff] = cdata->m_inused[buff] = true;      
  buff++;
  if(buff == cdata->m_buffnos) buff=0;
  cdata->m_iocurbuff = buff;
  return 0;
}

OSStatus SndObj_IOProcEntry(AudioDeviceID indev,
			    const AudioTimeStamp *inN, const AudioBufferList *input,
			    const AudioTimeStamp *inT, AudioBufferList *output,
			    const AudioTimeStamp *inOT, void* cdata){

  return ((SndCoreAudio *)cdata)->ADIOProc(indev,inN,input,inT,output,inOT,cdata);

}

SndCoreAudio::SndCoreAudio(int channels,int bufframes, int buffnos, float norm, SndObj** inObjs, 
			   UInt32 dev,  int vecsize, float sr):
  SndIO((channels < 2 ?  2 : channels), sizeof(float)*8, inObjs, vecsize, sr) {
                  
  UInt32 psize;
  int i;
  UInt32 obufframes, ibufframes;
  AudioStreamBasicDescription format;
  m_norm = norm ? norm : 1.f;

  if(dev=DEV_DEFAULT){
    psize = sizeof(AudioDeviceID);
    AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice,
			     &psize, &m_dev);
  }
  else m_dev = dev;
  m_sleept = 5;
  m_bufframes = bufframes;
  m_buffsize = bufframes*sizeof(float)*m_channels;
  m_buffitems = bufframes*m_channels;
  m_buffnos = buffnos;

  psize = 4;
  // set the buffer size
  // output
  AudioDeviceSetProperty(m_dev,NULL,0,false,
			 kAudioDevicePropertyBufferFrameSize,
			 psize, &m_bufframes);
  // input            
  AudioDeviceSetProperty(m_dev,NULL,0,true,
			 kAudioDevicePropertyBufferFrameSize,
			 psize, &m_bufframes);
            
  // check that it matches the expected size
  AudioDeviceGetProperty(m_dev,0,true,
			 kAudioDevicePropertyBufferFrameSize,
			 &psize, &ibufframes);
            
  AudioDeviceGetProperty(m_dev,0,false,
			 kAudioDevicePropertyBufferFrameSize,
			 &psize, &obufframes);

  psize = sizeof(double);
  float rsr = m_sr;
  AudioDeviceSetProperty(m_dev, NULL, 0, true,
			 kAudioDevicePropertyNominalSampleRate, psize, &rsr);
  AudioDeviceSetProperty(m_dev, NULL, 0, false,
			 kAudioDevicePropertyNominalSampleRate, psize, &rsr);   
                               
  if(ibufframes != m_bufframes){            
    
    if(ibufframes == obufframes)
      m_bufframes = obufframes;
    else {
      m_error = 21;
      return;
    }
    
  }

  psize = sizeof(AudioStreamBasicDescription);
  
  AudioDeviceGetProperty(m_dev,0,false,      
			 kAudioDevicePropertyStreamFormat,
			 &psize, &format);

  m_format.mSampleRate = m_sr;
  m_format.mFormatID = kAudioFormatLinearPCM;
  m_format.mFormatFlags = kAudioFormatFlagIsFloat | format.mFormatFlags;
  m_format.mBytesPerPacket = sizeof(float)*m_channels;
  m_format.mFramesPerPacket = 1;
  m_format.mBytesPerFrame = format.mBytesPerPacket;
  m_format.mChannelsPerFrame = m_channels;
  m_format.mBitsPerChannel = sizeof(float);

  psize = sizeof(AudioStreamBasicDescription);

  AudioDeviceSetProperty(m_dev,NULL,0,true,      
			 kAudioDevicePropertyStreamFormat,
			 psize, &m_format);

  AudioDeviceSetProperty(m_dev,NULL,0,false,      
			 kAudioDevicePropertyStreamFormat,
			 psize, &m_format);

  AudioDeviceGetProperty(m_dev,0,false,      
			 kAudioDevicePropertyStreamFormat,
			 &psize, &format);

  if(format.mSampleRate != m_sr){
    
    m_error = 22;
    return;         
  }

  if(format.mChannelsPerFrame != m_channels){
    
    m_error = 23;
    return;         
  }

  m_outbuffs = new float*[m_buffnos];
  m_inbuffs = new float*[m_buffnos];
  m_inused = new bool[m_buffnos];
  m_outused = new bool[m_buffnos];

  for(i=0; i < m_buffnos; i++){

    if(!(m_inbuffs[i] = new float[m_bufframes*m_channels])){
      m_error = 24;
      return;
    }
    if(!(m_outbuffs[i] = new float[m_bufframes*m_channels])){
      m_error = 25;
      return;
    }
    memset(m_outbuffs[i], 0, m_bufframes*m_channels*sizeof(float));
    memset(m_inbuffs[i], 0, m_bufframes*m_channels*sizeof(float));
    m_inused[i] = m_outused[i] = false;
  }

  m_incurbuff = m_outcurbuff = m_iocurbuff = 0;
  m_incount = m_outcount = m_buffitems;

  if(AudioDeviceAddIOProc(m_dev, SndObj_IOProcEntry, this) != 0) {
    m_error = 26;
    return;
  }
  AudioDeviceGetProperty(m_dev,0,false,      
			 kAudioDevicePropertyStreamFormat,
			 &psize, &format);

  if (format.mFormatFlags & kAudioFormatFlagIsNonInterleaved == kAudioFormatFlagIsNonInterleaved)
    m_interleaved = true;
  else
    m_interleaved = false; 

    m_stopped = true;
}
    

SndCoreAudio::~SndCoreAudio(){

    AudioDeviceStop(m_dev, SndObj_IOProcEntry);

  delete[] m_outbuffs;
  delete[] m_inbuffs;
  delete[] m_inused;
  delete[] m_outused;

}    


short
SndCoreAudio::Write(){
  if(!m_error){
    int i;
    if(m_stopped){
     AudioDeviceStart(m_dev, SndObj_IOProcEntry);
     m_stopped = false;
    }
    for(m_vecpos = 0; m_vecpos < m_vecsize; 
	m_vecpos++){
      if(m_outcount == m_buffitems){           
	m_outused[m_outcurbuff] = false;  
	m_outcurbuff++;
	if(m_outcurbuff == m_buffnos) m_outcurbuff=0;
	m_outcount = 0; 
	while(!m_outused[m_outcurbuff]) usleep(m_sleept);
      }
      for(i = 0; i < m_channels; i++){
        m_outbuffs[m_outcurbuff][m_outcount+i] = (m_IOobjs[i] ?
						  m_IOobjs[i]->Output(m_vecpos)/m_norm: 0.f);
      } 
      m_outcount+=m_channels;
      
    } // for
  
    return 1;
  } // if no error
  return 0;
}    


short
SndCoreAudio::Read(){

  if(!m_error){
    if(m_stopped){
      if(AudioDeviceStart(m_dev, SndObj_IOProcEntry)==0)
       m_stopped = false;
      else {
	m_error = 26;
        return 0;
      }
    }
    for(m_vecpos = 0; m_vecpos < m_vecsize*m_channels; 
	m_vecpos++){
      if(m_incount == m_buffitems){           
	m_inused[m_incurbuff] = false;  
	m_incurbuff++;
	if(m_incurbuff == m_buffnos) m_incurbuff = 0;
	m_incount = 0;
	while(!m_inused[m_incurbuff]) usleep(m_sleept);
      }
      m_output[m_vecpos] = m_inbuffs[m_incurbuff][m_incount]*m_norm;
      m_inbuffs[m_incurbuff][m_incount] = 0.f;
      m_incount++;
      
    } // for
    return 1;
  } // if no error
  return 0;
}

char* SndCoreAudio::ErrorMessage(){

  char* mess;

  switch(m_error){
  case 21:
    mess="cannot set the requested buffer size \n";
    break;
  case 22:
    mess="error setting the sampling rate \n";
    break;
  case 23:
    mess="error setting the number of channels \n";
    break;
  case 24:
    mess="error allocating memory for input\n";
    break;
  case 25:
    mess="error allocating memory for output\n";
    break;
  case 26:
    mess="can't start device";
    break;

  default:
    return SndIO::ErrorMessage();
  }
  return mess;

}
#endif
