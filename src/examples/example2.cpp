// Example2.cpp
// A dirty reverb showing the use of
// standard operators (+, <<, >>)
// VL, 2001

#include <SndObj/AudioDefs.h>

int
main(int argc, char** argv){

  int dur = 60;
  SndRTIO  input(1, SND_INPUT);
  SndObj  audio;
  Allpass ap1(.1f, .005f, &audio);
  Allpass ap2(.55f, .013f, &ap1);
  Allpass ap3(.6f, .022f, &ap2);
  Allpass ap4(.7f, .035f, &ap3);

  SndRTIO output(1, SND_OUTPUT);
  

 for(int i=0; i<dur*(DEF_SR/DEF_VECSIZE);i++){

 audio<<input;

 ap1.DoProcess();
 ap2.DoProcess();
 ap3.DoProcess();
 ap4.DoProcess();
 audio += ap4;

 audio>>output; 
 
  }

  return 1;
}
