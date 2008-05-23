 
////////////////////////////////////////////////////////////////////////
// This file is part of the SndObj library
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
//
#include <math.h>
#include "Ptrack.h"

#define MINFREQINBINS 5    
#define MAXHIST 3                   
#define MAXWINSIZ 8192
#define MINWINSIZ 128
#define DEFAULTWINSIZ 1024
#define MAXPEAKNOS 100            
#define DEFAULTPEAKNOS 20             
#define MINBW 0.03f                  
#define BINPEROCT 48                    
#define BPEROOVERLOG2 69.24936196f    
#define FACTORTOBINS (4/0.0145453)      
#define BINGUARD 10                     
#define PARTIALDEVIANCE (0.023)          
#define DBSCAL 3.333       
#define DBOFFSET (-92.3)
#define MINBIN 3
#define MINAMPS 40
#define MAXAMPS 50
#define THRSH (10.)   

static float partialonset[] =
  {
    0,
    48,
    76.0782000346154967102,
    96,
    111.45254855459339269887,
    124.07820003461549671089,
    134.75303625876499715823,
    144,
    152.15640006923099342109,
    159.45254855459339269887,
    166.05271769459026829915,
    172.07820003461549671088,
    177.62110647077242370064,
    182.75303625876499715892,
    187.53074858920888940907,
    192,
  };

#define NPARTIALONSET ((int)(sizeof(partialonset)/sizeof(float)))


#define COEF1 ((float)(.5 * 1.227054))
#define COEF2 ((float)(.5 * -0.302385))
#define COEF3 ((float)(.5 * 0.095326))
#define COEF4 ((float)(.5 * -0.022748))
#define COEF5 ((float)(.5 * 0.002533))
#define FLTLEN 5
#define OK 1

extern "C" {
void ComplexFFT(float *s, int N);
}

