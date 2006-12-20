// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _FIR_H
#define _FIR_H

#include "DelayLine.h"
#include "Table.h"

class FIR : public DelayLine {

protected:
      Table*   m_table;
      bool     m_newtable;      

public:
	int Connect(char* mess, void* input);
	int Set(char* mess, float value);
     FIR();
	 FIR(Table* coeftable, SndObj* input, 
		  int vecsize=DEF_VECSIZE, float sr=DEF_SR);
	 FIR(float* impulse, int impulsesize, SndObj* input, 
		  int vecsize=DEF_VECSIZE, float sr=DEF_SR);
	 ~FIR();

	 void SetTable(Table* coeftable){ m_table = coeftable; m_newtable = false;
	 	SetDelayTime(m_table->GetLen()/m_sr);}
     void SetImpulse(float* impulse, int impulsesize);
	 void SetDelayTime(float dtime){
         if(m_newtable) DelayLine::SetDelayTime(dtime);
         else return;
	 }

     short DoProcess();

};

#endif
