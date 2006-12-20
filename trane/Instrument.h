// Instrument.h: interface for the Instrument class.
//
//////////////////////////////////////////////////////////////////////
#ifndef INSTRUMENT_H
#define INSTRUMENT_H


#include "SndObj/AudioDefs.h"

class Instrument  
{
	
	float res[4];
	float fr[4];
	float gloop[4];
	float gstr[4];
 
	bool process_on;

	// SndObjs
        StringFlt *string[4];
	Gain      *strgain[4];
	Gain    *loopgain[4];
	Mixer   *strmix;
	Mixer   *loopmix;
        SndIn   *sound;
	SndLoop *loop[4];
	Allpass *ap[2];
        SndIO   *input;
	SndIO   *output;
	SndObj  *outchannel[2];
	SndThread *thread;

	public:

	void ReSample(int no);
	void LoopOff(int no);
	void LoopOn(int no);
	void StringOff(int no);
	void StringOn(int no);
	void SetPitch(int no, float pitch);
	void SetLoopGain(int no, float gain);
	void SetStrGain(int no, float gain);
	void SetRes(int no, float res);
	void SetFreq(int no, float freq);
	void ProcessOff();
	void ProcessOn();
        float GetFreq(int no) { if(no<4 && no >= 0)return fr[no]; }
	float GetRes(int no){ if(no<4 && no >= 0)return res[no]; }
        float GetLoopGain(int no) { if(no<4 && no >= 0)return gloop[no]; }
	float GetStrGain(int no){ if(no<4 && no >= 0)return gstr[no]; }
	Instrument();
	virtual ~Instrument();

};

#endif 
