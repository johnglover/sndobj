// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

///////////////////////////////////////////
// SndFIO.cpp
//
//
///////////////////////////////////////////

#include "SndFIO.h"


SndFIO::SndFIO(char* name, short mode, short channels, short bits,
		     SndObj** inputlist, float spos, int vecsize, float sr) :
 SndIO(channels, bits,inputlist,vecsize,sr){

 m_name = name;
 m_mode = mode;
 m_spos = spos; 
 m_datapos = 0;
 m_filestat = WAITOPEN;
 m_selfdesc = 0;
 m_eof=0;

 char* s_temp;

 
 switch (mode){  // open modes

   case INSERT:
   s_temp="r+b";
   break;

   case OVERWRITE:  
   s_temp="wb";
   break;

   case APPEND:
   s_temp="ab";
   m_datapos = 0;
   break;

   case READ:
   s_temp= "rb";
   if(!m_selfdesc) m_bits = bits;
   else m_bits = 0;
   break;

   default:
   m_error = 8;
   cout << ErrorMessage();
   return;

   } 

 // open file
 if (m_file=fopen(name,s_temp)) m_filestat=SFOPEN;
  else{
    m_filestat=SFERROR;
    m_error=12;
    cout << ErrorMessage();
    return;
     } 



 if(m_bits>0){
 m_buffsize = (m_bits/8)*m_samples;
 if(!(m_buffer = new char[m_buffsize])){
     m_error = 11;
	 cout << ErrorMessage();
	 return;
 }
 
 // these are the pointers used to read/write to the buffer
 m_cp = (char *) m_buffer;
 m_sp = (short *) m_buffer;
 m_lp = (long *) m_buffer;
 m_s24p = (_24Bit*) m_buffer; 
 }
 else {
 m_buffsize = 0;
 m_buffer = 0;
 m_cp = 0;
 m_sp = 0;
 m_lp = 0;
 }
 if(m_bits != 16 && m_bits != 8 && m_bits != 32
	 && m_bits != 24){
	 m_error = 13;
     cout << ErrorMessage();
   }
 if(spos > 0) SetPos(spos);
 m_safe = m_file;
 }

SndFIO::~SndFIO(){
	 delete[] m_buffer;
     if(m_filestat==SFOPEN) fclose(m_file);
}


short 
SndFIO::Read(){

if(!m_error && (m_mode == READ) && !feof(m_file)){
 
 int i;
 short items;
 items = fread(m_buffer, 1, m_buffsize, m_file);
 items /= m_sampsize;

 switch(m_bits) {
  
  case 16:
  for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
	for(i=0; i < m_channels; i++)
    m_output[m_vecpos+i] = (m_vecpos+i < items ?
	                     (float) m_sp[m_vecpos+i]
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
	                              (float) m_lp[m_vecpos+i]
								  : 0.f);
  break;
  case 24:
  for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
   for(i=0; i < m_channels; i++)
	   m_output[m_vecpos+i] = (m_vecpos+i < items ?
	                              (float) 
								  (*(long *)m_s24p[m_vecpos+i].s)
								  : 0.f);
 }
 return items;
}

for(m_vecpos=0; m_vecpos < m_samples; m_vecpos++)
        m_output[m_vecpos] = 0.f;

return 0;
}


short 
SndFIO::Write(){

 if(!m_error && (m_mode != READ)){
 int i,n;

  switch(m_bits){
  case 16:
  for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
	for(i = 0; i < m_channels; i++)
		 	if(m_IOobjs[i])
         m_sp[m_vecpos+i] = (short) m_IOobjs[i]->Output(n);
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
         m_lp[m_vecpos+i] = (long) m_IOobjs[i]->Output(n);
  return (short) fwrite(m_lp, m_buffsize, 1, m_file);
  
  case 24:
   for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
    for(i = 0; i < m_channels; i++)
		if(m_IOobjs[i]){ 
		 (*(long *)m_s24p[m_vecpos+i].s) = (long) m_IOobjs[i]->Output(n);
		}
  return (short) fwrite(m_s24p, m_buffsize, 1, m_file);
  }
 }
 return 0;
}

char*
SndFIO::ErrorMessage(){

  char* message;

  switch(m_error){

  case 11:
  message = "Failed to allocate buffer memory\n";
  break;
  
  case 12:
  message = "File open error\n";
  break;
  
  case 13:
  message = "Unsupported precision.";
  break;

  default:
  message =  SndIO:: ErrorMessage();
  break;
  
  }

 return message;
}

