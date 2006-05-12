// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information
//
// PVBlur.h: interface for the PVBlur class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _PVBlur_H
#define _PVBlur_H


#include "SpecMult.h"

class PVBlur : public SpecMult  
{
protected:
float **m_frame;
float m_time;
int m_framenos;
int m_hopsize;
int m_cur;

public:
	int Set(char* mess, float value);
	void SetBlurTime(float time);
	void SetHopsize(int hopsize){ m_hopsize = hopsize;
	SetBlurTime(m_time);
	}
	PVBlur();
	PVBlur(SndObj* input, float blurtime, int hopsize=DEF_VECSIZE, 
		int vecsize=DEF_FFTSIZE, float sr=DEF_SR);
	~PVBlur();
	short DoProcess();


};

#endif 
