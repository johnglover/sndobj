#ifndef _PTRACK_H
#define _PTRACK_H

#include "SndObj.h"

#define NPREV 20

struct Peak         
{
  float pfreq;                   
  float pwidth;                  
  float ppow;                   
  float ploudness;                                   
};

struct Histopeak
{
  float hpitch;                  
  float hvalue;                
  float hloud;                   
  int hindex;                   
  int hused;                     
};

class Ptrack : public SndObj 
{

 protected:
                         
  float *sig, *prev, *sinus, *spec, *spectmp; 
  Peak *peakarray; 
  int numpks;                
  int cnt;                 
  int histcnt;                
  int hop;                     
  float sr;                     
  float cps;
  float dbs[NPREV];         
  float amplo;
  float amphi;
  float npartial;
  float dbfs;
  int vecsize;
  float m_scale;

  void pitchtrack();

 public:

  SndObj *pitch, *amp;

  Ptrack();
  Ptrack(SndObj *in, int siz=1024, int peak=10, float scale=1.0, 
         int vecsize=DEF_VECSIZE, float sr=DEF_SR);
  ~Ptrack();

  void SetHopsize(int siz);
  void SetPeaks(int peaks);
  void SetScale(float scale) { m_scale = scale; }

  short DoProcess();

};


#endif
