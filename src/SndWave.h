 
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
//  SndWave.h: interface of the Sndwave          base class.  //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _SNDWAVE_H 
#define _SNDWAVE_H

#include "SndFIO.h"

const char     RIFF_ID[4] = {'R','I','F','F'};
const char     WAVE_ID[4] = {'W','A','V','E'};
const char     FMT_ID[4]  = {'f','m','t',' '};
const char     DATA_ID[4] = {'d','a','t','a'};

struct wave_head{
  long	magic;			// 'RIFF' 
  long	len0;			// Chunk size = len + 8 + 16 + 12 
  long	magic1;			// 'WAVE' 
  long	magic2;			// 'fmt ' 
  long	len;			// length of header (16)
  short format;// 1 is PCM (the only format supported) 
  short	nchns;			// Number of channels 
  long	rate;			// sampling frequency 
  long	aver;			// Average bytes/sec !! 
  short	nBlockAlign;		// (rate*nch +7)/8 
  short	size;			// size of each sample (8,16,32) 
};

struct wave_data {
  long	magic3;			// 'data' 
  long	datasize;		// data chunk size 
};



class SndWave : public SndFIO {

 protected:
  bool m_iswave;
        
  int   m_wchkpos;
  int m_len;
  int m_format;
  int m_hdrsize;
  wave_head m_header;
  wave_data m_wdata;
  short ReadHeader();
  wave_head PutHeader(long databytes=0, int hdrsize=36, int len=16,
		      int format=1); 

 public:	

  wave_head GetHeader(){ return m_header;}
  SndWave(char* name, short mode = OVERWRITE, short channels=1,  short bits=16,
	  SndObj** inputlist=0, float spos= 0.f, int vecsize = DEF_VECSIZE, float sr = DEF_SR); 
  ~SndWave();
  short Read();
  short Write();
  bool IsWave(){ return m_iswave;}
  char* ErrorMessage();

};

#endif









