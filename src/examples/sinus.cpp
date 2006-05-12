// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include <SndObj/AudioDefs.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifndef WIN32
#include <unistd.h>
#endif
 
int
main(int argc, char** argv){

    if(argc != 8) {
	 cout << argv[0] << " infile.wav outfile.wav timestr pitch thresh intracks outracks\n";
     return 1;
	}
        time_t ts, te;
	char* infile = argv[1];
	char* outfile = argv[2];	
	float stratio = atof(argv[3]);  // time-stretch ratio
	float pitch = atof(argv[4]);
	float thresh = atof(argv[5]);  // analysis threshold
	int intracks = atoi(argv[6]);  // analysis max number of tracks
	int outracks = atoi(argv[7]);  // synthesis */
	int fftsize = 2048;     // FFT analysis size 2048
	int decimation = 512;      // analysis hopsize
	int interpolation = (int)(decimation*stratio); // synthesis hopsize  
	float scale = 1.f;   // scaling factor */
	
         time(&ts);

	// SndObj objects set-up  
	 
	SndThread thread;    //  processing thread
	
	HarmTable table(10000, 1, 1, 0.25);    // cosine wave
	 
	HammingTable window(fftsize, 0.5); // hanning window
	
	// input sound
	SndWave input(infile,READ,1,16,0,0.f,decimation);
	SndIn   insound(&input, 1, decimation);
	
	// IFD analysis
	IFGram ifgram(&window,&insound,1.f,fftsize,decimation);
	// Sinusoidal analysis
	SinAnal sinus(&ifgram,thresh,intracks, 1, 3);
	// Sinusoidal resynthesis
	AdSyn synth(&sinus,outracks,&table,pitch,scale,interpolation);
	// output sound
        // SndRTIO output(1,SND_OUTPUT,16384,10,SHORTSAM,0,interpolation);
        SndWave output(outfile, OVERWRITE,1,16,0,0.f,interpolation);
	output.SetOutput(1, &synth);
	
	// sound thread set-up
	
	thread.AddObj(&insound);
	thread.AddObj(&ifgram);
	thread.AddObj(&sinus);
        thread.AddObj(&synth);
	thread.AddObj(&input, SNDIO_IN);
	thread.AddObj(&output, SNDIO_OUT); 
 
	
	thread.ProcOn();
	
	while(!input.Eof());

	thread.ProcOff();
   
	time(&te);	cout << " process time (secs): " << (te -ts) << "\n";
	return 0;
}