void Ptrack::pitchtrack()
{
  Histopeak histpeak;
  int i, j, k, n = 2*hop, npeak, logn = -1, count, tmp;
  float totalpower, totalloudness, totaldb;
  float maxbin,  *histogram = spectmp + BINGUARD;
  float hzperbin = m_sr / (2.0f * n);
  int indx, halfhop = hop>>1;
  float best;
  float cumpow = 0, cumstrength = 0, freqnum = 0, freqden = 0;
  int npartials = 0,  nbelow8 = 0;
  float putfreq;
   
  count = histcnt + 1;
  if (count == NPREV) count = 0;
  histcnt = count;

  tmp = n;
  while(tmp){
    tmp >>= 1;
    logn++;
  }
  maxbin = BINPEROCT * (logn-2);

  for (i = 0, k = 0; i < hop; i++, k += 2){
    spec[k] = sig[i] * sinus[k];
    spec[k+1] = sig[i] * sinus[k+1];
  }

  ComplexFFT(spec, hop);

  for (i = 0, k = 2*FLTLEN; i < hop; i+=2, k += 4){
    spectmp[k] = spec[i];
    spectmp[k+1] = spec[i+1];
  }
  for (i = n - 2, k = 2*FLTLEN+2; i >= 0; i-=2, k += 4){
    spectmp[k] = spec[i]; 
    spectmp[k+1] = -spec[i+1];
  }
  for (i = (2*FLTLEN), k = (2*FLTLEN-2);i<FLTLEN*2; i+=2, k-=2){
    spectmp[k] = spectmp[i];  
    spectmp[k+1] = -spectmp[i+1];
  }
  for (i = (2*FLTLEN+n-2), k =(2*FLTLEN+n); i>=0; i-=2, k+=2){
    spectmp[k] = spectmp[i];
    spectmp[k+1] = -spectmp[k+1];
  }

  for (i = j = 0, k = 2*FLTLEN; i < halfhop; i++, j+=8, k+=2)
    {
      float re,  im;

      re= COEF1 * ( prev[k-2] - prev[k+1]  + spectmp[k-2] - prev[k+1]) +
	COEF2 * ( prev[k-3] - prev[k+2]  + spectmp[k-3]  - spectmp[ 2]) +
	COEF3 * (-prev[k-6] +prev[k+5]  -spectmp[k-6] +spectmp[k+5]) +
	COEF4 * (-prev[k-7] +prev[k+6]  -spectmp[k-7] +spectmp[k+6]) +
	COEF5 * ( prev[k-10] -prev[k+9]  +spectmp[k-10] -spectmp[k+9]);

      im= COEF1 * ( prev[k-1] +prev[k]  +spectmp[k-1] +spectmp[k]) +
	COEF2 * (-prev[k-4] -prev[k+3]  -spectmp[k-4] -spectmp[k+3]) +
	COEF3 * (-prev[k-5] -prev[k+4]  -spectmp[k-5] -spectmp[k+4]) +
	COEF4 * ( prev[k-8] +prev[k+7]  +spectmp[k-8] +spectmp[k+7]) +
	COEF5 * ( prev[k-9] +prev[k+8]  +spectmp[k-9] +spectmp[k+8]);

      spec[j] = 0.7071f * (re + im);
      spec[j+1] = 0.7071f * (im - re);
      spec[j+4] = prev[k] + spectmp[k+1];
      spec[j+5] = prev[k+1] - spectmp[k];
       
      j += 8; 
      k += 2;
      re= COEF1 * ( prev[k-2] -prev[k+1]  -spectmp[k-2] +spectmp[k+1]) +
	COEF2 * ( prev[k-3] -prev[k+2]  -spectmp[k-3] +spectmp[k+2]) +
	COEF3 * (-prev[k-6] +prev[k+5]  +spectmp[k-6] -spectmp[k+5]) +
	COEF4 * (-prev[k-7] +prev[k+6]  +spectmp[k-7] -spectmp[k+6]) +
	COEF5 * ( prev[k-10] -prev[k+9]  -spectmp[k-10] +spectmp[k+9]);

      im= COEF1 * ( prev[k-1] +prev[k]  -spectmp[k-1] -spectmp[k]) +
	COEF2 * (-prev[k-4] -prev[k+3]  +spectmp[k-4] +spectmp[k+3]) +
	COEF3 * (-prev[k-5] -prev[k+4]  +spectmp[k-5] +spectmp[k+4]) +
	COEF4 * ( prev[k-8] +prev[k+7]  -spectmp[k-8] -spectmp[k+7]) +
	COEF5 * ( prev[k-9] +prev[k+8]  -spectmp[k-9] -spectmp[k+8]);

      spec[j] = 0.7071f * (re + im);
      spec[j+1] = 0.7071f * (im - re);
      spec[j+4] = prev[k] - spectmp[k+1];
      spec[j+5] = prev[k+1] + spectmp[k];
        
    }
    

  for (i = 0; i < n + 4*FLTLEN; i++) prev[i] = spectmp[i];

  for (i = 0; i < MINBIN; i++) spec[4*i + 2] = spec[4*i + 3] = 0;
  
  for (i = 4*MINBIN, totalpower = 0; i < (n-2)*4; i += 4)
    {
      float re = spec[i] - 0.5f * (spec[i-8] + spec[i+8]);
      float im = spec[i+1] - 0.5f * (spec[i-7] + spec[i+9]);
      spec[i+3] = (totalpower += (spec[i+2] = re * re + im * im));
    }
 
  if (totalpower > 1e-9f)
    {
      totaldb = DBSCAL  * log(totalpower/n);
      totalloudness = sqrt(sqrt(totalpower));
      if (totaldb < 0) totaldb = 0;
    }
  else totaldb = totalloudness = 0;
  
  dbs[count] = totaldb + DBOFFSET;

  if (totaldb >= amplo) {

    npeak = 0;
  
    for (i = 4*MINBIN;i < (4*(n-2)) && npeak < numpks; i+=4)
      {
        float height = spec[i+2], h1 = spec[i-2], h2 = spec[i+6];
        float totalfreq, peakfr, tmpfr1, tmpfr2, m, var, stdev;
        
        if (height < h1 || height < h2 ||
            h1 < 0.00001f*totalpower || 
            h2 < 0.00001f*totalpower) continue;

        peakfr= ((spec[i-8] - spec[i+8]) * (2.0f * spec[i] - spec[i+8] - spec[i-8]) +
		 (spec[i-7] - spec[i+9]) * (2.0f * spec[i+1] - spec[i+9] - spec[i-7])) /
	  (2.0f * height);
        tmpfr1=    ((spec[i-12] - spec[i+4]) * (2.0f * spec[i-4] - spec[i+4] - spec[i-12]) +
		    (spec[i-11] - spec[i+5]) * (2.0f * spec[i-3] - spec[i+5] - spec[i-11])) /
	  (2.0f * h1) - 1;
        tmpfr2=    ((spec[i-4] - spec[i+12]) * (2.0f * spec[i+4] - spec[i+12] - spec[i-4]) +
		    (spec[i-3] - spec[i+13]) * (2.0f * spec[i+5] - spec[i+13] - spec[i-3])) /
	  (2.0f * h2) + 1;


        m = 0.333333f * (peakfr + tmpfr1 + tmpfr2);
        var = 0.5f * ((peakfr-m)*(peakfr-m) + (tmpfr1-m)*(tmpfr1-m) + (tmpfr2-m)*(tmpfr2-m));

        totalfreq = (i>>2) + m;
        if (var * totalpower > THRSH * height 
	    || var < 1e-30) continue;
	  
        stdev = sqrt(var);
        if (totalfreq < 4) totalfreq = 4;
        	 
      
        peakarray[npeak].pwidth = stdev;
        peakarray[npeak].ppow = height;
        peakarray[npeak].ploudness = sqrt(sqrt(height));
        peakarray[npeak].pfreq = totalfreq;
        npeak++;
       
      }
    
    if (npeak > numpks) npeak = numpks; 
    for (i = 0; i < maxbin; i++) histogram[i] = 0;
    for (i = 0; i < npeak; i++)
      {
        float pit = BPEROOVERLOG2 * log(peakarray[i].pfreq) - 96.0f;
        float binbandwidth = FACTORTOBINS * peakarray[i].pwidth/peakarray[i].pfreq;
        float putbandwidth = (binbandwidth < 2 ? 2 : binbandwidth);
        float weightbandwidth = (binbandwidth < 1.0f ? 1.0f : binbandwidth);
        float weightamp = 4. * peakarray[i].ploudness / totalloudness;
        for (j = 0; j < NPARTIALONSET; j++)
	  {
            float bin = pit - partialonset[j];
            if (bin < maxbin)
	      {
                float para, pphase, score = 30.0f * weightamp /
		  ((j+npartial) * weightbandwidth);
                int firstbin = (int) (bin + 0.5f - 0.5f * putbandwidth);
                int lastbin = (int) (bin + 0.5f + 0.5f * putbandwidth);
                int ibw = lastbin - firstbin;
                if (firstbin < -BINGUARD) break;
                para = 1.0f / (putbandwidth * putbandwidth);
                for (k = 0, pphase = firstbin-bin; k <= ibw;
		     k++,pphase += 1.0f)
		  histogram[k+firstbin] += score * (1.0f - para * pphase * pphase);
                   
	      }
	  }
      }


    for (best = 0, indx = -1, j=0; j < maxbin; j++)
      if (histogram[j] > best)
	indx = j,  best = histogram[j];
	   
    histpeak.hvalue = best;
    histpeak.hindex = indx;
       
    putfreq = exp((1.0f / BPEROOVERLOG2) *
		  (histpeak.hindex + 96.0f));
    for (j = 0; j < npeak; j++)
      {
	float fpnum = peakarray[j].pfreq/putfreq;
	int pnum = (int)(fpnum + 0.5f);
	float fipnum = pnum;
	float deviation;
	if (pnum > 16 || pnum < 1) continue;
	deviation = 1.0f - fpnum/fipnum;
	if (deviation > -PARTIALDEVIANCE && deviation < PARTIALDEVIANCE)
	  {
	    float stdev, weight;
	    npartials++;
	    if (pnum < 8) nbelow8++;
	    cumpow += peakarray[j].ppow;
	    cumstrength += sqrt(sqrt(peakarray[j].ppow));
	    stdev = (peakarray[j].pwidth > MINBW ?
		     peakarray[j].pwidth : MINBW);
	    weight = 1.0f / ((stdev*fipnum) * (stdev*fipnum));
	    freqden += weight;
	    freqnum += weight * peakarray[j].pfreq/fipnum;          

	  }

      }
    if ((nbelow8 < 4 || npartials < 7) && cumpow < 0.01f * totalpower)
      histpeak.hvalue = 0;
    else
      {
	float pitchpow = (cumstrength * cumstrength) *
	  (cumstrength * cumstrength);
	float freqinbins = freqnum/freqden;
	if (freqinbins < MINFREQINBINS)
	  histpeak.hvalue = 0;
	else
	  {
	    cps = histpeak.hpitch = hzperbin * freqnum/freqden;
	    histpeak.hloud = (DBSCAL) * log(pitchpow/n);
	  }
      }

  }

}

