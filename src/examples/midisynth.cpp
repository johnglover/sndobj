// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//***********************************************************//
//     MIDISYNTH                                             //
//     Sample application using Sound Object Classes         //
//     to synthesize a cascading harmonics drone             //
//                Victor Lazzarini, 2001                     //
//***********************************************************//

#include <stdlib.h>
#include <SndObj/AudioDefs.h>


void usage();

main(int argc, char* argv[]){

float duration;
int harmonics; 

#ifdef WIN    // port is int on WIN
int port;
#endif
#if defined(SGI) || defined(OSS)
char* port; // port is char on OSS/Irix
#endif

if(argc == 1){

cout << "midisynth: MIDI-controlled cascading harmonics synth based on JC Risset design.\n\n";
cout << "duration (secs.): ";
cin >> duration;
cout << "harmonics: ";
cin >> harmonics;

#ifdef WIN
MidiDeviceList();  // List devices (only on WIN)
#endif
cout << "Enter MIDI port: ";
#ifndef WIN
port = new char[50];
#endif
cin >> port;
}

else {
if(argc != 4){
     usage();
    return 0;
             }
duration = (float)atof(argv[1]);   // duration.
harmonics = atoi(argv[2]);         // no of harmonics 
port = 
#ifdef WIN
       atoi
#endif
       (argv[3]);              // port   
}

//  wavetable
HarmTable table1(1024, harmonics, SQUARE);

// conversion table (12-note equal tempered, A3 = 440Hz)
NoteTable ptable;

// midi stuff: note (midi note), conversion (equiv. in tempered Hz)
// and pitch (bends the conversion output)
SndMidiIn midi(port, 10);
MidiIn note(&midi);
Lookup conversion(&ptable, 0, &note); 
Bend  pitch(&conversion, &midi, 10.f);
char cur_note = 0;

// 9 interpolating oscillator objects, slightly mistuned
Oscili oscil1(&table1, 0.f, 32767.f, &pitch);
Oscili oscil2(&table1, .03f, 32767.f, &pitch);
Oscili oscil3(&table1, .06f, 32767.f, &pitch);
Oscili oscil4(&table1, .09f, 32767.f, &pitch);
Oscili oscil5(&table1, .12f, 32767.f, &pitch);
Oscili oscil6(&table1, -.03f, 32767.f, &pitch);
Oscili oscil7(&table1, -.06f, 32767.f, &pitch);
Oscili oscil8(&table1, -.09f, 32767.f, &pitch);
Oscili oscil9(&table1, -.12f, 32767.f, &pitch);

//  Mixer & gain objects, 
Mixer  mix;

//   Add the oscili objects to the mixer input
mix.AddObj(&oscil1);
mix.AddObj(&oscil2);
mix.AddObj(&oscil3);
mix.AddObj(&oscil4);
mix.AddObj(&oscil5);
mix.AddObj(&oscil6);
mix.AddObj(&oscil7);
mix.AddObj(&oscil8);
mix.AddObj(&oscil9);
Gain   gain(-90.f,&mix); 

// DAC output
SndRTIO output(1, SND_OUTPUT);
output.SetOutput(1, &gain);


// synthesis loop, 'dur' is the duration in samples  
unsigned long dur = (unsigned long)(duration*mix.GetSr())/mix.GetVectorSize();

for(unsigned long n=0; n < dur; n++){
  midi.Read(); 
  note.DoProcess();

 if(cur_note == midi.NoteOff())   // if current note is 
     gain.SetGain(-90.f);  	      //  switched off  
 
 if(midi.NoteOn() != -1){         // if a new note is detected
  cur_note = midi.LastNote();     // set the cur_note to its value
  gain.SetGain(midi.Velocity(cur_note) - 130.f); // and the gain	  
  }

   conversion.DoProcess();    // convert to tempered freq
   pitch.DoProcess();         // bend it 
   oscil1.DoProcess();        // oscillators
   oscil2.DoProcess();
   oscil3.DoProcess();
   oscil4.DoProcess();
   oscil5.DoProcess();
   oscil6.DoProcess();
   oscil7.DoProcess();
   oscil8.DoProcess();
   oscil9.DoProcess();
   mix.DoProcess();      // mix
   gain.DoProcess();     // gain attenuation
   output.Write();       // file output             
                                } 

   cout << "Synthesis OFF \n";
   return 1; 
}

void
usage(){
   cout <<   "\n"  <<
   "//******************************************************//" << "\n" <<
   "// MIDISYNTH                                            //" << "\n" <<
   "// sample application using SndObj classes,             //" << "\n" <<
   "// synthesizes a cascading harmonics drone              //" << "\n" <<
   "// as designed by JC Risset (MIDI controlled)           //" << "\n" <<
   "//          Victor Lazzarini, 2001                      //" << "\n" <<
   "//******************************************************//" << "\n";

   cout <<
   "\nusage:\nmidisynth [dur(s) no_of_harmonics MIDI_input_port]\n\n";
  return;              
       }




