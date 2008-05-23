 
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
//////////////////////////////////////////////////////
// SndJackIO.cpp: implementation of the SndJackIO class
//           Jack IO client support
//
//

#ifdef JACK


#include <unistd.h>
#include "SndJackIO.h"

int
jprocess_callback(jack_nframes_t n_frames, void *arg){
  return ((SndJackIO *)arg)->JProcess(n_frames);
  
}

void
jshutdown_callback(void *arg){
  ((SndJackIO *)arg)->JShutdown();
}

int
jbuffersize_callback(jack_nframes_t n_frames, void *arg){
  return ((SndJackIO *)arg)->BufferResize(n_frames);
}

SndJackIO::SndJackIO(char* name, int channels, int mode, int buffno,
		     SndObj** inObjs, int vecsize,
		     float sr) : SndIO(channels,16,inObjs,vecsize, sr)
{
  int i, portno, portmax;
  char port_name[10];
  const char **iports;
  const char **oports;  

  m_outused = new bool[buffno];
  m_inused = new bool[buffno];


  m_mode = mode;
  if((m_client = jack_client_new (name)) == 0){
    m_error = 11;
    return;
  }
  m_bufframes = jack_get_buffer_size(m_client);
  m_buffno = buffno;
  m_items = m_bufframes*m_channels;

  jack_set_process_callback(m_client, jprocess_callback, (void *)this);
  jack_on_shutdown(m_client, jshutdown_callback, (void *)this);
  jack_set_buffer_size_callback(m_client,jbuffersize_callback, (void *) this);
  
  if(jack_activate(m_client)){
    m_error = 17;
    return;
  }
  
  if(m_mode == SND_IO || m_mode == SND_INPUT){
    // register & connect inputs
    m_inbuff = new float*[m_buffno];
    for(i=0; i < m_buffno; i++){
      if(!(m_inbuff[i] = new float[m_items])){
	m_error = 12;
        return;
      }
      m_inused[i] = true;
    } 
    if((iports = jack_get_ports(m_client,0,0,
				JackPortIsPhysical | JackPortIsOutput))==0){
      m_error = 13;
    } 
      
    portmax = 24;

    m_inport = new jack_port_t*[m_channels];
    for(i=0; i < m_channels; i++){
      sprintf(port_name, "in%d", i+1);    
      m_inport[i] = 
	jack_port_register (m_client,port_name,JACK_DEFAULT_AUDIO_TYPE,
			    JackPortIsInput,0);
      if(i<=portmax) portno = i;
      else portno = portmax;
	
      if(jack_connect(m_client,iports[portno],
		      jack_port_name(m_inport[i]))){
	m_error = 14;
      }
    }
    free(iports);              
  }

  if(m_mode == SND_IO || m_mode == SND_OUTPUT){
    // register & connect outputs
    m_outbuff = new float*[m_buffno];
    for(i=0; i < m_buffno; i++){
      if(!(m_outbuff[i] = new float[m_items])){
	m_error = 12;
        return;
      }
      m_outused[i] = true;
    } 
    if((oports = jack_get_ports(m_client,0,0,
				JackPortIsPhysical | JackPortIsInput))==0){
      m_error = 15;
    } 
    
     
    portmax = 24;

    m_outport = new jack_port_t*[m_channels];
    for(i=0; i < m_channels; i++){
      sprintf(port_name, "out%d", i+1);    
      m_outport[i] = 
	jack_port_register (m_client,port_name,JACK_DEFAULT_AUDIO_TYPE,
			    JackPortIsOutput,0);
      if(i<=portmax) portno = i;
      else portno = portmax;
      
      if(jack_connect(m_client,
		      jack_port_name(m_outport[i]), oports[portno])){
	m_error = 16;
      }
    }
    free(oports);
  }

  m_outcount = m_incount = 0;
  m_outcurbuff = m_incurbuff = m_curbuff = 0;
    
}

SndJackIO::~SndJackIO(){
  jack_client_close(m_client);
  if(m_outbuff) delete[] m_outbuff;
  if(m_inbuff)  delete[] m_inbuff;
  delete[] m_outused;
  delete[] m_inused;
}

void
SndJackIO::JShutdown(){
  m_error = 18;
}

int
SndJackIO::BufferResize(jack_nframes_t nframes){
   
  m_bufframes = nframes;
  m_items = m_bufframes*m_channels;

  if(m_mode == SND_IO || m_mode == SND_INPUT){
     
    delete[] m_inbuff;
    m_inbuff = new float*[m_buffno];
    for(int i=0; i < m_buffno; i++){
      if(!(m_inbuff[i] = new float[m_items])){
	m_error = 12;
        return 0;
      }
      m_inused[i] = true;
    }   
               
  }

  if(m_mode == SND_IO || m_mode == SND_OUTPUT){
   
    delete[] m_outbuff;
    m_outbuff = new float*[m_buffno];
    m_outused = new bool[m_buffno];
    for(int i=0; i < m_buffno; i++){
      if(!(m_outbuff[i] = new float[m_items])){
	m_error = 12;
        return 0;
      }
      m_outused[i] = true;
    } 
    
  }
  m_outcount = m_incount = 0;
  m_outcurbuff = m_incurbuff = m_curbuff = 0;
   
  return 1;
}

