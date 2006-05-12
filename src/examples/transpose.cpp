#include <SndObj/AudioDefs.h>
#include <stdio.h>

void Usage(char* progr);

int
main(int argc, char** argv){

 float dur, pitch;
 int formants;

 if(argc == 4){
 dur = (float) atof(argv[1]);
 pitch = (float) atof(argv[2]);
 formants = atoi(argv[3]);
 }
 else {
 Usage(argv[0]);
 exit(1);
 }
#ifndef MACOSX
SndRTIO output(1, SND_OUTPUT);
SndRTIO input(1, SND_INPUT);
#else
SndCoreAudio io(1);
#define input io
#define output io
#endif
 

 HammingTable window(1024, 0.54f);

 SndIn in(&input);
 PVA anal(&window, &in); 
 PVTransp trans(&anal, pitch,formants);
 PVS synth(&window, &trans);

 output.SetOutput(1, &synth);
 
 int end = (int)(dur*DEF_SR/DEF_VECSIZE);
 
 for(int i=0; i<end; i++){ 

   input.Read();
   in.DoProcess();
   anal.DoProcess();
   trans.DoProcess();
   synth.DoProcess();
   output.Write();
}

return 0;

}

void Usage(char* progr) {
 
	cout << progr << " dur(s) pitch formants\n";
	cout << "        where pitch is the transposition factor\n";
    cout << "     and formants => 1=keep formants 0=ignore formants\n";
}




