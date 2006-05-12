// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//////////////////////////////////////////////////////
// IFFT.h: interface of the IFFT class: 
//        short-time inverse fast fourier transform
//        using the FFTW library (v. 2.1.3) 
//        Victor Lazzarini, 2003 
/////////////////////////////////////////////////////////

#ifndef _IFFT_H
#define _IFFT_H
#include <rfftw.h>
#include "Table.h"
#include "SndObj.h"

class IFFT : public SndObj {

protected:

// m_vecsize is hopsize
// and fftsize is always a whole-number
// multiple of it.

int m_fftsize;
int m_hopsize;  // hopsize
int m_halfsize; // 1/2 fftsize
int *m_counter; // counter 
rfftw_plan m_plan; // FFTW initialisation
float m_fund;

int m_frames;  // frame overlaps
float** m_sigframe; // signal frames
float* m_ffttmp; // tmp vector for fft transform
int m_cur;    // index into current frame 

Table*  m_table; // window

// reset memory and initialisation
void ReInit();

private:
// ifft wrapper method
void inline ifft(float* signal);



public:

IFFT::IFFT();
IFFT::IFFT(Table* window, SndObj* input, int fftsize = DEF_FFTSIZE, 
		   int hopsize=DEF_VECSIZE, float sr=DEF_SR);
IFFT::~IFFT();


	int GetFFTSize() { return m_fftsize; }
	int GetHopSize() { return m_hopsize; }
	void SetWindow(Table* window){ m_table = window;}
	int Connect(char* mess, void* input);
	int Set(char* mess, float value);
	virtual void SetFFTSize(int fftsize);
	virtual void SetHopSize(int hopsize);

short DoProcess();


};

#endif