int
SndJackIO::ConnectIn(int channel, char* port){
      
  if( (m_mode != SND_OUTPUT) && (channel < 1) && (channel <= m_channels) &&
      (jack_connect(m_client,port,
		    jack_port_name(m_inport[channel-1])) != 0 ))
    return 0;
  else return 1;

}
 
int
SndJackIO::DisconnectIn(int channel, char* port){
      
  if((m_mode != SND_OUTPUT) && (channel < 1) && (channel <= m_channels) &&
     (jack_disconnect(m_client,port,
		      jack_port_name(m_inport[channel-1])) != 0))
    return 0;
  else return 1;

}

int
SndJackIO::ConnectOut(int channel, char* port){
      
  if((m_mode != SND_INPUT) && (channel < 1) && (channel <= m_channels) &&
     (jack_connect(m_client,jack_port_name(m_outport[channel-1]),
		   port) != 0))
    return 0;
  else return 1;

}

int
SndJackIO::DisconnectOut(int channel, char* port){
      
  if((m_mode != SND_INPUT) && (channel < 1) && (channel <= m_channels) &&    
     (jack_disconnect(m_client,jack_port_name(m_outport[channel-1]),
		      port) != 0))
    return 0;
  else return 1;

}
 

int
SndJackIO::JProcess(jack_nframes_t nframes){

  int i,j,k;
  jack_default_audio_sample_t *sigin;
  jack_default_audio_sample_t *sigout;
  for(i=0; i < m_channels; i++){
    if(m_mode != SND_OUTPUT)
      sigin = (jack_default_audio_sample_t *)
	jack_port_get_buffer(m_inport[i], nframes);
    if(m_mode != SND_INPUT)
      sigout = (jack_default_audio_sample_t *)
	jack_port_get_buffer(m_outport[i], nframes);      

    for(j=i, k=0; j < m_items; j+=m_channels, k++){
      if(m_mode != SND_OUTPUT)
	m_inbuff[m_curbuff][j] = sigin[k];
      if(m_mode != SND_INPUT){
	sigout[k] = m_outbuff[m_curbuff][j];
	m_outbuff[m_curbuff][j] = 0.f;
      }
    }
  }
  m_outused[m_curbuff] =  m_inused[m_curbuff] = true;
  m_curbuff++;
  m_curbuff %= m_buffno;

  return 0;
}

short
SndJackIO::Write(){
  if(!m_error){
    int i;
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){

      for(i=0; i < m_channels; i++)
	m_outbuff[m_outcurbuff][m_outcount+i]
	  = (m_IOobjs[i] ? m_IOobjs[i]->Output(m_vecpos) : 0.f);
      m_outcount+=m_channels;
    
      if(m_outcount == m_items){
	m_outused[m_outcurbuff] = false;
	m_outcurbuff++;
	m_outcurbuff %= m_buffno;
	m_outcount = 0;
	while(!m_outused[m_outcurbuff]) usleep(100);
      }
     
    }
    return 1;
  }
  return 0;
}

short 
SndJackIO::Read(){
  if(!m_error){    
    for(m_vecpos=0; m_vecpos  < m_vecsize*m_channels;m_vecpos++){
      m_output[m_vecpos] = m_inbuff[m_incurbuff][m_incount];
      m_inbuff[m_incurbuff][m_incount] = 0.f;
      m_incount++;
      if(m_incount == m_items){
	m_inused[m_incurbuff] = false;
	m_incurbuff++;
	m_incurbuff %= m_buffno;
	m_incount = 0;
	while(!m_inused[m_incurbuff]) usleep(100);
      }
    }
    return 1;
  }
  return 0;

}
char*
SndJackIO::ErrorMessage(){

  char* message;
   
  switch(m_error){

  case 11:
    message = "Error initialising the Jack Client\n";
    break; 

  case 12:
    message = "Failed to allocate buffer memory\n";
    break;

  case 13:
    message = "Failed to find any physical input ports\n";
    break;

  case 14:
    message = "Failed to connect to physical input port\n";
    break;

  case 15:
    message = "Failed to find any physical output ports\n";
    break;

  case 16:
    message = "Failed to connect to physical output port\n";
    break;

  case 17:
    message = "Failed to activate Jack client\n";
    break;

  case 18:
    message = "Jack server has shut down\n";
    break;

  default:
    return SndIO::ErrorMessage();
    break;
  
  }
  return message;
}

#endif





