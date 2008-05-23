 
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

#include "SndPVOCEX.h"


SndPVOCEX::SndPVOCEX(char* name, short mode, int analformat, int windowtype,  
		     short channels, int channelmask, short bits, int format,
		     SndObj** inputlist, float framepos, int hopsize, 
		     int fftsize, float sr):
  SndWaveX(name,mode,channels,channelmask, bits, format,
	   inputlist,framepos,fftsize+2, sr)
{
	
  short cbsize;
  m_len = 80;
  m_format = WAVE_FORMAT_EXTENSIBLE;
  m_hdrsize = 100;
	
  //	printf("bits %i mode %i fftsize %i\n", bits, mode, fftsize);
	
  if(mode != READ){ // if output
    int mask;
    short sbits;
    m_hopsize = hopsize;
    SetVectorSize (fftsize);
    GUID subfmt;
    cbsize = SHORT_LE((short)62);
    PutHeader(0,m_hdrsize,m_len, m_format);
    sbits = SHORT_LE((short)bits);
    m_bits = bits; //
    mask = LONG_LE((long) (m_ChannelMask = channelmask));
    subfmt.Data1 = LONG_LE(0x8312B9C2);
    subfmt.Data2 = SHORT_LE(0x2E6E);
    subfmt.Data3 = SHORT_LE(0x11d4); 
    subfmt.Data4[0] = 0xA8;
    subfmt.Data4[1] =0x24;
    subfmt.Data4[2] = 0xDE;
    subfmt.Data4[3] = 0x5B;
    subfmt.Data4[4] = 0x96;
    subfmt.Data4[5] = 0xC3;
    subfmt.Data4[6] = 0xAB;
    subfmt.Data4[7] = 0x21;
    m_SubFormat = subfmt;
		
    m_pvheader.dwVersion =  LONG_LE(1);
    m_pvheader.dwDataSize = LONG_LE(32L);
    m_pvheader.data.wWordFormat =  SHORT_LE((short)(m_bits != 64 ? IEEE_FLOAT_T : IEEE_DOUBLE_T));  
    m_pvheader.data.wAnalFormat =  SHORT_LE((short)analformat);
    m_pvheader.data.wSourceFormat =  SHORT_LE((short)m_subformat);
    m_pvheader.data.wWindowType =  SHORT_LE((short)windowtype); 
    m_pvheader.data.nAnalysisBins =  LONG_LE((long)(fftsize/2) + 1);
    m_pvheader.data.dwWinlen =  LONG_LE((long)fftsize);
    m_pvheader.data.dwOverlap =  LONG_LE((long)m_hopsize);
    m_pvheader.data.dwFrameAlign =  LONG_LE((long)((fftsize/2)+1)*2*m_bits); //m_bits
    m_pvheader.data.fAnalysisRate = FLOAT32_LE(m_sr/m_hopsize);
    m_pvheader.data.fWindowParam = FLOAT32_LE(0.f);
		
    if(mode != APPEND){
      fseek(m_file, sizeof(wave_head), SEEK_SET);
      fwrite(&cbsize, sizeof(short), 1, m_file);
      fwrite(&sbits, sizeof(short), 1, m_file);
      fwrite(&mask, sizeof(int), 1, m_file);
      fwrite(&subfmt, sizeof(GUID), 1, m_file);
      fwrite(&m_pvheader, sizeof(pvocex), 1, m_file);  
      m_wchkpos = ftell(m_file);
      fwrite(&m_wdata, sizeof(wave_data), 1, m_file);
      m_datapos = ftell(m_file);
      if(framepos > 0) SetTimePos(framepos);   
    } else m_wchkpos = sizeof(wave_head) + 22 + sizeof(pvocex) + 2;
		
  } // output
	
  else { // if INPUT
		
    fseek(m_file, sizeof(wave_head)+2+22, SEEK_SET); 	  
    fread(&m_pvheader, sizeof(pvocex),1, m_file);
		
    if(GUIDcheck(KSDATAFORMAT_SUBTYPE_PVOC)){ // check for GUID
      m_pvheader.dwVersion =  LONG_LE(m_pvheader.dwVersion );
      m_pvheader.dwDataSize = LONG_LE(  m_pvheader.dwDataSize );
      m_pvheader.data.wWordFormat =  SHORT_LE(m_pvheader.data.wWordFormat );  
      m_pvheader.data.wAnalFormat =  SHORT_LE(m_pvheader.data.wAnalFormat);
      m_pvheader.data.wSourceFormat =  SHORT_LE(m_pvheader.data.wSourceFormat);
      m_pvheader.data.wWindowType =  SHORT_LE(m_pvheader.data.wWindowType );
			
      m_pvheader.data.nAnalysisBins  =  LONG_LE(m_pvheader.data.nAnalysisBins );
      m_pvheader.data.dwWinlen =  LONG_LE(m_pvheader.data.dwWinlen );
      m_pvheader.data.dwOverlap =  LONG_LE(m_pvheader.data.dwOverlap );
      m_pvheader.data.dwFrameAlign =  LONG_LE(m_pvheader.data.dwFrameAlign );
      m_pvheader.data.fAnalysisRate = FLOAT32_LE(m_pvheader.data.fAnalysisRate);
      m_pvheader.data.fWindowParam = FLOAT32_LE(m_pvheader.data.fWindowParam);
      m_ispvocex = true;
    } else {
      m_ispvocex = false;
      m_error = 61;
    }
    fseek(m_file, 108, SEEK_SET);
    if(framepos > 0) SetTimePos(framepos);       
  }   // INPUT
	
	
	
	
}


