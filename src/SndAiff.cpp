 
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

//************************************************************//
// SndAiff.cpp: implementation of the SndAiff                 // 
//               class                                        //
//                                                            //
//                                                            //
//************************************************************//

#include "SndAiff.h"
#include <stdlib.h>


SndAiff::SndAiff(char* name, short mode, short channels, short bits,
		 SndObj** inputlist, float spos, int vecsize, float sr):
  SndFIO(name, mode, channels, bits, inputlist, spos, vecsize, sr)
{
	
  m_selfdesc = 1; // yes, this is a self-describing  format !!!!
  m_isaiff = false;
  if(m_mode != READ){     // OUTPUT
    m_framesize = (short)((m_bits/8)*m_channels);
    m_header = PutHeader();
		
    if(m_mode != APPEND){
      fwrite((char *)&m_form, sizFormHdr, 1, m_file); 
      fwrite((char *)&m_comm1, sizCommChunk1, 1, m_file);
      fwrite((char *)&m_comm2, sizCommChunk2, 1, m_file);
      fwrite((char *)&m_ssnd, sizSoundDataHdr, 1, m_file);
      m_datapos = ftell(m_file); 
      if(spos > 0) SetPos(spos);     
    }
  } // OUTPUT
	
  else {  // INPUT
		
    if(m_filestat==SFERROR) {
      m_dataframes = 0;
      m_sr = 0.f;
      m_bits = 0;
      m_channels = 0;
      m_error = 21;
      return;
    }
		
    long IDchk;
    fread(&IDchk, 4, 1, m_file);
    if(!is_aiff_form(IDchk)){
      m_filestat = SFERROR;
      m_sr = 0.f;
      m_bits = 0;
      m_channels = 0;
      m_dataframes = 0;
      m_error = 25;
      return;
    }
		
    fseek(m_file, 4, SEEK_CUR);
    fread(&IDchk, 4, 1, m_file);
    if(IDchk != *(long *) FORM_TYPE){
      m_filestat = SFERROR;
      m_sr = 0.f;
      m_bits = 0;
      m_channels = 0;
      m_dataframes =0;
      m_error = 26;
      m_output = 0;
      return;
    }
		
    fseek(m_file, 0, SEEK_SET);
    if(!ReadHeader()){
      m_dataframes = 0;
      m_error = 27;
      m_output = 0; 
      return; 
			
    }
    m_bits = m_header.size;
    m_channels = m_header.nchns;
    m_dataframes = m_header.numSampleFrames;
    int datasize = m_dataframes*m_channels*m_sampsize;
    m_isaiff = true;
    m_itemsleft = (datasize%m_buffsize)/m_sampsize;
    m_spos=spos;          
    m_datapos = ftell(m_file);
    if(spos > 0) SetPos(spos); 
		
    delete[] m_output;
    delete[] m_buffer;
		
    m_samples = m_vecsize*m_channels;
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
		
  }  // INPUT
	
}

SndAiff::~SndAiff(){
	
  if(m_mode != READ){  // OUPUT
    if(m_filestat==SFOPEN){
      unsigned long datasize;
#ifndef WIN
      unsigned long endpos, startpos;
      fseek(m_file, 0, SEEK_END);
      endpos = ftell(m_file);
      fseek(m_file, sizFormHdr, SEEK_SET);
      fseek(m_file, sizCommChunk1, SEEK_CUR);
      fseek(m_file, sizCommChunk2, SEEK_CUR);
      fseek(m_file,sizSoundDataHdr, SEEK_CUR);
      startpos = ftell(m_file);
#endif
#ifdef WIN
      fpos_t endpos, startpos;
      fseek(m_file, 0, SEEK_END);
      fgetpos(m_file, &endpos);
      fseek(m_file, sizFormHdr, SEEK_SET);
      fseek(m_file, sizCommChunk1, SEEK_CUR);
      fseek(m_file, sizCommChunk2, SEEK_CUR);
      fseek(m_file,sizSoundDataHdr, SEEK_CUR);
      fgetpos(m_file, &startpos);
#endif
      datasize = (unsigned long) (endpos - startpos);
			
      double_to_ieee_80((double)m_sr,(unsigned char*)m_comm2.sampleRate);  
      m_header.ckSize1 =
	m_form.ckHdr.ckSize = LONG_BE(datasize + sizeof(aiff_head) - sizeof(CkHdr));
      m_header.numSampleFrames =
	m_comm2.numSampleFrames = LONG_BE(datasize / m_framesize);
      m_ssnd.ckHdr.ckSize = LONG_BE(datasize + (2*sizeof(long)));
			
      if(m_mode == APPEND){
	fclose(m_file);
	if(!(m_file = fopen(m_name, "r+b")))
	  m_error = 23;
	cout << ErrorMessage();
      }   
      fseek(m_file,0, SEEK_SET);
      fwrite((char *)&m_form, sizFormHdr, 1, m_file); 
      fwrite((char *)&m_comm1, sizCommChunk1, 1, m_file);
      fwrite((char *)&m_comm2, sizCommChunk2, 1, m_file);
      fwrite((char *)&m_ssnd, sizSoundDataHdr, 1, m_file);
    }
  }  //OUTPUT
	
}

