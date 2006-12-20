#include "Instrument.h"

Instrument::Instrument()
{
    int i;

	/* input */
	input = new SndRTIO(2, SND_INPUT, 1024);
    sound = new SndIn(input, 1);

    /* strings */
	fr[0] =  73.4f;
	res[0] = .99f;
    fr[1] =  130.8f;
	res[1] = .993f;
	fr[2] =  233.0f;
	res[2] = .996f;
    fr[3] =  392.0f;
	res[3] = .999f;
	
	strmix = new Mixer;
	for (i = 0; i < 4; i++){
	string[i] = new StringFlt(fr[i], res[i], sound);
	gstr[i] = 0.f;
    strgain[i] = new Gain(gstr[i], string[i]);
	strmix->AddObj(strgain[i]);
    StringOff(i);
	}

	/* loops */
	loop[0] = new SndLoop(.15f, .8f, sound);
	loop[1] = new SndLoop(.5f, 2.4f, sound);
	loop[2] = new SndLoop(.8f, 4.8f, sound);
	loop[3] = new SndLoop(1.2f, 9.f, sound);

    loopmix = new Mixer;
	for (i = 0; i < 4; i++){
	gloop[i] = 0.f;
	loopgain[i] = new Gain(gloop[i], loop[i]);
      loopmix->AddObj(loopgain[i]);
      LoopOff(i);
	}
	ap[0] = new Allpass(.6f, .05f, loopmix);
	ap[1] = new Allpass(.75f, .09f, ap[0]);

	outchannel[0] = strmix;
	outchannel[1] = ap[1];
    output = new SndRTIO(2,SND_OUTPUT, 1024, 4, SHORTSAM, outchannel);
	

 	thread = new SndThread();

	thread->AddObj(sound);
	for(i=0; i<4; i++){
		thread->AddObj(string[i]);
		thread->AddObj(strgain[i]);
		thread->AddObj(loop[i]);
		thread->AddObj(loopgain[i]);
	}
	thread->AddObj(strmix);
	thread->AddObj(loopmix);
	thread->AddObj(ap[0]);
	thread->AddObj(ap[1]);
	
	thread->AddObj(input, SNDIO_IN);
	thread->AddObj(output, SNDIO_OUT);
	process_on = false;
}

Instrument::~Instrument()
{
  ProcessOff();
  delete input;
  for(int i=0;i <4; i++){
  delete string[i];
  delete strgain[i];
  delete loop[i];
  delete loopgain[i];
  }
  delete ap[0];
  delete ap[1];
  delete strmix;
  delete loopmix;
  delete thread;
  delete output;

}

void Instrument::ProcessOn()
{
   if(!process_on){
	   thread->ProcOn();
	   process_on = true;
   }
}


void Instrument::ProcessOff()
{
   if(process_on){
	   thread->ProcOff();
	   process_on = false;
	   for(int i = 0; i < 4; i++) {
        StringOff(i);
        LoopOff(i);
	   }
   }
}

void Instrument::SetFreq(int no, float freq)
{
if(no >= 0 && no < 4) string[no]->SetFreq(freq);
}

void Instrument::SetRes(int no, float res)
{
if(no >= 0 && no < 4) string[no]->SetFdbgain(res);
}

void Instrument::SetStrGain(int no, float gain)
{
if(no >= 0 && no < 4) strgain[no]->SetGain(gain);
}

void Instrument::SetLoopGain(int no, float gain)
{
if(no >= 0 && no < 4) loopgain[no]->SetGain(gain);
}

void Instrument::SetPitch(int no, float pitch)
{
if(no >= 0 && no < 4) loop[no]->SetPitch(pitch);
}

void Instrument::StringOn(int no)
{
	if(no >= 0 && no < 4){
       strgain[no]->Enable();
	   string[no]->Enable();
	   }
}

void Instrument::StringOff(int no)
{
	if(no >= 0 && no < 4){
       strgain[no]->Disable();
	   string[no]->Disable();
	   }
}

void Instrument::LoopOn(int no)
{
	if(no >= 0 && no < 4){
       loopgain[no]->Enable();
	   loop[no]->Enable();
	   }
}

void Instrument::LoopOff(int no)
{
if(no >= 0 && no < 4){
       loopgain[no]->Disable();
	   loop[no]->Disable();
	   }
}

void Instrument::ReSample(int no)
{
if(no >= 0 && no < 4) loop[no]->ReSample();
}
