// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//******************************************************//
// pluck.cpp                                            //
// Sample application using SndObj classes.             //
// Synthesizes a plucked string sound, using            //
// an implementation of the Karplus-Strong algorithm.   //
//          Victor Lazzarini, 2001                      // 
//******************************************************//

#include <stdlib.h>
#include <math.h>
#include <SndObj/AudioDefs.h>

void usage();

int
main(int argc, char* argv[]){


float dur, res;

#ifdef WIN    // port is int on WIN
int port;
#endif
#if defined(SGI) || defined(OSS)
char port[50]; // port is char on OSS/Irix
#endif


if(argc > 1) {
	usage();
	return 0;
}

cout << "pluck: MIDI-controlled string emulation using Karplus-Strong-based object.\n\n";

cout << "duration (secs.): ";
cin >> dur;
cout << "sustain factor (0 - 1.0): ";
cin >> res;

#ifdef WINMIDI
cout << MidiDeviceList();
#endif
cout << "Enter MIDI port: ";
cin >> port;


// conversion table (12-note equal tempered, A3 = 440Hz)
NoteTable ptable; 

// midi stuff: note (midi note), conversion (equiv. in tempered Hz)
// and pitch (bends the conversion output)
SndMidiIn* midi = new SndMidiIn(port, 10);
MidiIn* note = new MidiIn(midi);
Lookup* conversion = new Lookup(&ptable, 0, note); 
Bend*  pitch = new Bend(conversion, midi, 10.f);
char cur_note = 0;

// Envelope and Pluck objects

Pluck* pluck = new Pluck(0.f, 32767.f, res, pitch);
Gain*  gain  = new Gain(-90.f, pluck);

// set the output

SndRTIO* output = new SndRTIO(1, SND_OUTPUT);
output->SetOutput(1, gain);

// processing loop
unsigned long n, end = (long)(dur*gain->GetSr())/gain->GetVectorSize();
for(n=0; n < end; n++){

  midi->Read(); 
  note->DoProcess();

 if(cur_note == midi->NoteOff())   // if current note is 
     gain->SetGain(-90.f);  	      //  switched off  
 
 if(midi->NoteOn() != -1){         // if a new note is detected
  cur_note = midi->LastNote();     // set the cur_note to its value
  pluck->RePluck();
  gain->SetGain(midi->Velocity(cur_note) - 127.f); // and the gain	  
  }
 
   conversion->DoProcess();    // convert to tempered freq
   pitch->DoProcess();         // bend it 
   pluck->DoProcess();    // Pluck generator
   gain->DoProcess();
   output->Write();

                     }
delete output;
delete gain;
delete pluck;
delete pitch;
delete conversion;
delete note;
delete midi;

 cout << "Synthesis OFF \n";

return 1;
}

void
usage(){
   cout <<   "\n"  <<


   "//******************************************************//" << "\n" <<
   "// pluck                                                //" << "\n" <<
   "// Sample application using SndObj classes.             //" << "\n" <<
   "// Synthesizes a plucked-string sound using an          //" << "\n" <<
   "// implementation of the Karplus-Strong algorithm.      //" << "\n" <<
   "//          Victor Lazzarini, 1998                      //" << "\n" <<
   "//******************************************************//" << "\n";

  cout <<
    "\nusage:" <<
    "\npluck\n";
    
  return;              
       }