aiff_head 
SndAiff::PutHeader()
{
  aiff_head form;
  form.ckID1 = m_form.ckHdr.ckID = *(long *) FORM_ID;
  form.ckSize1 = 
    m_form.ckHdr.ckSize = 0;  		// leave for destructor 
  form.formType = 
    m_form.formType = *(long *) FORM_TYPE;
  form.ckID2 = 
    m_comm1.ckHdr.ckID = *(long *) COMM_ID;
  form.ckSize2 = 
    m_comm1.ckHdr.ckSize = LONG_BE((long)sizeof(short) + sizCommChunk2);
  form.nchns = 
    m_comm1.numChannels = SHORT_BE((short)m_channels);
  form.numSampleFrames =
    m_comm2.numSampleFrames = 0;	// leave for destructor 
  form.size =
    m_comm2.sampleSize = SHORT_BE((short)(m_bits));
  // insert 80-bit srate 
  double_to_ieee_80((double)m_sr,(unsigned char*)m_comm2.sampleRate);  
  form.rate = LONG_BE((long)m_sr);
  m_ssnd.ckHdr.ckID = *(long *) SSND_ID;
  m_ssnd.ckHdr.ckSize = 0;  		// leave for destructor
  m_ssnd.offset = 0;
  m_ssnd.blockSize = 0;
  return form;
}

short 

SndAiff::ReadHeader(){
	
  fread(&m_form, sizeof(FormHdr), 1, m_file);
  m_header.ckID1 = m_form.ckHdr.ckID;
  m_header.ckSize1 =
    m_form.ckHdr.ckSize = LONG_BE(m_form.ckHdr.ckSize);
  m_header.formType = m_form.formType;
	
  char temp[4];
  short find=0;
  do
    { 
      fread(&temp[find],1,1,m_file);
      if (temp[find]==COMM_ID[find]) find++;
      else 
	find=0;
      if(feof(m_file)) return 0;
    }
  while (find<4);
	
  m_header.ckID2 =
    m_comm1.ckHdr.ckID = LONG_BE(*(long *) temp);
  fread(&m_comm1.ckHdr.ckSize, 4, 1, m_file);
  fread(&m_comm1.numChannels, 2, 1, m_file);
  fread(&m_comm2, sizeof(CommChunk2), 1, m_file);
  m_header.ckSize2 =
    m_comm1.ckHdr.ckSize = LONG_BE(m_comm1.ckHdr.ckSize);
  m_header.nchns =
    m_comm1.numChannels = SHORT_BE(m_comm1.numChannels);
  m_header.numSampleFrames =
    m_comm2.numSampleFrames = LONG_BE(m_comm2.numSampleFrames);	     
  m_header.size =
    m_comm2.sampleSize = SHORT_BE(m_comm2.sampleSize);	
  m_sr = (float)ieee_80_to_double((unsigned char*)m_comm2.sampleRate);	
	
  find = 0;
  do
    { 
      fread(&temp[find],1,1,m_file);
      if (temp[find]==SSND_ID[find]) find++;
      else find=0;
      if(feof(m_file)) return 0;
    }
	
  while (find<4);
  m_ssnd.ckHdr.ckID = *(long *)temp;
  fread(&m_ssnd.ckHdr.ckSize, 4, 1, m_file);
  fread(&m_ssnd.offset, 4, 1, m_file);
  fread(&m_ssnd.blockSize, 4, 1, m_file);
  m_ssnd.ckHdr.ckSize = LONG_BE(m_ssnd.ckHdr.ckSize);  	
  m_ssnd.offset = LONG_BE(m_ssnd.offset);
  m_ssnd.blockSize = LONG_BE(m_ssnd.blockSize);
	
  return 1;
}



short 
SndAiff::Read(){
	
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
				  (float) SHORT_BE(m_sp[m_vecpos+i])
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
				  (float) LONG_BE(m_lp[m_vecpos+i])
				  : 0.f);
      break;
    case 24:
      char tmp[4];
      for(m_vecpos=0; m_vecpos < m_samples; m_vecpos+=m_channels)
	for(i=0; i < m_channels; i++){
	  if(m_vecpos+i < items ){
	    tmp[0] = m_s24p[m_vecpos+i].s[0];
	    tmp[1] = m_s24p[m_vecpos+i].s[1];
	    tmp[2] = m_s24p[m_vecpos+i].s[2];
	    tmp[3] = 0;
	    m_output[m_vecpos+i] = (float) LONG_BE(*(long *) tmp);
	  }else m_output[m_vecpos+i] = 0.f;
	}
    }
    return items;
  }
		
  for(m_vecpos=0; m_vecpos < m_samples; m_vecpos++)
    m_output[m_vecpos] = 0.f;
		
  return 0;
}

