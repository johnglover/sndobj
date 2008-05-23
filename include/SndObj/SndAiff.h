 
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
//  SndAiff.h: interface of the SndAiff abstract base class.  //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _SNDAIFF_H
#define _SNDAIFF_H

#include "SndFIO.h"

const char     FORM_ID[4] = {'F','O','R','M'};
const char     COMM_ID[4] = {'C','O','M','M'};
const char     MARK_ID[4] = {'M','A','R','K'};
const char     INST_ID[4] = {'I','N','S','T'};
const char     SSND_ID[4] = {'S','S','N','D'};
const char     FORM_TYPE[4] = {'A','I','F','F'};


typedef unsigned long ID;            // chunk ID
typedef short MrkrID;       // Marker ID

struct CkHdr{
  ID	ckID;
  long ckSize;
};

struct FormHdr{
  CkHdr	ckHdr;
  ID	formType;
};

struct CommChunk1{
  CkHdr	ckHdr;                   // CommonChunk in 2 parts to avoid 
  short	numChannels;             // this short rounded up to long 
};

struct CommChunk2{
  long	numSampleFrames;         // ... to accomodate this long  
  short	sampleSize;
  char    sampleRate[10];          // 80-bit extended value     
};


struct Loop{
  short   playMode;
  MrkrID  beginLoop;
  MrkrID  endLoop;
};

struct InstrChunk{
  CkHdr	ckHdr;
  char	baseNote;
  char	detune;
  char	lowNote;
  char	highNote;
  char	lowVelocity;
  char	highVelocity;
  short	gain;
  Loop	sustainLoop;
  Loop	releaseLoop;
};



struct SoundDataHdr{
  CkHdr	ckHdr;
  long	offset;
  long	blockSize;
};


struct aiff_head{
  ID	ckID1;              // 'FORM'	
  long ckSize1;          
  ID	formType;           // 'AIFF'
  ID	ckID2;              // 'COMM'
  long ckSize2;
  short nchns;
  long numSampleFrames;           
  short size;
  long  rate;         
};



const int sizFormHdr = sizeof(FormHdr);
const int sizCommChunk1 = sizeof(CkHdr) + sizeof(short);  
const int sizCommChunk2 = sizeof(CommChunk2);
const int sizSoundDataHdr = sizeof(SoundDataHdr);
const int aiffhdrsiz = sizeof(FormHdr)
     + sizeof(CkHdr) + sizeof(short)
     + sizeof(CommChunk2)
     + sizeof(SoundDataHdr);

     const double  onept = 1.021975;     // A440 tuning factor 
     const double  log10d20 = 0.11512925;  // for db to ampfac   

     const unsigned long ULPOW2TO31	= ((unsigned long)0x80000000L);
     const double DPOW2TO31	= ((double)2147483648.0);	/* 2^31 */

     class SndAiff : public SndFIO {

     protected:


       FormHdr	     m_form;
       CommChunk1   m_comm1;   // CommonChunk split    
       CommChunk2   m_comm2;   // to avoid xtra space 
       SoundDataHdr m_ssnd;
       InstrChunk   m_instr;

       aiff_head   m_header;
       short m_framesize;
       short ReadHeader();
       aiff_head PutHeader();
       aiff_head GetHeader(){ return m_header; }

       double ieee_80_to_double(unsigned char *p);
       void   double_to_ieee_80(double val, unsigned char *p);  
       int is_aiff_form(long firstlong){ // test a form           
	 return (firstlong == *(long *)FORM_ID);
       }
       bool m_isaiff;
        
     public:      
       bool IsAiff(){ return m_isaiff; }    
       SndAiff(char* name, short mode, short channels=1, short bits=16,
	       SndObj** inputlist=0, float spos= 0.f, int vecsize = DEF_VECSIZE, float sr = DEF_SR);
       ~SndAiff();
       short Read();
       short Write();
       char* ErrorMessage();
     };

#endif

