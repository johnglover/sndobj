// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//******************************************************//
// RTSCHROEDER.cpp   (realtime version)                 //
// Sample application using SndObj classes.             //
// Standard reverberator for simulation of              // 
// medium-sized halls, as designed by M R Schroeder.    //
//          Victor Lazzarini, 1998                      // 
//******************************************************//


#include <stdlib.h>
#include <math.h>
#include <SndObj/AudioDefs.h>

void usage();

main(int argc, char* argv[]){

float rvt, rvgain, dur;
float kr = DEF_SR/DEF_VECSIZE;

#ifndef MACOSX
SndRTIO output(1, SND_OUTPUT);
SndRTIO input(1, SND_INPUT);
#else
SndCoreAudio io(1);
#define input io
#define output io
#endif

if(argc == 1){
     
	cout << "schroeder: standard reverberator based on Schroeder design.\n\n";
 
	cout << "duration(s):";
	cin >> dur;
	cout << "reverb time(secs.):";
	cin >> rvt;
    cout << "reverb gain(dB):";
    cin >> rvgain;

}
else {

if(argc != 4){
     usage();
    return 0;
             }
// command line args
rvt = (float) atof(argv[2]);
rvgain = (float) atof(argv[3]);
dur =(float) atof(argv[1]);

 }




// comb filter g's
float g1 = (float) pow(.001,.0297/rvt); 
float g2 = (float) pow(.001,.0371/rvt); 
float g3 = (float) pow(.001,.0411/rvt); 
float g4 = (float) pow(.001,.0437/rvt); 



// comb, allpass, mixers and gain objects
SndIn insound(&input, 1);
Comb c1(g1, .0297f, &insound); 
Comb c2(g2, .0371f, &insound); 
Comb c3(g3, .0411f, &insound); 
Comb c4(g4, .0437f, &insound); 
Mixer mix, mix2;


// set the two mixer objs inputs
mix.AddObj(&c1);
mix.AddObj(&c2);
mix.AddObj(&c3);
mix.AddObj(&c4);

Allpass a1(.7f,0.01f, &mix); 
Allpass a2(.7f,0.0017f, &a1);
Gain    direct(-6.f,&insound);
Gain    reverb(rvgain-6.f, &a2);


mix2.AddObj(&direct);
mix2.AddObj(&reverb);

// set the output

output.SetOutput(1, &mix2);

// loop counter and end
unsigned long n, end = 
        (long) (kr*(dur+rvt));

// processing loop
for(n=0; n < end; n++){
  if(n == (unsigned long) dur*kr)
               insound.Disable();  // switch off input 
   input.Read();                   // signal input
   insound.DoProcess();            // input sound
   c1.DoProcess();                 // 4 comb filter units 
   c2.DoProcess();
   c3.DoProcess();
   c4.DoProcess();
   mix.DoProcess();                // comb's mixer
   a1.DoProcess();                 // 2 allpass filter units
   a2.DoProcess();
   direct.DoProcess();             // direct sound
   reverb.DoProcess();             // reverb sound
   mix2.DoProcess();               // final mix
   output.Write();                 // file output

}
 //delete output;
 //delete input;

 return 1;
}
void
usage(){
   cout <<   "\n"  <<
   "//******************************************************//" << "\n" <<
   "// SCHROEDER     (realtime version)                     //" << "\n" <<
   "// Sample application using SndObj classes.             //" << "\n" <<
   "// Standard reverberator for simulation of              //" << "\n" <<
   "// medium-sized halls, as designed by M R Schroeder.    //" << "\n" <<
   "//          Victor Lazzarini, 1999                      //" << "\n" <<
   "//******************************************************//" << "\n";

  cout <<
  "\nusage:\nschroeder [dur(s) rev_time(s) rev_gain(dB)]\n\n";
  return;              
       }


