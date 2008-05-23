 
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
// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//***********************************************************//
//  Pitch.cpp: Implementation of the Pitch Object           //
//                                                           //
//                                                           //
//                                                           //
//***********************************************************//

#include "Pitch.h"
#include <stdio.h>

//////////CONSTRUCTION /////////////////////

Pitch::Pitch(){

  m_pointer1 = (float) m_rpointer;
  m_pointer3 = (float) m_rpointer+(m_size/2);
  m_pitch = 1;
  m_incr = 0; 

  sintab = 0;

  AddMsg("multiplier", 21);
  AddMsg("semitones", 22);

}

Pitch::Pitch(float delaytime, SndObj* InObj, float pitch, int vecsize, float sr)
  : DelayLine(delaytime, InObj, vecsize, sr)
{

  m_pointer1 = (float) m_rpointer;
  m_pointer3 = (float) m_rpointer+(m_size/2);
  m_pitch = pitch;
  m_incr = 0;
  sintab = new float[m_size/2+1];
  for(int i = 0; i <= m_size/2; i++) sintab[i] = sin(i*PI/m_size);
  AddMsg("multiplier", 31);
  AddMsg("semitones", 32);

}

Pitch::Pitch(float delaytime, SndObj* InObj, int semitones, int vecsize, float sr)
  : DelayLine(delaytime, InObj, vecsize, sr)
{
  sintab = new float[m_size/2+1];
  for(int i = 0; i <= m_size/2; i++) sintab[i] = sin(i*PI/m_size);
  m_pointer1 = (float) m_rpointer;
  m_pointer3 = (float) m_rpointer+(m_size/2);
  m_pitch = (float) pow(2., semitones/12.);
  m_incr = 0;

  AddMsg("multiplier", 31);
  AddMsg("semitones", 32);

}

Pitch::~Pitch()
{
  delete[] sintab;
}


////////////////////OPERATIONS////////////////////
int
Pitch::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 31:
    SetPitch(value);
    return 1;

  case 32:
    SetPitch((int) value);
    return 1;

  default:
    return DelayLine::Set(mess,value);
     
  }


}



short
Pitch::DoProcess(){
     
  if(!m_error){	
    if(m_input){   
      float s1, s3;
      float absdiff;
      int halfsize;

      for(m_vecpos=0; m_vecpos<m_vecsize;m_vecpos++){	 
	if(m_enable){
	  halfsize = m_size/2;
	  absdiff = (float) Ftoi(m_pointer1 - m_wpointer);
	  absdiff = absdiff > 0 ? absdiff : -absdiff;
	
	  if(absdiff > halfsize){
	    if(m_pointer1 > m_wpointer) absdiff = m_wpointer+m_size - m_pointer1;
	    else absdiff = m_pointer1+m_size - m_wpointer;
	  }
	  absdiff = sintab ?  sintab[Ftoi(absdiff)] : sin(PI*absdiff/m_size);

	  s1 = GetSample(m_pointer1); 
	  s3 = GetSample(m_pointer3);

	  PutSample(m_input->Output(m_vecpos));
	  m_output[m_vecpos] =  absdiff*s1+ (1.f - absdiff)*s3;
	
	  m_incr += m_pitch;

	  while(m_incr >= m_size) m_incr -= m_size;
	  m_pointer1 = m_incr;
	  m_pointer3 = m_pointer1+m_size/2;
	  while(m_pointer3 >= m_size) m_pointer3 -= m_size;
	}
	else m_output[m_vecpos] = 0.f;
      }
      return 1;
    }
    else{        
      m_error = 11;
      return 0;
    }
  }
  else return 0;
}
