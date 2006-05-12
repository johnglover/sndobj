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

   if(mode != READ){ // if output
	int mask;
	short sbits;
   m_hopsize = hopsize;
   m_vecsize = fftsize;
   GUID subfmt;
   cbsize = lenshort((short)62);
   PutHeader(0,m_hdrsize,m_len, m_format);
   sbits = lenshort((short)m_bits);
   mask = lenlong((long) (m_ChannelMask = channelmask));
   subfmt.Data1 = lenlong((long)0x8312B9C2);
   subfmt.Data2 = lenshort((short)0x2E6E);
   subfmt.Data3 = lenshort((short)0x11d4); 
   subfmt.Data4[0] = 0xA8;
   subfmt.Data4[1] =0x24;
	   subfmt.Data4[2] = 0xDE;
	   subfmt.Data4[3] = 0x5B;
	   subfmt.Data4[4] = 0x96;
	   subfmt.Data4[5] = 0xC3;
	   subfmt.Data4[6] = 0xAB;
	   subfmt.Data4[7] = 0x21;
       m_SubFormat = subfmt;

       m_pvheader.dwVersion =  lenshort((short)1);
       m_pvheader.dwDataSize = lenlong(32L);
	   m_pvheader.data.wWordFormat =  lenshort((short)(m_bits != 64 ? IEEE_FLOAT_T : IEEE_DOUBLE_T));  
       m_pvheader.data.wAnalFormat =  lenshort((short)analformat);
       m_pvheader.data.wSourceFormat =  lenshort((short)m_subformat);
 m_pvheader.data.wWindowType =  lenshort((short)windowtype); 
 m_pvheader.data.nAnalysisBins =  lenlong((long)(fftsize/2) + 1);
 m_pvheader.data.dwWinlen =  lenlong((long)fftsize);
 m_pvheader.data.dwOverlap =  lenlong((long)m_hopsize);
 m_pvheader.data.dwFrameAlign =  lenlong((long)((fftsize/2)+1)*2*m_bits);  
 m_pvheader.data.fAnalysisRate = m_sr/m_hopsize;
 m_pvheader.data.fWindowParam = 0.f;
                 
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
       m_pvheader.dwVersion =  natlshort((short)m_pvheader.dwVersion );
       m_pvheader.dwDataSize = natllong(  m_pvheader.dwDataSize );
	   m_pvheader.data.wWordFormat =  natlshort((short)m_pvheader.data.wWordFormat );  
       m_pvheader.data.wAnalFormat =  natlshort((short)m_pvheader.data.wAnalFormat);
       m_pvheader.data.wSourceFormat =  natlshort((short)m_pvheader.data.wSourceFormat);
       m_pvheader.data.wWindowType =  natlshort((short) m_pvheader.data.wWindowType );
	   
       m_pvheader.data.nAnalysisBins  =  natllong((long) m_pvheader.data.nAnalysisBins );
       m_pvheader.data.dwWinlen =  natllong((long) m_pvheader.data.dwWinlen );
       m_pvheader.data.dwOverlap =  natllong((long) m_pvheader.data.dwOverlap );
       m_pvheader.data.dwFrameAlign =  natllong((long)m_pvheader.data.dwFrameAlign );  
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
   m_fp[n++] = m_IOobjs[i]->Output(0);
   m_fp[n++] = 0.f;
   for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
				 m_fp[n] = m_IOobjs[i]->Output(m_vecpos);

   m_fp[n++] = m_IOobjs[i]->Output(1);
   m_fp[n++] = m_sr/2;
	  }
   else 
	for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++, n++)
	 m_fp[n] = 0.f;
  }
  return (short) fwrite(m_fp, m_buffsize, 1, m_file);
  
  case 64:
	for(i = 0, n= 0; i < m_channels; i++){	
	  if(m_IOobjs[i]){ 
   m_dp[n++] = m_IOobjs[i]->Output(0);
   m_dp[n++] = 0.f;
   for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
				 m_dp[n] = m_IOobjs[i]->Output(m_vecpos);

   m_dp[n++] = m_IOobjs[i]->Output(1);
   m_dp[n++] = m_sr/2;
	  }
   else 
	for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++, n++)
	 m_dp[n] = 0.f;
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
	
    m_output[n] = m_fp[n]; n++;
    m_output[n] = m_fp[(m_vecsize-2)+n]; n++;
	for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
                           m_output[n] = m_fp[n];	
      }
  break;

  case 64:
  for(n=0, i=0; i < m_channels; i++){
    m_output[n] = (float)m_dp[n]; n++;
    m_output[n] = (float)m_dp[(m_vecsize-2)+n]; n++;
  for(m_vecpos=2; m_vecpos < m_vecsize-2; m_vecpos++, n++)
  	            m_output[n] = (float)m_dp[n];  	  
      }
  break;
 }
 return items;
}
else for(m_vecpos=0; m_vecpos < m_vecsize; m_vecpos++)
     m_output[m_vecpos] = 0.f;  
return 0;


}
