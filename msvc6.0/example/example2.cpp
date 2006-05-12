// Example2.cpp
// A dirty reverb showing the use of
// standard operators (+, <<, >>)
// VL, 2001

#include <SndObj/AudioDefs.h>

int
main(int argc, char** argv){

  int dur = 2;
  SndASIO  output(2, SND_OUTPUT, "M-Audio Quattro ASIO");
  SndObj  audio;
  	HarmTable table(10000, 1, 1, 0.25); 
  SndAiff input("test.aif", READ);
  	SndIn in(&input, 1);
	output.SetOutput(1, &in);

	  //SndAiff outfile("test.aif", OVERWRITE,1,24);
	//outfile.SetOutput(1, &in);

    Oscilt osc(&table, 440.f, 41944304.f);
    Allpass ap1(0.3f, .001f,  &in);
  Allpass ap2(.55f, .013f, &ap1);
  Allpass ap3(.6f, .022f, &ap2);
  Allpass ap4(.7f, .035f, &ap3);

 


 for(int i=0; i<dur*(DEF_SR/DEF_VECSIZE);i++){

input.Read();
 in.DoProcess();
 ap1.DoProcess();
 ap2.DoProcess();
 ap3.DoProcess();
 osc.DoProcess();
 //outfile.Write();
 output.Write();

  }

  return 1;
}