void Ptrack::SetPeaks(int peak) {
  if(peak == 0 || peak > MAXPEAKNOS)
    numpks = DEFAULTPEAKNOS;
  else
    numpks = peak;
  peakarray = new Peak[(numpks+1)];
}

void
Ptrack::SetHopsize(int siz){
  int i, winsize = siz*2, powtwo, tmp;
  float *tmpb;

  if (winsize < MINWINSIZ || winsize > MAXWINSIZ)
    winsize = DEFAULTWINSIZ;
    
  tmp = winsize;
  powtwo = -1;
   
  while (tmp){   
    tmp >>= 1;
    powtwo++;
  }

  if (winsize != (1 << powtwo))
    winsize = (1 << powtwo);

  hop = siz;
  sig = new float[hop];
  prev = new float[(hop*2 + 4*FLTLEN)];
  sinus = new float[(hop*2)];
  spectmp = new float[(winsize*4 + 4*FLTLEN)];
  spec = new float[(winsize*4)];
    
  for (i = 0, tmpb = sig; i < hop; i++)
    tmpb[i] = 0;
  for (i = 0, tmpb = prev; i < winsize + 4 * FLTLEN; i++)
    tmpb[i] = 0;
  for (i = 0, tmpb = sinus; i < hop; i++){
    tmpb[2*i] =    cos((3.14159*i)/(winsize));
    tmpb[2*i+1] = -sin((3.14159*i)/(winsize));
  }

}

