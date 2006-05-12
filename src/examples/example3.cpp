// Example3.cpp
// MIDI-controlled synthesizer using
// control & audio rates
// VL, 2001

#include <SndObj/AudioDefs.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char** argv){

  int i;
  float dur = 30.f; // dur in secs
  float sr = DEF_SR; // sampling rate 
  int   vecsize = 100; // DSP vector size
  float kr = sr/vecsize; // control rate 
  short cur_note = 0; // current note
  float cur_amp = 0.f;

  // table objects
  NoteTable ptable;  
  HarmTable table1(1024,20,SAW);  
  // midi input
  SndMidiIn midi;


  // control-rate objects
  MidiIn note(&midi,NOTE_MESSAGE,1,1,kr);
  Lookup conversion(&ptable,0,&note,WRAP_AROUND,RAW_VALUE,1,kr); 
  Bend  pitch(&conversion, &midi, 10.f, 1, 1, kr); 
  Interp amp(0.f, cur_amp, .05f, 0.f, 1, kr);

  // audio-rate objects
  Oscil   oscil(&table1, 0.f, 0.f, &pitch, &amp, vecsize, sr);  
  SndRTIO output(1, SND_OUTPUT, 128, 10, SHORTSAM,0, vecsize, sr);
  output.SetOutput(1, &oscil);
 
  
  for(i=0; i<dur*kr;i++){ 

  midi.Read();

  // the objects below are effectively running at control rate
  // since their vector size is 1
  note.DoProcess();
  conversion.DoProcess();
  pitch.DoProcess();
  amp.DoProcess();
 
  if(cur_note == midi.NoteOff()){   // if current note is  OFF
  amp.SetCurve(cur_amp, 0.f); 
  }
  if(midi.NoteOn() != -1){     // if a new note is detected
  cur_note = midi.LastNote(); 
  cur_amp = midi.Velocity(cur_note)*100;
  amp.SetCurve(0.f, cur_amp); 
  }

  // these two objects run at full SR 
  oscil.DoProcess();
  output.Write();
	
  }

  return 1;
}