short 
SndAiff::Write(){
	
  if(!m_error && (m_mode != READ)){
    int i,n;
		
    switch(m_bits){
    case 16:
      for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
	for(i = 0; i < m_channels; i++)
	  if(m_IOobjs[i])
	    m_sp[m_vecpos+i] = SHORT_BE((short)m_IOobjs[i]->Output(n));
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
	    m_lp[m_vecpos+i] = LONG_BE((long) m_IOobjs[i]->Output(n));
      return (short) fwrite(m_lp, m_buffsize, 1, m_file);
    case 24:
      for(m_vecpos=n=0; m_vecpos < m_samples; m_vecpos+=m_channels, n++)
	for(i = 0; i < m_channels; i++)
	  if(m_IOobjs[i]){ 
	    *(long *)m_s24p[m_vecpos+i].s =  LONG_BE((long)m_IOobjs[i]->Output(n));
	  }
      return (short) fwrite(m_s24p, m_buffsize, 1, m_file);
    }
  }
  return 0;
}

// IEEE conversions taken from Csound sources (thanks to its developers)

static double myUlongToDouble(unsigned long ul)
{
  double val;
  if(ul & ULPOW2TO31)
    val = DPOW2TO31 + (ul & (~ULPOW2TO31));
  else
    val = ul;
  return val;
	
}

static unsigned long myDoubleToUlong(double val)
{
  unsigned long ul;	
  // cannot cast negative numbers into unsigned longs 
  if(val < 0)	
    { 
      //err_printf("IEEE80:DoubleToUlong: val < 0\n"); 
      exit(-1);
    }
  // in ultrix 4.1's cc, double -> unsigned long loses the top bit, 
  // so we do the conversion only on the bottom 31 bits and set the 
  // last one by hand, if val is truly that big 
  // should maybe test for val > (double)(unsigned long)0xFFFFFFFF ? 
  if(val < DPOW2TO31)
    ul = (unsigned long)val;
  else
    ul = ULPOW2TO31 | (unsigned long)(val-DPOW2TO31);
  return ul;
}

// Convert IEEE 80 bit floating point to double.
// Should be portable to all C compilers.
double  
SndAiff::ieee_80_to_double(unsigned char *p)
{
  char sign;
  short exp = 0;
  unsigned long mant1 = 0;
  unsigned long mant0 = 0;
	
  double val;
  exp = *p++;
  exp <<= 8;
  exp |= *p++;
  sign = (exp & 0x8000) ? 1 : 0;
  exp &= 0x7FFF;
	
  mant1 = *p++;
  mant1 <<= 8;
  mant1 |= *p++;
  mant1 <<= 8;
  mant1 |= *p++;
  mant1 <<= 8;
  mant1 |= *p++;
	
  mant0 = *p++;
  mant0 <<= 8;
  mant0 |= *p++;
  mant0 <<= 8;
  mant0 |= *p++;
  mant0 <<= 8;
  mant0 |= *p++;
	
  // special test for all bits zero meaning zero 
  //   - else pow(2,-16383) bombs 
  if(mant1 == 0 && mant0 == 0 && exp == 0 && sign == 0)
    return 0.0;
  else{
    val = myUlongToDouble(mant0) * pow(2.0,-63.0);
    val += myUlongToDouble(mant1) * pow(2.0,-31.0);
    val *= pow(2.0,((double) exp) - 16383.0);
    return sign ? -val : val;
  }
}

// Convert double to IEEE 80 bit floating point
void 
SndAiff::double_to_ieee_80(double val, unsigned char *p)
{
	
  char sign = 0;
  short exp = 0;
  unsigned long mant1 = 0;
  unsigned long mant0 = 0;
	
  if(val < 0.0)	{  sign = 1;  val = -val; }
  if(val != 0.0)	// val identically zero -> all elements zero 
    {
      exp = (short)(log(val)/log(2.0) + 16383.0);
      val *= pow(2.0, 31.0+16383.0-(double)exp);
      mant1 = myDoubleToUlong(val);
      val -= myUlongToDouble(mant1);
      val *= pow(2.0, 32.0);
      mant0 = myDoubleToUlong(val);
    }
  *p++ = ((sign<<7)|(exp>>8));
  *p++ = (unsigned char)(0xFF & exp);
  *p++ = (unsigned char)(0xFF & (mant1>>24));
  *p++ = (unsigned char)(0xFF & (mant1>>16));
  *p++ = (unsigned char)(0xFF & (mant1>> 8));
  *p++ = (unsigned char)(0xFF & (mant1));
  *p++ = (unsigned char)(0xFF & (mant0>>24));
  *p++ = (unsigned char)(0xFF & (mant0>>16));
  *p++ = (unsigned char)(0xFF & (mant0>> 8));
  *p++ = (unsigned char)(0xFF & (mant0));
}
char*
SndAiff::ErrorMessage()
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
    message = "bad AIF ID.";
    break;
			
  case 26:
    message = "this is not an AIFF file.";
    break;
			
  case 27:
    message = "could not read header.";
    break;
			
  default:
    message = SndFIO::ErrorMessage();
    break;
			
  }
  return message;
}









