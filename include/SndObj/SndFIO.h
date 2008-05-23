 
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
//  SndFIO.h: interface of the SndFIO class.                 //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _SNDFIO_H 
#define _SNDFIO_H

#include <stdio.h>
#include <errno.h>
#include "SndIO.h"



enum {OVERWRITE,APPEND,INSERT,READ };
enum {WAITOPEN=10,SFOPEN,SFERROR};

class SndFIO : public SndIO{
	
 protected:
	
  char* m_name;
  FILE* m_file; 
  FILE* m_safe;
  short m_filestat;
  short m_mode;
  float m_spos;
  long  m_datapos;
  long  m_buffsize;  // size of buffer in bytes 
  char* m_buffer;
  char* m_cp;
  short* m_sp;
  long* m_lp;
  _24Bit* m_s24p;
  short m_selfdesc; // self-describing header present
  long m_dataframes;
  int  m_eof; // end of file indicator
	
  short m_itemsleft;
	
  /* Byte Swapping Functions */
	
  short SwapShort(short inv);
  long SwapLong(long inv);
  float SwapFloat32( float inv );
  double SwapDouble( double inv );
	
 public:
		
  FILE *GetFile(){return m_safe; }
  short GetMode(){ return m_mode; }
  void SetPos(float pos){ 
    m_spos = pos;
    if(!fseek(m_safe,(long)(m_spos*m_sr)*m_channels*(m_bits/8)+
	      m_datapos,
	      SEEK_SET)) m_eof=0; 
  }
  void SetPos(long pos){
    if(!fseek(m_safe, pos  +
	      m_datapos, SEEK_SET)){
      if(m_sr && m_channels && m_bits)
	m_spos = pos/(m_sr*m_channels*(m_bits/8));
      m_eof=0; 
    }
  }
	
  int  Eof() { return (m_eof = feof(m_file));}
  long  GetDataFrames(){ return m_dataframes;} 
  float GetPos(){ return m_spos; }
  short GetStatus(){ return m_filestat; }
	
  SndFIO(char* name, short mode, short channels=1, short bits=16,
	 SndObj** inputlist=0, float spos= 0.f,
	 int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~SndFIO();
  short Read();
  short Write();
  char* ErrorMessage();
	
};


inline short SndFIO::SwapShort (short inv)
{
  union shortconv {
    short	us;
    unsigned char uc[2];
  } *inp, outv;
	
  inp = (union shortconv *)&inv;
	
  outv.uc[0] = inp->uc[1];
  outv.uc[1] = inp->uc[0];
	
  return( outv.us);
}

inline long SndFIO::SwapLong (long inv)
{
  union longconv {
    long	ul;
    unsigned char uc[4];
  } *inp, outv;
	
  inp = (union longconv *)&inv;
	
  outv.uc[0] = inp->uc[3];
  outv.uc[1] = inp->uc[2];
  outv.uc[2] = inp->uc[1];
  outv.uc[3] = inp->uc[0];
	
  return( outv.ul);
	
}

inline float SndFIO::SwapFloat32( float inv )
{
  union floatconv {
    float				uf;
    unsigned char		uc[4];
  } *inp, outv;
    
  inp = (union floatconv *)&inv;
    
  outv.uc[0] = inp->uc[3];
  outv.uc[1] = inp->uc[2];
  outv.uc[2] = inp->uc[1];
  outv.uc[3] = inp->uc[0];
    
  return( outv.uf );
}

inline double SndFIO::SwapDouble( double inv )
{
  union doubleconv {
    double				ud;
    unsigned char		uc[8];
  } *inp, outv;
    
  inp = (union doubleconv *)&inv;
    
  outv.uc[0] = inp->uc[7];
  outv.uc[1] = inp->uc[6];
  outv.uc[2] = inp->uc[5];
  outv.uc[3] = inp->uc[4];
  outv.uc[4] = inp->uc[3];
  outv.uc[5] = inp->uc[2];
  outv.uc[6] = inp->uc[1];
  outv.uc[7] = inp->uc[0];
    
  return( outv.ud );
}

/* Maybe not the best way, but these deal with endian issues
   for any type of io use the macro around what type is expected
   to be written or read. if this is already the processors native form 
   it will do nothing, if not it will swap bytes.

   so, when reading or writing a LE type on a BE machine, SHORT_LE( n ) 
   will swap bytes for reading and writing. when reading or writing a LE
   type on a LE machine, it does nothing
*/

#ifdef WORDS_BIGENDIAN

#define SHORT_LE(x) SwapShort(x)
#define LONG_LE(x) SwapLong(x)
#define FLOAT32_LE(x) SwapFloat32(x)
#define DOUBLE_LE(x) SwapDouble(x)
#define SHORT_BE(x) x
#define LONG_BE(x) x
#define FLOAT32_BE(x) x
#define DOUBLE_BE(x) x


#else

#define SHORT_LE(x) x
#define LONG_LE(x) x
#define FLOAT32_LE(x) x
#define DOUBLE_LE(x) x
#define SHORT_BE(x) SwapShort(x)
#define LONG_BE(x) SwapLong(x)
#define FLOAT32_BE(x) SwapFloat32(x)
#define DOUBLE_BE(x) SwapDouble(x)


#endif

#endif













