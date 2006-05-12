// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef __VstPlug_H
#define __VstPlug_H

#include "audioeffectx.h"
#include  <SndObj/AudioDefs.h>

class VstPlug : public AudioEffectX
{
public:
	VstPlug(audioMasterCallback audioMaster);
	~VstPlug();

	void process(float **inputs, float **outputs, long sampleFrames);
	void processReplacing(float **inputs, float **outputs, long sampleFrames);
	void setProgramName(char *name);
	void getProgramName(char *name);
	void setParameter(long index, float value);
	float getParameter(long index);
	void getParameterLabel(long index, char *label);
	void getParameterDisplay(long index, char *text);
	void getParameterName(long index, char *text);
	void setBlockSize(long blockSize);
	void setSampleRate(float sr);

protected:
	int vecsize;
	float fGain; 
	float Freq;
	float Fdb;
	char programName[32];

	SndObj* channel1;
	SndObj* procobj1;

};

#endif
