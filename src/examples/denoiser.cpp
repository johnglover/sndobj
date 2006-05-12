// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include <SndObj/AudioDefs.h>
#include <iostream>


void Usage(int argc, char** argv);

int
main(int argc, char** argv){

 
 if(argc != 5){
     Usage(argc,argv);
     return 1;
 }
	 
 // amount of mask attenuation (dB)
 float amount = (float)pow(10, atof(argv[4])/20.f);
 
 // masking file
 SndWave inmask(argv[2], READ);
 // input file
 SndWave infile(argv[1], READ);

 // Hamming window
 HammingTable window(DEF_FFTSIZE, 0.54f);
 // masking table
 PVTable table2(DEF_FFTSIZE,&inmask,&window, 0.f, 1.f);

 // input signal
 SndIn  in(&infile);
 // PV analysis
 PVA   anal(&window, &in, 0.6f);
 // Masking
 PVMask mask(amount, &table2, &anal);
 // PV synthesis
 PVS   synth(&window, &mask);
 // output file
 SndWave  output(argv[3], OVERWRITE, 1);
 output.SetOutput(1, &synth);
 // processing loop
 while(!infile.Eof()){ 

   infile.Read();
   in.DoProcess();
   anal.DoProcess();
   mask.DoProcess();
   synth.DoProcess();
   output.Write();  
   
}

return 0;

}

void 
Usage(int argc, char** argv){

	std::cout << "Wrong number of arguments: "
		      <<  argc << ".\n";

	std::cout << "Usage:\n" <<
	argv[0] << " input.wav mask.wav output.wav noise_atten(dB)\n";
}
