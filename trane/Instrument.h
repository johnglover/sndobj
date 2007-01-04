
#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include "SndObj/AudioDefs.h"

class Instrument  
{
  float dec[4];
  float fr[4];
  float gloop[4];
  float gstr[4];
 
  bool process_on;

  // SndObjs
  StringFlt *string[4];
  Unit   *value[4];
  LoPass  *lp[4];
  Ring      *strgain[4];
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
      value[no]->Disable();
      lp[no]->Disable();
      strgain[no]->Disable();
      string[no]->Disable();
    }
  }
  void StringOn(int no){
    if(no >= 0 && no < 4){
      value[no]->Enable();
      lp[no]->Enable();
      strgain[no]->Enable();
      string[no]->Enable();
    }
  }
  void SetPitch(int no, float pitch){
    if(no >= 0 && no < 4) loop[no]->SetPitch(pitch);
  }
  void SetLoopGain(int no, float gain){
    if(no >= 0 && no < 4) loopgain[no]->SetGain(gloop[no] = gain);
  }

  void SetStrGain(int no, float gain){
    if(no >= 0 && no < 4) value[no]->SetAmp(gstr[no] = gain);
  }

  void SetDec(int no, float re){
    if(no >= 0 && no < 4) {
   string[no]->SetDecay(dec[no] = re);
    }
  }
  void SetFreq(int no, float freq){
    if(no >= 0 && no < 4) string[no]->SetFreq(fr[no] = freq);
  }
  float GetFreq(int no){ 
    if(no<4 && no >= 0) return fr[no]; 
  }
  float GetDec(int no){ 
    if(no<4 && no >= 0) return dec[no]; 
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
