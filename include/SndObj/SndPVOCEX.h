 
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

#ifndef _SNDPVOCEX_H
#define _SNDPVOCEX_H

#include "SndWaveX.h"


struct pvoc_data { 
  short wWordFormat;    /* IEEE_FLOAT or IEEE_DOUBLE */ 
  short wAnalFormat;    /*PVOC_AMP_FREQ, PVOC_AMP_PHASE, PVOC_COMPLEX */ 
  short wSourceFormat;    /* WAVE_FORMAT_PCM or WAVE_FORMAT_IEEE_FLOAT*/ 
  short wWindowType;    /* defines the standard analysis window used, or a  custom window */ 
  int nAnalysisBins;  /* number of analysis channels. The FFT window size is derived from this */ 
  int dwWinlen;     /* analysis window length, in samples */ 
  int dwOverlap;     /* window overlap length in samples (decimation)  */ 
  int dwFrameAlign;    /* usually nAnalysisBins * 2 * sizeof(float) */ 
  float fAnalysisRate;            /* sample rate / Overlap */ 
  float fWindowParam;    /* parameter associated with some window types: default 0.0f unless needed */ 
}; 

struct pvocex{ 
  int dwVersion;                                      /* initial version is 1*/ 
  int dwDataSize;                                  /*  sizeof PVOCDATA data block */ 
  pvoc_data data;                                       /* 32 byte block */ 
}; 

enum pvoc_datatype {IEEE_FLOAT_T, IEEE_DOUBLE_T};
enum pvoc_frametype {PVOC_AMP_FREQ=0, PVOC_AMP_PHASE,PVOC_COMPLEX};

enum pvoc_windowtype {DEFAULT=0,
		      HAMMING,
		      HANNING,
		      KAISER,
		      RECTANGULAR,
		      CUSTOM
}; 



struct WAVEFORMATPVOCEX {

  wave_head waveformatex;
  wav_ex     waveformat_ext;
  pvocex    pvocformat_ext;

};

const GUID KSDATAFORMAT_SUBTYPE_PVOC = {
  0x8312b9c2,
  0x2e6e,
  0x11d4,
  { 0xa8, 0x24, 0xde, 0x5b, 0x96, 0xc3, 0xab, 0x21 }
};



class SndPVOCEX : public SndWaveX {

 protected:

  pvocex m_pvheader;
  int m_hopsize;
  bool m_ispvocex;

 public:

  SndPVOCEX(char* name, short mode = OVERWRITE, int analformat=PVOC_AMP_FREQ, int windowtype=HANNING,  
	    short channels=1, int channelmask=0, short bits=32, int format=PCM,
	    SndObj** inputlist=0, float framepos= 0.f, int hopsize = DEF_VECSIZE, 
	    int fftsize = DEF_FFTSIZE, float sr = DEF_SR);

  ~SndPVOCEX();

  int GetFFTSize(){ return (m_pvheader.data.nAnalysisBins-1)*2;}
  int GetHopSize(){ return m_pvheader.data.dwOverlap; }
  int GetWindowType() { return m_pvheader.data.wWindowType; }
  int GetWindowLength() { return m_pvheader.data.dwWinlen; }
  void GetHeader(WAVEFORMATPVOCEX* pheader);

  void SetTimePos(float pos);

  short Read();
  short Write();

  bool IsPvocex(){ return m_ispvocex; }

}; 
#endif
