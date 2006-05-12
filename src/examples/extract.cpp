#include <SndObj/AudioDefs.h>

int
main(int argc, char** argv){


SndWave infile(argv[1], READ);
SndIn   sig1(&infile,1);
SndIn   sig2(&infile,2);
SndAiff output1(argv[2], OVERWRITE);
SndAiff output2(argv[3], OVERWRITE);

output1.SetOutput(1, &sig1);
output2.SetOutput(1, &sig1);

while(!infile.Eof()){

infile.Read();
sig1.DoProcess();
sig2.DoProcess();
output1.Write();
output2.Write();

}

return 0;
}

