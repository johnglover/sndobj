// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information
//
// PVTransp.h: interface for the PVTransp class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _PVTRANSP_H
#define _PVTRANSP_H

enum { NORMAL_TRANSP=0, KEEP_FORMANT};

#include "SpecMult.h"

class PVTransp : public SpecMult  
{
protected:
float m_base;
float m_pitch;
float m_keepform;

public:
	int Set(char* mess, float value);
	int Connect(char* mess, void* input);
	void SetPitch(float pitch, SndObj* inpitch=0);
	void SetMode(int mode){ m_keepform= mode ? true : false;}
	PVTransp();
	PVTransp(SndObj* input, float pitch, int mode=NORMAL_TRANSP,
		  SndObj* inpitch=0, 
		 int vecsize=DEF_FFTSIZE, float sr=DEF_SR);
	~PVTransp();
	short DoProcess();


};

#endif 
