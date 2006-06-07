// Example2.cpp
// A dirty reverb showing the use of
// standard operators (+, <<, >>)
// VL, 2001

#include <SndObj/AudioDefs.h>
#include <iostream>

int
main(int argc, char** argv){

  int dur = 4;
  SndASIO  output(2, SND_OUTPUT, "M-Audio Quattro ASIO");
  SndObj  audio;
  //	HarmTable table(10000, 1, 1, 0.25); 
  //SndAiff input("test.aif", READ);
  //SndIn in(&input, 1);

  int SAMPLE_DURATION = dur;
	  //SndAiff outfile("test.aif", OVERWRITE,1,24);
	//outfile.SetOutput(1, &in);

/*    Oscilt osc(&table, 440.f, 41944304.f);
    Allpass ap1(0.3f, .001f,  &in);
  Allpass ap2(.55f, .013f, &ap1);
  Allpass ap3(.6f, .022f, &ap2);
  Allpass ap4(.7f, .035f, &ap3);
*/
     Rand noise(1000.f);
   float segs[3] = { 0.05f, 0.01f, 0.01f};
   float lens[3] = { 0.01f, 0.19f, 0.8f};
   SpecEnvTable    stab(1024,3, 1.f, segs,lens);
   HammingTable    win(1024, 0.5f);
   FFT                fft(&win, &noise);  // &in
   SpecMult            fil(&stab, &fft);
   IFFT                ifft(&win, &fil);

   float highest = 0.f;
   for (int size = 0; size < SAMPLE_DURATION*44100; )
   {
       //input.Read();
       noise.DoProcess();
       //in.DoProcess();
       fft.DoProcess();
       fil.DoProcess();
       ifft.DoProcess();
       SndObj & out = ifft;
       for (int i = 0; size < SAMPLE_DURATION*44100 && i < out.GetVectorSize(); i ++, size ++)
       {
           double val = out.Output(i); // values in the thousands
           //buffer[size] = (char) (val * 127);
		   highest = val > highest ? val : highest;
       }
	    out >> output;
   }
cout << "\n" << highest << "\n";

  return 1;
}