SndPVOCEX::~SndPVOCEX(){
}


void 
SndPVOCEX::GetHeader(WAVEFORMATPVOCEX* pheader){
	
  SndWaveX::GetHeader((WAVEFORMATEXTENSIBLE*) pheader);   
  pheader->pvocformat_ext.dwVersion = m_pvheader.dwVersion;
  pheader->pvocformat_ext.dwDataSize = m_pvheader.dwDataSize;
  pheader->pvocformat_ext.data.wWordFormat =  m_pvheader.data.wWordFormat;  
  pheader->pvocformat_ext.data.wAnalFormat =  m_pvheader.data.wAnalFormat;
  pheader->pvocformat_ext.data.wSourceFormat = m_pvheader.data.wSourceFormat;
  pheader->pvocformat_ext.data.wWindowType =  m_pvheader.data.wWindowType; 
  pheader->pvocformat_ext.data.nAnalysisBins  =  m_pvheader.data.nAnalysisBins;
  pheader->pvocformat_ext.data.dwWinlen =  m_pvheader.data.dwWinlen;
  pheader->pvocformat_ext.data.dwOverlap =  m_pvheader.data.dwOverlap;
  pheader->pvocformat_ext.data.dwFrameAlign =  m_pvheader.data.dwFrameAlign;  
  pheader->pvocformat_ext.data.fAnalysisRate = m_pvheader.data.fAnalysisRate;
  pheader->pvocformat_ext.data.fWindowParam = m_pvheader.data.fWindowParam;
	
}

void
SndPVOCEX::SetTimePos(float pos){
	
  int framep = (int)(pos*m_sr/m_hopsize);
  framep *= (GetFFTSize()+2)*m_channels*(m_bits/8);
  if(!fseek(m_file,m_datapos+framep, SEEK_SET)) m_eof = 0;
  else m_eof=1;
}


short
SndPVOCEX::Write(){
  if(!m_error && (m_mode != READ)){
    int i,n;
			
    switch(m_bits){
			
    case 32: 
				
      for(i = 0, n= 0; i < m_channels; i++){	
	if(m_IOobjs[i]){ 
	  m_fp[n++] = FLOAT32_LE(m_IOobjs[i]->Output(0));
	  m_fp[n++] = FLOAT32_LE(0.f);
	  for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
	    m_fp[n] = FLOAT32_LE(m_IOobjs[i]->Output(m_vecpos));
						
	  m_fp[n++] = FLOAT32_LE(m_IOobjs[i]->Output(1));
	  m_fp[n++] = FLOAT32_LE(m_sr/2);
	}
	else 
	  for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++, n++)
	    m_fp[n] = FLOAT32_LE(0.f);
      }
      return (short) fwrite(m_fp, m_buffsize, 1, m_file);
				
    case 64:
      for(i = 0, n= 0; i < m_channels; i++){	
	if(m_IOobjs[i]){ 
	  m_dp[n++] = DOUBLE_LE(m_IOobjs[i]->Output(0));
	  m_dp[n++] = DOUBLE_LE(0.0);
	  for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
	    m_dp[n] = DOUBLE_LE(m_IOobjs[i]->Output(m_vecpos));
						
	  m_dp[n++] = DOUBLE_LE(m_IOobjs[i]->Output(1));
	  m_dp[n++] = DOUBLE_LE(m_sr/2);
	}
	else 
	  for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++, n++)
	    m_dp[n] = DOUBLE_LE(0.0);
      }
      return (short) fwrite(m_dp, m_buffsize, 1, m_file);
    }
  }
  return 0;
}


short 
SndPVOCEX::Read(){
	
  if(!m_error && (m_mode == READ) && !feof(m_file)){
    int i,n;
    short items;
    items = fread(m_buffer, 1, m_buffsize, m_file); 
    items /= m_sampsize;
		
    switch(m_bits) {
			
    case 32:
				
      for(n=0, i=0; i < m_channels; i++){
					
	m_output[n] = FLOAT32_LE(m_fp[n]); n++;
	m_output[n] = FLOAT32_LE(m_fp[(m_vecsize-2)+n]); n++;
	for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
	  m_output[n] = FLOAT32_LE(m_fp[n]);	
      }
      break;
				
    case 64:
      for(n=0, i=0; i < m_channels; i++){
	m_output[n] = FLOAT32_LE((float)m_dp[n]); n++;
	m_output[n] = FLOAT32_LE((float)m_dp[(m_vecsize-2)+n]); n++;
	for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
	  m_output[n] = FLOAT32_LE((float)m_dp[n]);  	  
      }
      break;
    }
    return items;
  }
  else for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++)
    m_output[m_vecpos] = 0.f;  
  return 0;
	
	
}
