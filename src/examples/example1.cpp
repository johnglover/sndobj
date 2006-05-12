#include <SndObj/AudioDefs.h>

int
main(int argc, char** argv){


SndWave infile("pianoc2.wav", READ);
SndIn   sig(&infile);
PVA     spec(&window, sig)
Pitch   pitch(0.1f, &sig, 1.5f); 

SndASIO output(1, SND_OUTPUT);

output.SetOutput(1, &pitch);

while(!infile.Eof()){

infile.Read();
pitch.DoProcess();
sig.DoProcess();
output.Write();

}

return 0;
}