Ptrack::Ptrack(){

  cnt = 0;
  histcnt = 0; 
  pitch = new SndObj(0, 1, m_sr);
  amp  = new SndObj(0, 1, m_sr);
  for (int i = 0; i < NPREV; i++) dbs[i] = 0;
  amplo = MINAMPS;
  amphi = MAXAMPS;
  npartial = 7;

}
Ptrack::Ptrack(SndObj  *in, int siz, int peak, float scale, int vecsize, float sr):
  SndObj(in, vecsize, sr)
{
  SetHopsize(siz);
  SetPeaks(peak);
  pitch = new SndObj(0, 1, m_sr);
  amp  = new SndObj(0, 1, m_sr);
  m_scale = scale;
  cnt = 0;
  histcnt = 0; 
  for (int i = 0; i < NPREV; i++) dbs[i] = 0;
  amplo = MINAMPS;
  amphi = MAXAMPS;
  npartial = 7;
    
}


Ptrack::~Ptrack(){
  delete[] sig;
  delete[] prev;
  delete[] spec;
  delete[] spectmp;
  delete[] sinus;
  delete[] peakarray;
  delete pitch;
  delete amp;
}

short Ptrack::DoProcess(){
 
  for(int i=0;i<m_vecsize;m_vecpos++, cnt++){
    if(cnt == hop){
      pitchtrack();
      cnt = 0;
      *pitch << cps;
      *amp << dbs[histcnt];  
    }
    sig[i] = m_input->Output(i)*m_scale;
  }
  return 1;
}

