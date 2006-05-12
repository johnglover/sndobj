// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
// SndWave.cpp: implementaion of the Sndwave                  // 
//                 base class                                 //
//                                                            //
//                                                            //
//************************************************************//
#include "SndWave.h"

SndWave::SndWave(char* name, short mode, short channels, short bits,
		     SndObj** inputlist, float spos, int vecsize, float sr) : 
      SndFIO(name, mode, channels, bits, inputlist, spos, vecsize, sr){

 m_selfdesc = 1;  // yes, this is a self-describing format!
 m_len = 16;
 m_hdrsize = 36;
 m_format = 1;
 if(m_mode != READ){ // OUTPUT
   if(m_mode != APPEND){
   fwrite(&m_header, sizeof(wave_head), 1, m_file);
   m_wchkpos = ftell(m_file);
   fwrite(&m_wdata, sizeof(wave_data), 1, m_file);
   m_datapos = ftell(m_file);
    if(spos > 0) SetPos(spos);     
   } else m_wchkpos = sizeof(wave_head);
   m_header = PutHeader();
   m_wdata.magic3 = *((long*)DATA_ID);
   m_wdata.datasize = 0;
 }	                // OUTPUT
 

 else {            // INPUT
  
   
 if(m_filestat == SFERROR) {    
	  m_dataframes = 0;
	  m_sr = 0.f;
	  m_bits = 0;
	  m_channels = 0;
      m_error = 21;
      m_output =0;
	  cout << ErrorMessage();
      return;

 }
 
 long IDchk;
 fread(&IDchk, 4, 1, m_file);
 if(IDchk != *(long *)RIFF_ID){

	 m_error = 25;
     m_dataframes = 0;
     m_sr = 0.f;
	 m_bits = 0;
	 m_channels = 0;
	 m_output = 0;
	 m_iswave = false;
	 cout << ErrorMessage();
	 return;

 }

 fseek(m_file, 4, SEEK_CUR);
 fread(&IDchk, 4, 1, m_file);

 if(IDchk != *(long *)WAVE_ID){
     m_error = 26;
     m_dataframes = 0;
     m_sr = 0.f;
     m_bits = 0;
     m_channels = 0;
	 m_output = 0;
	 m_iswave = false;
	 cout << ErrorMessage();
	 return;
 }


fseek(m_file ,0, SEEK_SET);
 if(!ReadHeader()){
	 m_error = 27;
	 m_dataframes = 0;
     m_output = 0;
	 m_iswave = false;
	 cout << ErrorMessage();
     return;
 }	 

 m_sr = (float) m_header.rate;
 m_bits = m_header.size;
 m_channels = m_header.nchns;

 if(!(m_IOobjs = new SndObj*[m_channels])){
	m_error = 2;
	cout << ErrorMessage();
	return;
 }

 m_samples = m_vecsize*m_channels;
 delete[] m_output;
 delete[] m_buffer;

 if(!(m_output = new float[m_samples])){
	m_error = 1;
	cout << ErrorMessage();
	return;
 }

 m_buffsize = (m_bits/8)*m_samples;
 if(!(m_buffer = new char[m_buffsize])){
     m_error = 11;
	 cout << ErrorMessage();
	 return;
 }
 
 // these are the pointers used to read the buffer
 m_cp = (char *) m_buffer;
 m_sp = (short *) m_buffer;
 m_lp = (long *) m_buffer;
 m_s24p = (_24Bit *) m_buffer;

 m_dataframes = (m_wdata.datasize*8)/(m_channels*m_bits);
 m_itemsleft = ((m_wdata.datasize)%m_buffsize)/m_sampsize;
 m_spos=spos;          
 m_datapos = ftell(m_file);
 if(spos > 0) SetPos(spos);
 m_iswave = true;
 }   // INPUT
 m_safe = m_file;
}

SndWave::~SndWave(){

	if(m_mode != READ) {  // OUTPUT
    
 if(m_filestat==SFOPEN){

   unsigned long databytes;
#ifndef WIN
  unsigned long endpos, startpos;
  fseek(m_file, 0, SEEK_END);
  endpos = ftell(m_file);
  fseek(m_file, m_wchkpos, SEEK_SET);
  fseek(m_file, sizeof(wave_data), SEEK_CUR);
  startpos = ftell(m_file);
  // find the size of written data and write it
#endif
#ifdef WIN
  fpos_t endpos, startpos;
  fseek(m_file, 0, SEEK_END);
  fgetpos(m_file, &endpos);
  fseek(m_file, m_wchkpos, SEEK_SET);
  fseek(m_file, sizeof(wave_data), SEEK_CUR);
  fgetpos(m_file, &startpos);
#endif
  databytes = (unsigned long) (endpos - startpos);
  m_wdata.datasize = lenlong(databytes);
  m_header = PutHeader(databytes, m_hdrsize, m_len, m_format);

  fseek(m_file, 0, SEEK_SET);
  // rewrite the header
  fwrite(&m_header, sizeof(wave_head), 1, m_file);
  fseek(m_file, m_wchkpos, SEEK_SET);
  fwrite(&m_wdata, sizeof(wave_data), 1, m_file);
 }
	
  }          // OUTPUT
             // nothing to do for INPUT 

}


