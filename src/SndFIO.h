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

	    // Native <-> Little-endian conversions
	    long lenlong(long lval);
        short lenshort(short sval);
        short natlshort(short sval);
        long natllong(long lval);
		
		// Native <->  Big-endian conversions
		long benlong(long lval);
        short benshort(short sval);
        short natshort(short sval);
        long natlong(long lval);   
		short m_itemsleft;

      public:
	     
		  FILE *GetFile(){return m_safe; }
      short GetMode(){ return m_mode; }
      void SetPos(float pos){ 
          m_spos = pos;
	      if(!fseek(m_safe,(long)(m_spos*m_sr*m_channels*(m_bits/8))+
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

short inline
SndFIO::lenshort(short sval) 
{
    char  benchar[2];
    register char *p = benchar;

    *p++ = 0xFF & sval;
    *p   = 0xFF & (sval >> 8);
    return(*(short *)benchar);
}

long inline
SndFIO::lenlong(long lval)
{
    char  benchar[4];
    register char *p = benchar;

    *p++ = (char) (0xFF & lval);
    *p++ = (char) (0xFF & (lval >> 8));
    *p++ = (char) (0xFF & (lval >> 16));
    *p   = (char) (0xFF & (lval >> 24));
    return(*(long *)benchar);
}

short inline
SndFIO::natlshort(short sval) 
{
    unsigned char benchar[2];
    register short natshort;

    *(short *)benchar = sval;
    natshort = benchar[1];
    natshort <<= 8;
    natshort |= benchar[0];
    return(natshort);
}

long inline
SndFIO::natllong(long lval)     
{
    unsigned char benchar[4];
    register unsigned char *p = benchar + 3;
    register long natlong;

    *(long *)benchar = lval;
    natlong = *p--;
    natlong <<= 8;
    natlong |= *p--;
    natlong <<= 8;
    natlong |= *p--;
    natlong <<= 8;
    natlong |= *p;
    return(natlong);
}

short inline
SndFIO::benshort(short sval)   // coerce a natural short into a bigendian short 
{
    char  benchar[2];
    register char *p = benchar;
    *p++ = 0xFF & (sval >> 8);
    *p   = 0xFF & sval;
    return(*(short *)benchar);
}

long inline 
SndFIO::benlong(long lval)       // coerce a natural long into a bigendian long 
{
    char  benchar[4];
    register char *p = benchar;
    *p++ = (char) (0xFF & (lval >> 24));
    *p++ = (char) (0xFF & (lval >> 16));
    *p++ = (char) (0xFF & (lval >> 8));
    *p   = (char) (0xFF & lval);
    return(*(long *)benchar);
}

short inline 
SndFIO::natshort(short sval)    // coerce a bigendian short into a natural short 
{
    unsigned char benchar[2];
    register short natshort;
    *(short *)benchar = sval;
    natshort = benchar[0];
    natshort <<= 8;
    natshort |= benchar[1];
    return(natshort);
}

long inline 
SndFIO::natlong(long lval)      // coerce a bigendian long into a natural long 
{
    unsigned char benchar[4];
    register unsigned char *p = benchar;
    register long natlong;
    *(long *)benchar = lval;
    natlong = *p++;
    natlong <<= 8;
    natlong |= *p++;
    natlong <<= 8;
    natlong |= *p++;
    natlong <<= 8;
    natlong |= *p;
    return(natlong);
}

#endif













