// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information


#ifndef SndRead_h_
#define SndRead_h_

#include "SndObj.h"
#include "SndFIO.h"



class SndRead : public SndObj {

 protected:
  SndFIO* m_ioinput;
  SndObj** m_outobj;
  float m_pitch;
  double m_pos;
  float m_scale;
  int m_channels;
  int m_count;

 public:

  SndObj* Outchannel(int channel){ return m_outobj[channel%m_channels];}

  SndRead();
  SndRead(char* name, float pitch=1.f, float scale=1.f,
	  int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~SndRead();

  void SetInput(char* name);
  void SetScale(float scale){ m_scale = scale; }
  void SetPitch(float pitch) { m_pitch = fabs(pitch); }

  int Set(char* mess, float value);
  short DoProcess();

};



#endif