wave_head 
SndWave::PutHeader(long databytes, int hdrsize, int len,
				   int format)
{
   wave_head form;
   form.magic = *((long *)RIFF_ID);
   form.len0 = lenlong((long)(hdrsize + databytes)); 
   form.magic1 = *((long *)WAVE_ID);
   form.magic2 = *((long *)FMT_ID);
   form.len = lenlong((long)len);  // length of format chunk 
   form.format = lenshort((short)format); // PCM == 1
   form.nchns = lenshort((short)m_channels);
   form.rate = lenlong((long)m_sr); // sampling rate

   // bytes per sec
   form.aver = lenlong((long)(m_sr*(m_bits/8)*m_channels));
   // bytes per frame  
   form.nBlockAlign = lenshort((short)((m_bits/8)*m_channels)); 
   form.size = lenshort((short)m_bits);	// bits per sample 
   return form;

}

short
SndWave::ReadHeader(){
fread(&m_header, sizeof(wave_head), 1, m_file);

   m_header.len0 = natllong(m_header.len0); 
   m_header.len = natllong(m_header.len);   
   m_header.format = natlshort(m_header.format); // PCM == 1
   m_header.nchns = natlshort(m_header.nchns);
   m_header.rate = natllong(m_header.rate); // sampling rate
   m_header.aver = natllong(m_header.aver);// bytes per sec
   m_header.nBlockAlign = natlshort(m_header.nBlockAlign); // bytes per frame  
   m_header.size = natlshort(m_header.size);	// bits per sample 
 
fseek(m_file,m_header.len+20,SEEK_SET);
char chunk_id[4]; 
long chunksize;
fread(&chunk_id,sizeof(char), 4, m_file);
fread(&chunksize,sizeof(long), 1, m_file);
chunksize = natllong(chunksize);

while (*(long*)chunk_id != *(long*)DATA_ID) {

 fseek(m_file,chunksize,SEEK_CUR);
 fread(&chunk_id,sizeof(char), 4, m_file);
 fread(&chunksize,sizeof(long), 1, m_file);
 chunksize = natllong(chunksize);
 }
m_wdata.datasize = chunksize;          

return 1;
}

short 
SndWave::Read(){

if(!m_error && (m_mode == READ) && !feof(m_file)){
 
 int i;
 short items; 
  items = fread(m_buffer, 1, m_buffsize, m_file); 
 items = (items < m_buffsize ? m_itemsleft : items/m_sampsize);

 switch(m_bits) {
  
  case 16:
  for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
	for(i=0; i < m_channels; i++)
    m_output[m_vecpos+i] = (m_vecpos+i < items ?
	                    (float) natlshort(m_sp[m_vecpos+i])
	                            :  0.f);

  break;

  case 8: 
  for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
       for(i=0; i < m_channels; i++)
  m_output[m_vecpos+i] = (m_vecpos+i < items ?
                            (float) m_cp[m_vecpos+i] 
                            :  0.f);
  break;

  case 32:
  for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
   for(i=0; i < m_channels; i++)
	   m_output[m_vecpos+i] = (m_vecpos+i < items ?
	                              (float) natllong(m_lp[m_vecpos+i])
								  : 0.f);
  break;
  
  case 24:
  char tmp[4];
  for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
	  for(i=0; i < m_channels; i++){
       if(m_vecpos+i < items ){
        tmp[1] = m_s24p[m_vecpos+i].s[0];
		tmp[2] = m_s24p[m_vecpos+i].s[1];
		tmp[3] = m_s24p[m_vecpos+i].s[2];
		tmp[0] = 0;
	    m_output[m_vecpos+i] = (float) natllong(*(long *) tmp);
		}else m_output[m_vecpos+i] = 0.f;
	  }
  break;
 }
return items;
}

for(m_vecpos=0; m_vecpos < m_samples; m_vecpos++)
        m_output[m_vecpos] = 0.f;

return 0;
}

short 
SndWave::Write(){

 if(!m_error && (m_mode != READ)){
 int i,n;
  switch(m_bits){
  case 16:
  for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
	for(i = 0; i < m_channels; i++)
			if(m_IOobjs[i])
         m_sp[m_vecpos+i] = lenshort((short)m_IOobjs[i]->Output(n));
  return (short) fwrite(m_sp, m_buffsize, 1, m_file);
  case 8:
  for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
    for(i = 0; i < m_channels; i++)
		 	if(m_IOobjs[i])
         m_cp[m_vecpos+i] = (char) m_IOobjs[i]->Output(n);
  return (short) fwrite(m_cp, m_buffsize, 1, m_file);
  case 32:
  for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
    for(i = 0; i < m_channels; i++)
			if(m_IOobjs[i])
         m_lp[m_vecpos+i] = lenlong((long) m_IOobjs[i]->Output(n));
  return (short) fwrite(m_lp, m_buffsize, 1, m_file);
  case 24:
	  union { char c[4]; long l;} tmp;
    for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
    for(i = 0; i < m_channels; i++)
		if(m_IOobjs[i]){ 
			 tmp.l =  lenlong((long)m_IOobjs[i]->Output(n));
			 	m_s24p[m_vecpos+i].s[0] = tmp.c[1];
				m_s24p[m_vecpos+i].s[1] = tmp.c[2];
				m_s24p[m_vecpos+i].s[2] = tmp.c[3];
				
		}
  return (short) fwrite(m_s24p, m_buffsize, 1, m_file);

  }
 }
 return 0;
}


char*
SndWave::ErrorMessage()
{

  char* message;

  switch(m_error){

  case 21:
  message = "File open error.";
  break;

  case 23:
  message = "Error opening file to update header.";
  break; 
  
  case 25:
  message = "bad RIFF ID.";
  break;
 
  case 26:
  message = "this is not a WAVE file.";
  break;

  case 27:
  message = "could not find data chunk ID.";
  break;

  default:
  message = SndFIO::ErrorMessage();
  break;

  }
 return message;
}


 



