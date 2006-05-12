#include <SndObj/AudioDefs.h>
#include "../PVTransp.h"
#include <iostream>

int
main(int argc, char** argv){

  int i;
  float dur = 6.f; // dur in secs
  float sr = DEF_SR; // sampling rate 
  int   vecsize = 256; // DSP vector size
  float kr = sr/vecsize; // control rate 

  // table object
 // HarmTable table1(1024,1,SINE); 

 SndRTIO* input = new SndRTIO(1, SND_INPUT);
 //SndWave input("blackbird.wav", READ);
// SndWave input("pianoc2.wav", READ);
 HammingTable window(1024, 0.54f);
 //PVTable table2(1024,&input,&window, 0.f, 0.15f);

  // control-rate objects
 //ADSR amp(.1f, 16000.f, .2f, 8000.f, .5f, 2.0f,0,1,kr);
 // IADSR freq(440.f, .1f, 880.f, .2f, 660.0f, .5f, 440.0f, 2.0f,0,1,kr); 

  // SndRTIO insig(1, SND_INPUT);
  // audio-rate objects
  SndIn  in(input);
  //SndIN file(&input);
  PVA   anal(&window, &in, 0.5f);
  //PVA   anal2(&window, &file); 
  PVTransp mask(&anal, 1.5f);
  PVS   synth(&window, &mask);
  //Oscili   oscil(&table1, 0.f, 0.f, &freq, &amp, vecsize, sr);  
  SndRTIO output(1, SND_OUTPUT);
  //SndWave  output("test.wav", OVERWRITE, 1);
  output.SetOutput(1, &synth);
 
  
  for(i=0; i<dur*kr;i++){ 

  // the objects below are effectively running at control rate
  // since their vector size is 1
  //freq.DoProcess();
  //amp.DoProcess();

  // these two objects run at full SR 
   input->Read();
	  in.DoProcess();
	  anal.DoProcess();

 mask.DoProcess();
 synth.DoProcess();
 output.Write();

  
}
delete input;
return 0;
}