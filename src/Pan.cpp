 
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

#include "Pan.h"
//////////////// CONSTRUCTION / DESTRUCTION ////////////////////

Pan::Pan(){

  m_pan = 0.f;
  m_channel = new SndObj[2];
  m_inputpan = 0;
  left = &m_channel[0];
  right = &m_channel[1];
  m_channel[0].SetInput(this);
  m_channel[1].SetInput(this);
  m_inputpan = 0;
  m_res = 512;
  m_panpos = new float[m_res*2];
  float pan;
  for(int i = 0; i < m_res*2; i++){
    pan = ((float)i/m_res) - 1; 
    m_panpos[i] = (float)(squrt2o2*(1-pan)/sqrt(1+(pan*pan)));
  }
  AddMsg("pan position", 21);
}

Pan::Pan(float pan, SndObj* InObj, SndObj* InPan, int res, int vecsize, float sr):
  SndObj(InObj, vecsize, sr){
  
  m_pan = pan;
  m_inputpan = InPan;
  m_channel = new SndObj[2];

  if(vecsize != DEF_VECSIZE){
    m_channel[0].SetVectorSize(vecsize);
    m_channel[1].SetVectorSize(vecsize);
  }


  m_channel[0].SetInput(this);
  m_channel[1].SetInput(this);
  left = &m_channel[0];
  right = &m_channel[1];
  m_res = res/2;
  m_panpos = new float[res];
  float panval;
  for(int i = 0; i < res; i++){
    panval = ((float)i/m_res) - 1; 
    m_panpos[i] = (float)(squrt2o2*(1-panval)/sqrt(1+(panval*panval)));
  }
  AddMsg("pan position", 21);
}

Pan::~Pan(){
  delete[] m_channel;
}

////////////////// OPERATIONS ///////////////////////////////
float  Pan::Panning(float pan, int chan){

  if(pan >= -1 && pan <= 1){
    if(!chan) return m_panpos[Ftoi(m_res*(1+pan))];
    else return m_panpos[Ftoi(m_res*(1-pan))];
  }
  else {
    if (pan < -1) { 
      if(!chan) return m_panpos[0]; 
      else  return 0.f;
    }
    else {
      if(!chan) return 0.f;
      else return m_panpos[0];

    } 
  }

}

int
Pan::Set(char* mess, float value){

  switch(FindMsg(mess)){

  case 21:
    SetPan(value);
    return 1;

  default:
    return SndObj::Set(mess, value);

  }

}

int
Pan::Connect(char* mess, void* input){

  switch(FindMsg(mess)){

  case 21:
    m_inputpan = (SndObj *) input;
    return 1;

  default:
    return SndObj::Connect(mess, input);

  }

}

short
Pan::DoProcess()
{

  if(!m_error){
    if(m_input){
      float pan;
      for(int i=0; i < 2; i++){
	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
	  if(m_enable) {
	    pan = m_pan + (m_inputpan ==  0 ? 0 : m_inputpan->Output(m_vecpos));
	    m_output[m_vecpos] = m_input->Output(m_vecpos)*Panning(pan,i);
	  }
	  else m_output[m_vecpos] = 0.f;
	}
	m_channel[i].DoProcess();
      }
      return 1;
    }
    else {
      m_error=11;
      return 0;
    }
  }
  else return 0;
}
	     
   
char*
Pan::ErrorMessage(){

  char *message;
	
  switch(m_error){

  case 11:
    message = "DoProcess() failed, no input object\n";	
    break;

  default :
    message =  SndObj::ErrorMessage();
    break;
  }

  return message;

}

