// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

/////////////////////////
// fir.cpp : FIR filter example, using
//           an impulse table.derived 
//           from a spectral magnitude
//           curve.

#include <SndObj/AudioDefs.h>

int main(int argc, char** argv) {
 
   // lowpass response
   // cf = sr/10
   // trans bw = sr/10
   float max = 1.f;
   float min = 0.f;
   float cf = 0.1f;
   float tbw = 0.1f;
   
   // magnitude response curve
   float points[3]= {max,min,min};
   float lens[3]= {cf,tbw,1-(cf+tbw)};
   
   // using Hamming window
   // filter order = 3.33*sr/tbw
   int order = 333;
   HammingTable window(order, 0.54f);
   ImpulseTable imp(order,3, 1.f, points, lens, 0.f,&window); 
   
   // test signal wavetable
   HarmTable t1(1024, 50, SAW);
   SndWave  output("test.wav", OVERWRITE); /* output */
   Oscili oscil(&t1, 100.f, 32767.f);  /* test signal */
   Convol fil(&imp, &oscil, 16.f);  /* filter */

  int dur = 5;
  for(int i=0; i<dur*(DEF_SR/DEF_VECSIZE); i++) {
	oscil.DoProcess();
	fil.DoProcess();
	fil >> output;
  }
  return 0;
}
