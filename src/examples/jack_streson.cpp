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
float fdbgain;
float gain;
float* fr;
float dur, sr=44100.f;

ifstream  datafile;

switch(argc){
case 1:
	

 cout << "streson: string resonator \n\n";
	 

   // prompt for parameters
 cout << "Enter number of strings: ";
 cin  >> nstrs;
 cout << "Enter feedback gain (0 < fbd < 1): ";
 cin  >> fdbgain;
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
    datafile >> fdbgain;
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
//input = new SndRTIO(1, SND_INPUT);
//output= new SndRTIO(1, SND_OUTPUT);

SndJackIO *jack = new SndJackIO("streson");

// Sound input, attenuation, string filters 
SndIn* sound = new SndIn(jack);

// String Filters
StringFlt** strings = new StringFlt*[nstrs];
for(i=0;i<nstrs; i++)
 strings[i] = new StringFlt(fr[i], fdbgain, sound, 
	   0, DEF_VECSIZE, sr);
           
Mixer* mix = new Mixer(nstrs, (SndObj **) strings, DEF_VECSIZE, sr);
Gain*  atten = new Gain(gain, mix, DEF_VECSIZE, sr);


jack->SetOutput(1, atten);
jack->SetOutput(2, atten);

// processing loop

unsigned long n, end = (unsigned long)(dur*(sr/DEF_VECSIZE));
for(n=0; n < end; n++){

 jack->Read();         // input from ADC
 sound->DoProcess();    // sound input
  for(i=0; i < nstrs; i++){ 
      strings[i]->DoProcess(); // string filters
  } 

  mix->DoProcess();       // mixer
  atten->DoProcess();    // attenuation
  jack->Write();
     
                     }

delete jack;
delete atten;
delete mix;
delete[] strings;
delete sound;
	       
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
    << "number_of_strings \nfeedback_gain \nattenuation(dB)\n" <<
       "string1_freq \nstring2_freq \n... \nstringN_freq \n\n"; 
 return;              
       }

