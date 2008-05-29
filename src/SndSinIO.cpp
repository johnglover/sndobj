 
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

#include "SndSinIO.h"
#include "SinAnal.h"


SndSinIO::SndSinIO(char* name, int maxtracks, float threshold, int windowtype, short mode, 
		   short channels, int channelmask, short bits, int format,
		   SndObj** inputlist, float framepos, int hopsize, 
		   int fftsize, float sr):
  SndWaveX(name,mode,channels,channelmask, bits, format,
	   inputlist,framepos, maxtracks*3, sr)
{
	
  short cbsize;
  m_len = 64;
  m_format = WAVE_FORMAT_EXTENSIBLE;
  m_hdrsize = 84;
	
  if(mode != READ){ // if output
		
    int mask;
    short sbits;      
		
    m_hopsize = hopsize;
    SetVectorSize(maxtracks*3);
    GUID subfmt;
    cbsize = SHORT_LE((short)46);
    PutHeader(0,m_hdrsize,m_len, m_format);
    sbits = SHORT_LE((short)m_bits);
    mask = LONG_LE((long) (m_ChannelMask = channelmask));
    subfmt.Data1 = LONG_LE(0x443a4b58);
    subfmt.Data2 = SHORT_LE(0x21a2);
    subfmt.Data2 = SHORT_LE(0x324b); 
    subfmt.Data4[0] = 0x00;
    subfmt.Data4[1] =0x00;
    subfmt.Data4[2] = 0x00;
    subfmt.Data4[3] = 0x01;
    subfmt.Data4[4] = 0xAA;
    subfmt.Data4[5] = 0x02;
    subfmt.Data4[6] = 0xBB;
    subfmt.Data4[7] = 0x03;
    m_SubFormat = subfmt;
		
    m_sinheader.dwVersion =  LONG_LE(1);
    m_sinheader.data.wWordFormat =  SHORT_LE((short)(m_bits != 64 ? IEEE_FLOAT_T : IEEE_DOUBLE_T));  
    m_sinheader.data.wWindowType =  SHORT_LE((short)windowtype); 
    m_sinheader.data.dwWindowSize =  LONG_LE((long)fftsize);
    m_sinheader.data.wMaxtracks =SHORT_LE((short) maxtracks);
    m_sinheader.data.wHopsize =  LONG_LE((long)m_hopsize);
    m_sinheader.data.fAnalysisRate = FLOAT32_LE(m_sr/m_hopsize);
    m_sinheader.data.fThreshold = FLOAT32_LE(threshold);
		
    if(mode != APPEND){
      fseek(m_file, sizeof(wave_head), SEEK_SET);
      fwrite(&cbsize, sizeof(short), 1, m_file);
      fwrite(&sbits, sizeof(short), 1, m_file);
      fwrite(&mask, sizeof(int), 1, m_file);
      fwrite(&subfmt, sizeof(GUID), 1, m_file);
      fwrite(&m_sinheader, sizeof(sinusex), 1, m_file);  
      m_wchkpos = ftell(m_file);
      fwrite(&m_wdata, sizeof(wave_data), 1, m_file);
      m_datapos = ftell(m_file);
			
    } else m_wchkpos = sizeof(wave_head) + 22 + sizeof(sinusex) + 2;
		
  } // output
	
  else { // if INPUT
    m_tracks = new int[m_channels];
    m_trkindx = new int*[m_channels];
		
		
    fseek(m_file, sizeof(wave_head)+2+22, SEEK_SET); 	  
    fread(&m_sinheader, sizeof(sinusex),1, m_file);
		
    if(GUIDcheck(KSDATAFORMAT_SUBTYPE_SINUS)){ // check for GUID
      m_sinheader.dwVersion =  LONG_LE(m_sinheader.dwVersion );
      m_sinheader.data.wWordFormat =  SHORT_LE(m_sinheader.data.wWordFormat );
      m_sinheader.data.wHopsize =  SHORT_LE(m_sinheader.data.wHopsize );
      m_sinheader.data.wWindowType =  SHORT_LE(m_sinheader.data.wWindowType );
      m_sinheader.data.wMaxtracks =  SHORT_LE(m_sinheader.data.wMaxtracks);
      m_sinheader.data.dwWindowSize =  LONG_LE(m_sinheader.data.dwWindowSize );
      m_sinheader.data.fThreshold = FLOAT32_LE(m_sinheader.data.fThreshold);
			
    }
    fseek(m_file, m_datapos, SEEK_SET);
    if(framepos > 0) SetTimePos(framepos);    
    m_maxtracks = m_sinheader.data.wMaxtracks; 
    for(int i = 0; i < m_channels; i++) m_trkindx[i] = new int[m_maxtracks];
  }   // INPUT
}


SndSinIO::~SndSinIO(){
  if(m_mode == READ) delete[] m_tracks;
}


void 
SndSinIO::GetHeader(WAVEFORMATSINUSEX* pheader){
	
  SndWaveX::GetHeader((WAVEFORMATEXTENSIBLE*) pheader);   
  pheader->sinusformat_ext.dwVersion = m_sinheader.dwVersion;
  pheader->sinusformat_ext.data.wWordFormat =  m_sinheader.data.wWordFormat;  
  pheader->sinusformat_ext.data.wHopsize =  m_sinheader.data.wHopsize;
  pheader->sinusformat_ext.data.wWindowType =  m_sinheader.data.wWindowType; 
  pheader->sinusformat_ext.data.wMaxtracks  =  m_sinheader.data.wMaxtracks;
  pheader->sinusformat_ext.data.dwWindowSize =  m_sinheader.data.dwWindowSize;
  pheader->sinusformat_ext.data.fAnalysisRate = m_sinheader.data.fAnalysisRate;
  pheader->sinusformat_ext.data.fThreshold = m_sinheader.data.fThreshold;
	
}

