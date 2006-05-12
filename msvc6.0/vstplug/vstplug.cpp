// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "vstplug.h" 

//-----------------------------------------------------------------------------
VstPlug::VstPlug(audioMasterCallback audioMaster)
	: AudioEffectX(audioMaster, 1, 3)	// 1 program, 3 parameters only
{
	fGain = 1.;				// default to 0 dB
	Freq = 0.127f;
	Fdb = 0.99f;
	setNumInputs(2);		// stereo in
	setNumOutputs(2);		// stereo out
	setUniqueID('SObj');	// identify
	canMono();				// makes sense to feed both inputs with the same signal
	canProcessReplacing();	// supports both accumulating and replacing output
	strcpy(programName, "Default");	// default program name
	channel1 = new SndObj(0,getBlockSize(),getSampleRate());
	procobj1 = new StringFlt(127.f, Fdb, channel1, 0, getBlockSize(),getSampleRate());

}

//-----------------------------------------------------------------------------------------
VstPlug::~VstPlug()
{
	// nothing to do here
	delete channel1;
	delete procobj1;

}

// We have to create a specialised version of setBlockSize()
// to reset the SndObjs prior to processing in case of
// change of block size
// This is very important if the blocksize is different from
// the default of 1024, because in this STUPID arrangement
// the constructor does not initialise the blocksize to anything
// but the default size!
// This is not clearly stated in the documentation, tsc,tsc..
// Why haven't they thought of a Initialise() method ?!

void
VstPlug::setBlockSize(long blockSize){
    
	delete procobj1;
	delete channel1;	
     channel1 = new SndObj(0,blockSize,getSampleRate());
	 procobj1 = new StringFlt(Freq*1000, Fdb, channel1, 0, blockSize,getSampleRate());	
	 AudioEffect::setBlockSize(blockSize);
}

// good idea to do it to the Sampling Rate as well 

void
VstPlug::setSampleRate(float sr){
    
	//delete channel1;
     channel1->SetSr(sr);
	 procobj1->SetSr(sr);
	 AudioEffect::setSampleRate(sr);
}


//-----------------------------------------------------------------------------------------
void VstPlug::setProgramName(char *name)
{
	strcpy(programName, name);
}

//-----------------------------------------------------------------------------------------
void VstPlug::getProgramName(char *name)
{
	strcpy(name, programName);
}

//-----------------------------------------------------------------------------------------
void VstPlug::setParameter(long index, float value)
{
	switch (index){
	case  0:  fGain = value; break;
	case  1:  Freq = value; 
	procobj1->Set("frequency", Freq*1000);
    break;         
	case  2:  Fdb = value;
	procobj1->Set("feedback gain", Fdb);
    break; 
	}
}

//-----------------------------------------------------------------------------------------
float VstPlug::getParameter(long index)
{
	float out = 0;
	switch (index){
	case  0:  out = fGain; break;
	case  1:  out = Freq;  break;
	case  2:  out = Fdb; break;
	}
	return out;
}

//-----------------------------------------------------------------------------------------
void VstPlug::getParameterName(long index, char *label)
{
	switch (index) {
	case 0: strcpy(label, "    Gain   "); break;
	case 1: strcpy(label, " Frequency "); break;
	case 2: strcpy(label, " Feedback "); break;
	}
}

//-----------------------------------------------------------------------------------------
void VstPlug::getParameterDisplay(long index, char *text)
{
	switch(index){
	case 0: dB2string(fGain, text); break;
	case 1: float2string(Freq, text); break;
    case 2: float2string(Fdb, text); break;
	}
}

//-----------------------------------------------------------------------------------------
void VstPlug::getParameterLabel(long index, char *label)
{
	switch(index){
	case 0: strcpy(label, "  dB  "); break;
	case 1: strcpy(label,  "Hz(x1000)"); break;
    case 2: strcpy(label,   "      "); break;
	}
}

//-----------------------------------------------------------------------------------------
void VstPlug::process(float **inputs, float **outputs, long sampleFrames)
{
    float *in1  =  inputs[0];
    float *in2  =  inputs[1];
    float *out1 = outputs[0];
    float *out2 = outputs[1];

    channel1->PushIn(in1, sampleFrames);

	(*channel1) *= fGain;

	procobj1->DoProcess();

    procobj1->AddOut(out1, sampleFrames);
	procobj1->AddOut(out2, sampleFrames);

}

//-----------------------------------------------------------------------------------------
void VstPlug::processReplacing(float **inputs, float **outputs, long sampleFrames)
{
    float *in1  =  inputs[0];
    float *in2  =  inputs[1];
    float *out1 = outputs[0];
    float *out2 = outputs[1];

	channel1->PushIn(in1, sampleFrames);

   	(*channel1) *= fGain;

    procobj1->DoProcess();

    procobj1->PopOut(out1, sampleFrames);
    procobj1->PopOut(out2, sampleFrames); 
}
