// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _SINSYN_H
#define _SINSYN_H

#include "SndObj.h"
#include "SinAnal.h"
#include "Table.h"

class SinSyn : public SndObj {

 protected:

  float m_size;
  Table* m_ptable;

  float m_factor;
  float m_facsqr;
  float m_LoTWOPI;
  float m_scale;
  float m_incr;
  float m_ratio;

  int m_tracks;
  int* m_trackID;
  int m_maxtracks;
 
  float* m_phases;
  float* m_freqs;
  float* m_amps;
 
 public:

  SinSyn();
  SinSyn(SinAnal* input, int maxtracks, Table* table, float scale=1.f, 
	 int vecsize=DEF_VECSIZE, float sr=DEF_SR);

  ~SinSyn();
  void SetTable(Table* table); 
  void SetMaxTracks(int maxtracks);
  void SetScale(float scale) { m_scale = scale; }
  int Set(char* mess, float value);
  int Connect(char* mess, void* input);
  short DoProcess();


};

#endif
