// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  SndIO.h: interface of the SndIO base class.               //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//
#ifndef _SNDIO_H
#define _SNDIO_H
#include <math.h>
#include "SndObj.h"

enum{FLOATSAM=0, BYTESAM, SHORTSAM_LE};
const int SHORTSAM_BE = -2;
const int S24LE = 3;
const int S24BE = -3;
const int LONGSAM = 4;

enum{SND_INPUT, SND_OUTPUT, SND_IO};


#ifdef WIN
const int SHORTSAM = SHORTSAM_LE;
#endif

#ifdef OSS
const int SHORTSAM = SHORTSAM_LE;
#endif

#ifdef ALSA
const int SHORTSAM = SHORTSAM_LE;
const int LONGSAM_LE = LONGSAM;
const int LONGSAM_BE = 5;
const int TWENTY_FOUR = 6;
const int TWENTYFOUR_LE = TWENTY_FOUR;
const int TWENTYFOUR_BE = 7;
#endif


#ifdef SGI
const int SHORTSAM = SHORTSAM_BE;
#endif

#if defined(MACOSX) && defined(WORDS_BIGENDIAN)
const int SHORTSAM = SHORTSAM_BE;
#endif

#if defined(MACOSX) && !defined(WORDS_BIGENDIAN)
const int SHORTSAM = SHORTSAM_LE;
#endif



struct _24Bit {
	char s[3];
};


 class SndIO {

      protected:
 
      SndObj**  m_IOobjs; 
      float* m_output;
      float m_sr;
      short m_channels;
      short m_bits;
	  int m_vecsize;
	  int m_vecpos;
      int m_error;
	  int m_samples;

	  short VerifySR(SndObj *InObj){      
       if(InObj->GetSr() != m_sr) return 0;
       else return 1;                           
                            }

      public:
	      short m_sampsize;
         
        float GetSr(){ return m_sr; }
		int   GetVectorSize() { return m_vecsize; }
        short GetChannels() { return m_channels; }
        short GetSize() { return m_bits; }
		float Output(int pos){ return m_output[pos]; }
        float Output(int pos, int channel){
            return m_output[(pos*m_channels)+(channel-1)];
                                }
        short SetOutput(short channel, SndObj* input){
		   if(channel <= m_channels){                     
					   m_IOobjs[channel-1] = input;
					   return 1;
				} else return 0;
                                }
         
		SndIO(short channels=1, short bits=16,SndObj** inputlist=0, 
              int vecsize = DEF_VECSIZE, float sr = DEF_SR);
		virtual ~SndIO();
		virtual short Read();
		virtual short Write();
        virtual char* ErrorMessage();
		int Error() { return m_error; }

                          };



#endif

