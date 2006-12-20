
#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include "SndObj/AudioDefs.h"

class Instrument  
{
  float res[4];
  float fr[4];
  float gloop[4];
  float gstr[4];
 
  bool process_on;

  // SndObjs
  StringFlt *string[4];
  Gain      *strgain[4];
  Gain    *loopgain[4];
  Mixer   *strmix;
  Mixer   *loopmix;
  SndIn   *sound;
  SndLoop *loop[4];
  Allpass *ap[2];
  SndIO   *input;
  SndIO   *output;
  SndObj  *outchannel[2];
  SndThread *thread;

 public:

  void ReSample(int no){
    if(no >= 0 && no < 4) loop[no]->ReSample();
  }
  void LoopOff(int no){
    if(no >= 0 && no < 4){
      loopgain[no]->Disable();
      loop[no]->Disable();
    }
  }
  void LoopOn(int no){
    if(no >= 0 && no < 4){
      loopgain[no]->Enable();
      loop[no]->Enable();
    }
  }
  void StringOff(int no){
    if(no >= 0 && no < 4){
      strgain[no]->Disable();
      string[no]->Disable();
    }
  }
  void StringOn(int no){
    if(no >= 0 && no < 4){
      strgain[no]->Enable();
      string[no]->Enable();
    }
  }
  void SetPitch(int no, float pitch){
    if(no >= 0 && no < 4) loop[no]->SetPitch(pitch);
  }
  void SetLoopGain(int no, float gain){
    if(no >= 0 && no < 4) loopgain[no]->SetGain(gain);
  }
  void SetStrGain(int no, float gain){
    if(no >= 0 && no < 4) strgain[no]->SetGain(gain);
  }
  void SetRes(int no, float res){
    if(no >= 0 && no < 4) string[no]->SetFdbgain(res);
  }
  void SetFreq(int no, float freq){
    if(no >= 0 && no < 4) string[no]->SetFreq(freq);
  }
  float GetFreq(int no){ 
    if(no<4 && no >= 0) return fr[no]; 
  }
  float GetRes(int no){ 
    if(no<4 && no >= 0) return res[no]; 
  }
  float GetLoopGain(int no){ 
    if(no<4 && no >= 0) return gloop[no]; 
  }
  float GetStrGain(int no){ 
    if(no<4 && no >= 0) return gstr[no]; 
  }
  void ProcessOff();
  void ProcessOn();
  Instrument();
  virtual ~Instrument();

};

#endif 
