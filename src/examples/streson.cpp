// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//******************************************************//
// rtstreson.cpp  (new realtime version)                //
// Sample application using SndObj classes.             //
// Simulates a N-string "string resonator"              //
//                                                      //
//          Victor Lazzarini, 1998                      // 
//******************************************************//

#include <fstream>
#include <stdlib.h>
#include <SndObj/AudioDefs.h>

void usage();

main(int argc, char *argv[]){

int nstrs, i;
float decay;
float gain;
float* fr;
float dur, sr=44100.f;

SndIO* output;
SndIO* input;

ifstream  datafile;

switch(argc){
case 1:
	

 cout << "streson: string resonator \n\n";
	 

   // prompt for parameters
 cout << "Enter number of strings: ";
 cin  >> nstrs;
 cout << "Enter decay factor (dB/sec): ";
 cin  >> decay;
 cout << "Enter gain attenuation(dB): ";
 cin  >>  gain;
 fr = new float[nstrs];
 for(i=0; i<nstrs; i++){
   cout << "String" << (i+1) << " frequency: ";
   cin  >>  fr[i];
  }

    cout << "enter duration: ";
	cin >> dur;
 
 break;
 
case 3:
   // get the parameters from file
	dur = (float) (atof(argv[1]));  
    datafile.open(argv[3]);
	
    datafile >> nstrs;
    datafile >> decay;
    datafile >> gain;  
    fr = new float[nstrs];
    for(i=0;i<nstrs; i++)
       datafile >> fr[i];

    datafile.close();
 break;
 
default:
    usage();
    return 0;
}
#ifndef MACOSX
input = new SndRTIO(1, SND_INPUT, 1024);
output= new SndRTIO(1, SND_OUTPUT, 1024);
#else
 input = new SndCoreAudio(1);
 output = input;
#endif

// Sound input, attenuation, string filters 
SndIn* sound = new SndIn(input);

// String Filters
StringFlt** strings = new StringFlt*[nstrs];
for(i=0;i<nstrs; i++)
 strings[i] = new StringFlt(fr[i], sound, decay, 
	   0, DEF_VECSIZE, sr);
           
Mixer* mix = new Mixer(nstrs, (SndObj **) strings, DEF_VECSIZE, sr);
Gain*  atten = new Gain(gain, mix, DEF_VECSIZE, sr);


output->SetOutput(1, atten);
// processing loop

unsigned long n, end = (unsigned long)(dur*(sr/DEF_VECSIZE));
for(n=0; n < end; n++){

 input->Read();         // input from ADC
 sound->DoProcess();    // sound input
  for(i=0; i < nstrs; i++){ 
      strings[i]->DoProcess(); // string filters
  } 

  mix->DoProcess();       // mixer
  atten->DoProcess();    // attenuation
  output->Write();
     
                     }

delete output;
delete atten;
delete mix;
for(i=0;i<nstrs; i++)
   delete strings[i];
delete[] strings;
delete sound;
delete input;
	       
return 1;
}


void
usage(){
   cout <<   "\n"  <<
   "//******************************************************//" << "\n" <<
   "// STRESON     (new realtime version)                   //" << "\n" <<
   "// Sample application using SndObj classes.             //" << "\n" <<
   "// Simulates a n-string 'string resonator',             //" << "\n" <<
   "// tuned to user-defined frequencies                    //" << "\n" <<
   "//          Victor Lazzarini, 1998                      //" << "\n" <<
   "//******************************************************//" << "\n";

  cout <<
    "\nusage:" <<
    "\nstreson [dur datafile]\n\n" << 
     "where datafile is an optional text file containing\n" << 
     "the following parameters:\n"
    << "number_of_strings \ndecay_factor(dB/sec) \nattenuation(dB)\n" <<
       "string1_freq \nstring2_freq \n... \nstringN_freq \n\n"; 
 return;              
       }

