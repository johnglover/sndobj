// SndCoreAudio.cpp:
// Core Audio Realtime IO implementation
//
//
#ifdef MACOSX
#include "SndCoreAudio.h"

OSStatus SndObj_IOProcEntry(AudioDeviceID indev,
const AudioTimeStamp *inN, const AudioBufferList *input,
const AudioTimeStamp *inT, AudioBufferList *output,
const AudioTimeStamp *inOT, void* cdata){

return ((SndCoreAudio *)cdata)->ADIOProc(input,output,(SndCoreAudio *)cdata);

}

SndCoreAudio::SndCoreAudio(int channels,int bufframes, int buffnos, float norm, SndObj** inObjs, 
                 AudioDeviceID dev,  int vecsize, float sr):
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
                                    
if(ibufframes != m_bufframes){            
    
    if(ibufframes == obufframes)
    m_bufframes = obufframes;
    else {
    m_error = 21;
    return;
    }
    
}

   m_format.mSampleRate = m_sr;
   m_format.mFormatID = kAudioFormatLinearPCM;
   m_format.mFormatFlags = kAudioFormatFlagIsFloat;
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
m_inused[i] = m_outused[i] = true;
}

m_incurbuff = m_outcurbuff = m_iocurbuff = 0;
m_incount = m_outcount = 0;

AudioDeviceAddIOProc(m_dev, SndObj_IOProcEntry, this);
AudioDeviceStart(m_dev, SndObj_IOProcEntry);
}
    

SndCoreAudio::~SndCoreAudio(){

AudioDeviceStop(m_dev, SndObj_IOProcEntry);

delete[] m_outbuffs;
delete[] m_inbuffs;
delete[] m_inused;
delete[] m_outused;

}    

OSStatus
SndCoreAudio::ADIOProc(const AudioBufferList *input,
AudioBufferList *output,
SndCoreAudio* cdata){

int chans = cdata->m_channels;
int items = cdata->m_buffitems;
int buff = cdata->m_iocurbuff;
output->mNumberBuffers = 1;
output->mBuffers[0].mDataByteSize = cdata->m_buffsize;
output->mBuffers[0].mNumberChannels = chans;
float *outp = (float *) output->mBuffers[0].mData;
float *inp = (float *) input->mBuffers[0].mData;
float *ibufp = cdata->m_inbuffs[buff];
float *obufp = cdata->m_outbuffs[buff];

for(int i = 0; i < items; i++){
      outp[i]  = obufp[i];
      ibufp[i] = inp[i];
      }
      
cdata->m_outused[buff] = cdata->m_inused[buff] = true;      
buff++;
buff %= cdata->m_buffnos;
cdata->m_iocurbuff = buff;

return 0;
}

short
SndCoreAudio::Write(){
 if(!m_error){
int i;
 for(m_vecpos = 0; m_vecpos < m_vecsize; 
              m_vecpos++){ 
      for(i = 0; i < m_channels; i++){
        m_outbuffs[m_outcurbuff][m_outcount+i] = (m_IOobjs[i] ?
           m_IOobjs[i]->Output(m_vecpos)/m_norm: 0.f);
           } 
      m_outcount+=m_channels;
      if(m_outcount == m_buffitems){           
            m_outused[m_outcurbuff] = false;  
            m_outcurbuff++;
            m_outcurbuff %= m_buffnos;
            m_outcount = 0; 
            while(!m_outused[m_outcurbuff]) usleep(100);
                  }
  } // for
  
  return 1;
 } // if no error
 return 0;
}    


short
SndCoreAudio::Read(){

 if(!m_error){
 while(!m_inused[m_incurbuff]) usleep(100);
 
 for(m_vecpos = 0; m_vecpos < m_vecsize*m_channels; 
              m_vecpos++){
      m_output[m_vecpos] = m_inbuffs[m_incurbuff][m_incount]*m_norm;
      m_incount++;
      if(m_incount == m_buffitems){           
            m_inused[m_incurbuff] = false;  
            m_incurbuff++;
            m_incurbuff %= m_buffnos;
            m_incount = 0;
       }
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

default:
return SndIO::ErrorMessage();
}
return mess;

}
#endif
