#include "Instrument.h"

Instrument::Instrument()
{
  int i;

  /* input */
#ifndef MACOSX
  input = new SndRTIO(2, SND_INPUT, 1024, 4);
#else
  input = new SndCoreAudio(2);
#endif
  sound = new SndIn(input, 1);

  /* strings */
  fr[0] =  73.4f;
  dec[0] = 12.f;
  fr[1] =  130.8f;
  dec[1] = 12.f;
  fr[2] =  233.0f;
  dec[2] = 12.f;
  fr[3] =  392.0f;
  dec[3] = 12.f;
	
  strmix = new Mixer;
  for (i = 0; i < 4; i++){
    string[i] = new StringFlt(fr[i], sound, dec[i]);
    gstr[i] = 0.5f;
    value[i] = new  Unit(0.5f, UNIT_STEP);
    lp[i] = new LoPass(10.f, value[i]);
    strgain[i] = new Ring(lp[i], string[i]);
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

  /* output */
  outchannel[0] = strmix;
  outchannel[1] = ap[1];
#ifndef MACOSX
  output = new SndRTIO(2,SND_OUTPUT, 1024, 4, SHORTSAM, outchannel);
#else
  output = input;
  output->SetOutput(1, strmix);
  output->SetOutput(2, ap[1]);
#endif
  

  /* processing thread */
  thread = new SndThread();
  thread->AddObj(sound);
  for(i=0; i<4; i++){
    thread->AddObj(value[i]);
    thread->AddObj(lp[i]);
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
    delete value[i];
    delete lp[i];
    delete strgain[i];
    delete loop[i];
    delete loopgain[i];
  }
  delete ap[0];
  delete ap[1];
  delete strmix;
  delete loopmix;
  delete thread;
#ifndef MACOSX
  delete output;
#endif

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
