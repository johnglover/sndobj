// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//******************************************************//
// cvoc.cpp                                             //
// Sample application using SndObj classes.             //
// N-filter channel vocoder using Butterworth-          //
// response filters                                     //
//          Victor Lazzarini, 1998                      // 
//******************************************************//
#include <fstream>
#include <stdlib.h>
#include <SndObj/AudioDefs.h>
void usage();

main(int argc, char *argv[]){

int nfltrs;
float Q;
float gain;
float* fr;

SndWave *input1;
SndWave *input2;
SndWave *output;

if(argc == 4){

   // prompt for parameters
 cout << "Enter number of filters: ";
 cin  >> nfltrs;
 cout << "Enter Q: ";
 cin  >> Q;
 cout << "Enter gain cut/boost(dB): ";
 cin  >>  gain;
    
 fr = new float[nfltrs];
 for(int i=0; i<nfltrs; i++){
   cout << "filter" << (i+1) << " frequency: ";
   cin  >>  fr[i];
  }
}
else {
	 if(argc == 5){
   // get the parameters from file
    ifstream datafile(argv[4]);
    datafile >> nfltrs;
    datafile >> Q;
    datafile >> gain;
    fr = new float[nfltrs];
    for(int i=0;i<nfltrs; i++) 
        datafile >> fr[i];
	 }
 else {
    usage();
    return 0;
 }
	 }

 // RIFF-Wave file IO objects
 input1 = new SndWave(argv[1], READ);
 input2 = new SndWave(argv[2], READ);
 if((input1->GetSr() != 44100.f) || (input2->GetSr() != 44100.f)){
	 cout << "Use ONLY 44100 KHz files\n";
     delete input1;
	 delete input2;
	 return 0;
 }

 output =  new SndWave(argv[3], OVERWRITE);

// Sound input, filters, balance, mix and atten 
SndIn sound1(input1, 1);  // control input
SndIn sound2(input2, 1);  // audio input
ButtBP* Infilters = new ButtBP[nfltrs];
ButtBP* Outfilters = new ButtBP[nfltrs];
Balance* bln = new Balance[nfltrs];
Mixer mix;

// Filters
for(int i=0;i<nfltrs; i++){
   Infilters[i].SetFreq(fr[i]);
   Infilters[i].SetBW(fr[i]/Q);
   Infilters[i].SetInput(&sound1);
   Outfilters[i].SetFreq(fr[i]);
   Outfilters[i].SetBW(fr[i]/Q);
   Outfilters[i].SetInput(&sound2);
   bln[i].SetInput(&Outfilters[i], &Infilters[i]); 
   mix.AddObj(&bln[i]);
}

Gain  atten(gain, &mix);
output->SetOutput(1, &atten);

// processing loop
unsigned long n, end = (unsigned long)(input1->GetDataFrames()/DEF_VECSIZE);

for(n=0; n < end; n++){

  input1->Read();         // input from file 
  input2->Read();         // input from file 
  sound1.DoProcess();    // sound input
  sound2.DoProcess();    // sound input
  for(int i=0; i < nfltrs; i++){
      Infilters[i].DoProcess();  // input filters
      Outfilters[i].DoProcess(); // output filters
      bln[i].DoProcess();        // env follower
  } 
  mix.DoProcess();      // mixer
  atten.DoProcess();    // attenuation
  output->Write();      // output to file

                     }
		       
delete input1;
delete input2;
delete output;

return 1;
}


void
usage(){
   cout <<   "\n"  <<
   "//******************************************************//" << "\n" <<
   "// CVOC                                                 //" << "\n" <<
   "// Sample application using SndObj classes.             //" << "\n" <<
   "// N-filter channel vocoder using                       //" << "\n" <<
   "// Butterworth-response filters                         //" << "\n" <<
   "//          Victor Lazzarini, 1998                      //" << "\n" <<
   "//******************************************************//" << "\n";

  cout <<
    "\nusage:" <<
    "\ncvoc infile1.wav infile2.wav outfile.wav [datafile]\n\n" << 
    "imposes the spectrum of infile1, measured by the\n" <<
     "bank of N filters, onto infile2.\n" <<
     "Datafile is an optional text file containing\n" << 
     "the following parameters:\n"
    << "number_of_filters \nQ factor\ncut/boost(dB)\n" <<
       "filter1_freq \nfilter2_freq \n... \nfilterN_freq \n\n"; 
 return;              
       }

