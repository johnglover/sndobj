#include <SndObj/AudioDefs.h>
#include <stdio.h>

void Usage(char* progr);

int
main(int argc, char** argv){

 float dur, time;
 
 if(argc == 3){
 dur = (float) atof(argv[1]);
 time = (float) atof(argv[2]);
  
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
 PVBlur blur(&anal, time);
 PVS synth(&window, &blur);

 output.SetOutput(1, &synth);
 
 int end = (int)(dur*DEF_SR/DEF_VECSIZE);
 
 for(int i=0; i<end; i++){ 

   input.Read();
   in.DoProcess();
   anal.DoProcess();
   blur.DoProcess();
   synth.DoProcess();
   output.Write();
}

return 0;

}

void Usage(char* progr) {
 
	cout << progr << " dur(s) blur_time\n";
	cout << "        where blur_time is the spectral\n";
    cout << "         blurring time period\n";
}



