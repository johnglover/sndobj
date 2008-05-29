 
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

#include "SndRead.h"
#include "SndWave.h"
#include "SndAiff.h"

SndRead::SndRead(){
	
  m_pitch = 1.f;
  m_pos = 0.;
  m_scale = 1.f;
  m_ioinput = 0;
  m_outobj = 0;
  m_channels = 0;
  m_count = 0;
  AddMsg("pitch", 21);
  AddMsg("scale", 22);
}


SndRead::SndRead(char* name, float pitch, 
		 float scale, int vecsize, float sr)
  : SndObj(0, vecsize, sr)
{
	
  m_pitch= fabs(pitch);
  m_count = 0;
  m_pos = 0.;
  m_scale = scale;
  int i;
  int type = 0;
  int size = strlen(name);
	
  if((name[size-3] == 'w') &&
     (name[size-2] == 'a') &&
     (name[size-1] == 'v')) type = 1;
	
  else if((name[size-3] == 'a') &&
	  (name[size-2] == 'i') &&
	  (name[size-1] == 'f')) type = 2;
	
  switch (type){
		
  case 1:
    m_ioinput = new SndWave(name, READ, 1, 16,0,0,vecsize*2);
    if(!((SndWave *)m_ioinput)->IsWave()) m_error = 21;
    break;
			
  case 2:
    m_ioinput = new SndAiff(name, READ, 1, 16,0,0,vecsize*2);
    if(!((SndAiff *)m_ioinput)->IsAiff()) m_error = 21;
    break;
			
  default:
    m_ioinput = new SndFIO(name, READ, 1, 16,0,0,vecsize*2);
    break;
			
  }
  if(m_sr != m_ioinput->GetSr()) m_error = 22;
	
  m_channels = m_ioinput->GetChannels();
	
  m_outobj = new SndObj*[m_channels];
  for(i=0;i< m_channels; i++)
    m_outobj[i] = new SndObj(0,vecsize,sr);
	
  AddMsg("pitch", 21);
  AddMsg("scale", 22);
	
}

SndRead::~SndRead(){
	
  delete m_ioinput;
  delete[] m_outobj;
	
}


int
SndRead::Set(char* mess, float value){
	
  switch (FindMsg(mess)){
		
  case 21:
    m_pitch = value; 
    return 1;
			
  case 22:
    m_scale = value; 
    return 1;
			
  default:
    return SndObj::Set(mess,value);
			
  }
}


void
SndRead::SetInput(char* name){
	
  if(m_ioinput) {
    delete m_ioinput;
    delete[] m_outobj;
  }
	
  int type = 0;
  int i;
  for(i = 0; name[i] == '.' || name[i] == '\0';
      i++);
	
  if((name[i] != '\0') &&
     (name[i+1] == 'w') &&
     (name[i+2] == 'a') &&
     (name[i+3] == 'v')) type = 1;
	
  else if((name[i] != '\0') &&
	  (name[i+1] == 'a') &&
	  (name[i+2] == 'i') &&
	  (name[i+3] == 'f')) type = 2;
	
  switch (type){
		
  case 1:
    m_ioinput = new SndWave(name, READ, 1, 16,0,0,m_vecsize*2);
    if(!((SndWave *)m_ioinput)->IsWave()) m_error = 21;
    break;
			
  case 2:
    m_ioinput = new SndAiff(name, READ, 1, 16,0,0,m_vecsize*2);
    if(!((SndAiff *)m_ioinput)->IsAiff()) m_error = 21;
    break;
			
  default:
    m_ioinput = new SndFIO(name, READ, 1, 16,0,0,m_vecsize*2);
    break;
			
  }
  if(m_sr != m_ioinput->GetSr()) m_error = 22;
  m_channels = m_ioinput->GetChannels();
	
  m_outobj = new SndObj*[m_channels];
  for(i=0;i< m_channels; i++)
    m_outobj[i] = new SndObj(0,m_vecsize, m_sr);
	
}

short
SndRead::DoProcess(){
	
  if(!m_error && m_ioinput){
    if(!m_ioinput->Eof()) {
			
      float out, outsum= 0.f;
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
				
	if(m_pos >= m_count/m_channels){  
	  m_pos -= (m_count/m_channels);
	  m_count = m_ioinput->Read();	
	}
				
	if(m_count && m_enable){
	  for(int i=0; i < m_channels; i++){
						
	    out = m_scale*m_ioinput->Output(Ftoi(m_pos), i+1);
	    outsum += out;
	    *(m_outobj[i]) << out;
						
	  }
	  m_output[m_vecpos] = outsum/m_channels;
	  m_pos += m_pitch;
	  outsum = 0.f;
					
	} else {
	  for(int i=0; i < m_channels; i++)	
	    *(m_outobj[i]) << 0.f;
	  m_output[m_vecpos] = 0;
	}
				
      }
    } else {
      for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++) {
	for(int i=0; i < m_channels; i++)	
	  *(m_outobj[i]) << 0.f;
	m_output[m_vecpos] = 0;
      }
			
			
    }
    return 1;
  }
  return 0;
}
