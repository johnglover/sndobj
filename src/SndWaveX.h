// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

///////////////////////////////////////////////
// SndWaveX.h: Interface of the SndWaveX
//
//   wave format extensible file IO
//
////////////////////////////////////////////////

#ifndef _SNDWAVEX_H
#define _SNDWAVEX_H

#ifdef WIN
#include <Windows.h>
#endif

#include "SndWave.h"

#define WAVE_FORMAT_EXTENSIBLE (0xFFFE)

#ifndef WIN
#define WAVE_FORMAT_PCM (0x0001)
#endif
#define WAVE_FORMAT_IEEE_FLOAT (0x0003)

#define SPEAKER_FRONT_LEFT 0x1
#define SPEAKER_FRONT_RIGHT 0x2
#define SPEAKER_FRONT_CENTER 0x4
#define SPEAKER_LOW_FREQUENCY 0x8
#define SPEAKER_BACK_LEFT 0x10
#define SPEAKER_BACK_RIGHT 0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER 0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER 0x80
#define SPEAKER_BACK_CENTER 0x100
#define SPEAKER_SIDE_LEFT 0x200
#define SPEAKER_SIDE_RIGHT 0x400
#define SPEAKER_TOP_CENTER 0x800
#define SPEAKER_TOP_FRONT_LEFT 0x1000
#define SPEAKER_TOP_FRONT_CENTER 0x2000
#define SPEAKER_TOP_FRONT_RIGHT 0x4000
#define SPEAKER_TOP_BACK_LEFT 0x8000
#define SPEAKER_TOP_BACK_CENTER 0x10000
#define SPEAKER_TOP_BACK_RIGHT 0x20000
#define SPEAKER_RESERVED 0x80000000

#ifndef WIN
struct GUID 
{ 
    int			Data1; 
    short			Data2; 
    short			Data3; 
    unsigned char	Data4[8]; 
};
#endif

struct wav_ex {	
 short wValidBitsPerSample;
 int dwChannelMask;
 GUID SubFormat;
}; 

struct WAVEFORMATEXTENSIBLE {

wave_head waveformatex;
wav_ex    waveformat_ext;

};

const int PCM = WAVE_FORMAT_PCM;
const int IEEE_FLOAT = WAVE_FORMAT_IEEE_FLOAT;

const GUID KSDATAFORMAT_SUBTYPE_PCM = {
                       0x00000001,
                       0x0000,
					   0x0010,
					   {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
					   };

const GUID KSDATAFORMAT_SUBTYPE_IEEE_FLOAT = {
                       0x00000003,
                       0x0000,
					   0x0010,
					   {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
					   };


class SndWaveX : public SndWave {

protected:

inline bool GUIDcheck(GUID ID);
int m_ChannelMask;
GUID m_SubFormat;
int  m_subformat;
float*  m_fp;
double* m_dp;
bool m_iswavex;

public:

SndWaveX(char* name, short mode = OVERWRITE, 
          short channels=1, int channelmask=0,  short bits=16, short format=PCM,
             SndObj** inputlist=0, float spos= 0.f, 
			 int vecsize = DEF_VECSIZE, float sr = DEF_SR); 
~SndWaveX();

void GetHeader(WAVEFORMATEXTENSIBLE* pheader);
int GetChannelMask(){ return m_ChannelMask;}
short Read();
short Write();
bool IsWaveExtensible(){ return m_iswavex; }

}; 

bool
SndWaveX::GUIDcheck(GUID ID){

if(
(m_SubFormat.Data1 == lenlong(ID.Data1)) &&
(m_SubFormat.Data2 == lenshort(ID.Data2)) &&
(m_SubFormat.Data3 == lenshort(ID.Data3))
){
for(int i=0; i < 8; i++) 
if(m_SubFormat.Data4[i] != ID.Data4[i]) return false;
return true;
}
else return false;
}

#endif
