// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  Unit.cpp: implementation of the Unit class.               //
//                                                            //
//                                                            //
//                                                            //
//************************************************************//

#include "Unit.h"

Unit::Unit(){
  m_amp = 1.f;
  m_mode = UNIT_SAMPLE;
  m_step = 0.f;

  AddMsg("mode", 21);
  AddMsg("step", 22);
  AddMsg("amplitude", 23);

}

Unit::Unit(float amp, short mode, float step, int vecsize, float sr):
  SndObj(0, vecsize, sr){
  m_amp = amp;
  m_step = step;
  m_mode = mode;

  AddMsg("mode", 21);
  AddMsg("step", 22);
  AddMsg("amplitude", 23);
}

Unit::~Unit(){
}

int
Unit::Set(char* mess, float value){

  switch (FindMsg(mess)){

  case 21:
    SetMode((short)value);
    return 1;

  case 23:
    SetStep(value);
    return 1;

  case 22:
    SetAmp(value);
    return 1;

  default:
    return SndObj::Set(mess,value);
     
  }


}


short 
Unit::DoProcess(){
  if(!m_error){
    for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
      if(m_enable){
	m_output[m_vecpos] = m_amp;
	if(m_mode == UNIT_SAMPLE) Disable();
	else if (m_mode == RAMP) m_amp += m_step;
      }
      else m_output[m_vecpos] = 0.f;
    }
    return 1;
  }
  else return 0;
}



