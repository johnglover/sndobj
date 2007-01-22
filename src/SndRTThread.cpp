#include "SndRTThread.h"
#include "SndRTIO.h"
#include "SndCoreAudio.h"

SndRTThread::SndRTThread() {
  m_channels = 2;
#ifdef MACOSX
  in = new SndCoreAudio(m_channels);
  out = in;  
#else
  in = new SndRTIO(m_channels, SND_INPUT);
  out = new SndRTIO(m_channels, SND_OUTPUT);
#endif
  sound = new SndIn*[m_channels];
  sound[0] = new SndIn(in, 1);
  sound[1] = new SndIn(in, 2);

  ochannel = new Mixer*[m_channels];
  ochannel[0] = new Mixer;
  ochannel[1] = new Mixer;

  out->SetOutput(1, ochannel[0]);
  out->SetOutput(2, ochannel[1]);

  AddObj(in, SNDIO_IN);
  AddObj(out, SNDIO_OUT);

  SndProcessThread = rtthreadfunc;
}

SndRTThread::SndRTThread(int channels, 
       int buffsize, int periods) :
  SndThread(){

  m_channels = channels;
  m_buffsize = buffsize;
  m_periods = periods;
  Init();
}

void SndRTThread::AddOutput(int channel, SndObj *in){
    if(channel > 0 && channel <= m_channels){
    AddObj(in);
    ochannel[channel-1]->AddObj(in);
    }
  }
void SndRTThread::DeleteOutput(int channel, SndObj *in){
    if(channel > 0 && channel <= m_channels){
    DeleteObj(in);
    ochannel[channel-1]->DeleteObj(in);
    }
  }

SndRTThread::SndRTThread(int n, SndObj** objlist, int channels, 
       int buffsize, int periods) :
  SndThread(n,objlist,0){

  m_channels = channels;
  m_buffsize = buffsize;
  m_periods = periods;
  Init();
}

SndObj *SndRTThread::GetInput(int channel) 
{ 
  if(channel > 0 && channel <= m_channels) 
                   return sound[channel-1];
  else return NULL;
 }   

void
SndRTThread::Direct(int channel, bool yes){
  if(channel > 0 && channel <= m_channels) 
    if(yes) ochannel[channel-1]->AddObj(sound[channel-1]);
    else ochannel[channel-1]->DeleteObj(sound[channel-1]);
}

void SndRTThread::ConnectOutput(int channel, SndObj *in){
 if(channel > 0 && channel <= m_channels)
    ochannel[channel-1]->AddObj(in);
}

void SndRTThread::DisconnectOutput(int channel, SndObj *in){
 if(channel > 0 && channel <= m_channels)
    ochannel[channel-1]->DeleteObj(in);
}


void SndRTThread::Init(){
  int i;
#ifdef MACOSX
  in = new SndCoreAudio(m_channels,m_buffsize,m_periods);
  out = in;  
#else
  in = new SndRTIO(m_channels, SND_INPUT, m_buffsize,m_periods);
  out = new SndRTIO(m_channels, SND_OUTPUT, m_buffsize,m_periods);
#endif
  sound = new SndIn*[m_channels];

  for(i=0; i < m_channels; i++)
         sound[i] = new SndIn(in, i+1);

  ochannel = new Mixer*[m_channels];

  for(i=0; i < m_channels; i++){
         ochannel[i] = new Mixer();
         out->SetOutput(i+1, ochannel[i]);
  }
  AddObj(in, SNDIO_IN);
  AddObj(out, SNDIO_OUT);

  SndProcessThread = rtthreadfunc;
}

SndRTThread::~SndRTThread(){
   delete[] ochannel;
  delete[] sound;
  delete in;
  delete out;
}


void
rtthreadfunc(void* data){
    
  int i, channels, objno, inputno, outputno;
  SndRTThread *sndthread = (SndRTThread *) data;
  SndLink<SndObj>* temp; 
  SndLink<SndIO>* itemp;
  SndLink<SndIO>* otemp; 
  channels =  sndthread->m_channels;
  SndIn **sound = sndthread->sound;
  Mixer **ochannel = sndthread->ochannel;

  while(sndthread->status){
    
    //... processing loop...
   temp = sndthread->last;
   itemp = sndthread->input;
   otemp = sndthread->output;
  
    sndthread->Update();
      
    for(i = 0; i < sndthread->InputNo; i++){
      itemp->obj->Read();
      itemp = itemp->next;
    }
    
    // callback
    if(sndthread->ProcessCallback != NULL)
    sndthread->ProcessCallback(sndthread->callbackdata);          
   
    // sound processing 
    // inputs
    for(i = 0; i < channels; i++)
      sound[i]->DoProcess();

    sndthread->processing = true;
    for(i = 0; i < sndthread->SndObjNo; i++){
      temp = temp->next;
      temp->obj->DoProcess();
    } 
    sndthread->processing = false;
 
    // outputs
    for(i = 0; i < channels; i++)
      ochannel[i]->DoProcess();
      
    // output processing   
    for(i = 0; i < sndthread->OutputNo; i++){ 
      otemp->obj->Write();
      otemp = otemp->next;
		
      }
    
  }
#ifndef USE_WIN32THREADS 
  return;
#else
  _endthread();
#endif
}