void
SndSinIO::SetTimePos(float pos){
	
  int framep = (int)(pos*m_sr/m_hopsize);
  int count;
  if(m_mode == READ){
    fseek(m_file,m_datapos, SEEK_SET);
    while(framep)
      fread(&count, sizeof(int), 1, m_file);
    fseek(m_file, count*(m_bits/8)*3, SEEK_CUR);
    framep--;
  }
	
}

short
SndSinIO::Write(){
  if(!m_error && (m_mode != READ)){
		
    int i, tracks, items = 0;
		
    switch(m_bits){
			
    case 32: 
      for(i = 0; i < m_channels; i++){
	if(m_IOobjs[i]){ 
	  int pos, tpos;
	  tracks = LONG_LE (((SinAnal *)m_IOobjs[i])->GetTracks());
	  items += fwrite(&tracks, sizeof(int), 1, m_file);
	  for(m_vecpos=0, pos=0, tpos=0; m_vecpos < tracks;m_vecpos+=4, tpos+=3, pos++)
	    m_fp[m_vecpos] = FLOAT32_LE((float)(((SinAnal *)m_IOobjs[i])->GetTrackID(pos)));
	  m_fp[m_vecpos+1] =  FLOAT32_LE(m_IOobjs[i]->Output(tpos));
	  m_fp[m_vecpos+2] =  FLOAT32_LE(m_IOobjs[i]->Output(tpos+1));
	  m_fp[m_vecpos+3] =  FLOAT32_LE(m_IOobjs[i]->Output(tpos+2));
	} else 
	  for(m_vecpos=0; m_vecpos < tracks;m_vecpos++)
	    m_fp[m_vecpos] = FLOAT32_LE(0.f);
	items += fwrite(m_fp, sizeof(float), tracks*4, m_file);
      }
      return (short) items; 
				
    case 64:
      for(i = 0; i < m_channels; i++){
	if(m_IOobjs[i]){ 
	  int pos, tpos;
	  tracks = LONG_LE (((SinAnal *)m_IOobjs[i])->GetTracks());
	  items += fwrite(&tracks, sizeof(int), 1, m_file);
	  for(m_vecpos=0, pos=0, tpos=0; m_vecpos < tracks;m_vecpos+=4, tpos+=3, pos++)
	    m_dp[m_vecpos] = DOUBLE_LE((double)(((SinAnal *)m_IOobjs[i])->GetTrackID(pos)));
	  m_dp[m_vecpos+1] = DOUBLE_LE(m_IOobjs[i]->Output(tpos));
	  m_dp[m_vecpos+2] = DOUBLE_LE(m_IOobjs[i]->Output(tpos+1));
	  m_dp[m_vecpos+3] = DOUBLE_LE(m_IOobjs[i]->Output(tpos+2));
	} else 
	  for(m_vecpos=0; m_vecpos < tracks;m_vecpos++)
	    m_dp[m_vecpos] = DOUBLE_LE(0.0);
	items += fwrite(m_dp, sizeof(double), tracks*4, m_file);
      }
      return (short) items;  
    }
  }
	
  return 0;
}

short 
SndSinIO::Read(){
	
  if(!m_error && (m_mode == READ) && !feof(m_file)){
    int i,tracks;
    short items=0;
		
    switch(m_bits) {
			
    case 32:
      for(i=0; i < m_channels; i++){
	int pos, tpos;
	items += fread(&tracks, sizeof(int), 1, m_file);
	m_tracks[i] = LONG_LE((long)tracks);
	items += fread(m_buffer, sizeof(float), tracks*4, m_file);
	for(m_vecpos=0, pos=0, tpos=0; m_vecpos < m_tracks[i]; 
	    m_vecpos+=4, tpos+=3, pos++){
	  m_trkindx[i][pos] = (int) FLOAT32_LE(m_fp[m_vecpos]);
	  m_output[(i+1)*tpos] = FLOAT32_LE(m_fp[m_vecpos+1]);  
	  m_output[(i+1)*tpos+2] = FLOAT32_LE(m_fp[m_vecpos+2]);
	  m_output[(i+1)*tpos+3] = FLOAT32_LE(m_fp[m_vecpos+3]);
	}
					
      }
      return items;
				
    case 64:
      for(i=0; i < m_channels; i++){
	int pos, tpos;
	items += fread(&tracks, sizeof(int), 1, m_file);
	m_tracks[i] = LONG_LE((long)tracks);
	items += fread(m_buffer, sizeof(double), tracks*4, m_file);
	for(m_vecpos=0, pos=0, tpos=0; m_vecpos < m_tracks[i]; 
	    m_vecpos+=4, tpos+=3, pos++){
	  m_trkindx[i][pos] = (int) DOUBLE_LE(m_dp[m_vecpos]);
	  m_output[(i+1)*tpos] = DOUBLE_LE(m_dp[m_vecpos+1]);  
	  m_output[(i+1)*tpos+2] = DOUBLE_LE(m_dp[m_vecpos+2]);
	  m_output[(i+1)*tpos+3] = DOUBLE_LE(m_dp[m_vecpos+3]);
	}
					
      }
      return items;
    }
  }
  return 0;
	
	
}
