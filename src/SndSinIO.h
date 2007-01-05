// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SndSinIO_h
#define _SndSinIO_h

#include "SndWaveX.h"
#include "SndPVOCEX.h"

struct sinus_data { 
  short wWordFormat;   
  short wHopsize; 
  short wWindowType;    
  short wMaxtracks;    
  int dwWindowSize;     
  float fThreshold;    
  float fAnalysisRate;       
}; 



struct sinusex {

  int dwVersion;
  sinus_data data;

};

struct WAVEFORMATSINUSEX {

  wave_head waveformatex;
  wav_ex     waveformat_ext;
  sinusex    sinusformat_ext;

};

const GUID KSDATAFORMAT_SUBTYPE_SINUS = {
  0x443a4b58,
  0x21a2,
  0x324b,
  { 0x00, 0x01, 0xAA, 0x02, 0x11, 0x03, 0xBB, 0x04 }
};

class SndSinIO : public SndWaveX {

 protected:

  sinusex m_sinheader;
  int m_hopsize;
  int* m_tracks;
  int** m_trkindx;
  int m_maxtracks;

 public:


  SndSinIO(char* name, int maxtracks, float threshold=0.01f, 
	   int windowtype=HANNING, short mode = OVERWRITE, 
	   short channels=1, int channelmask=0, short bits=32, int format=PCM,
	   SndObj** inputlist=0, float framepos= 0.f, int hopsize = DEF_VECSIZE, 
	   int fftsize = DEF_FFTSIZE, float sr = DEF_SR);
  ~SndSinIO();

  short Write();
  short Read();
  int GetTrackID(int track, int channel) { return m_trkindx[channel][track];}
  int GetTracks(int channel) { return m_tracks[channel]; }
  int GetFFTSize(){ return m_sinheader.data.dwWindowSize;}
  int GetHopSize(){ return m_sinheader.data.wHopsize; }
  int GetWindowType() { return m_sinheader.data.wWindowType; }
  int GetMaxTracks() { return m_sinheader.data.wMaxtracks; }
  void GetHeader(WAVEFORMATSINUSEX* pheader);
  void SetTimePos(float pos);
};

#endif
