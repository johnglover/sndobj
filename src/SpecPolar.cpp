// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "SpecPolar.h"

SpecPolar::SpecPolar(){
}

SpecPolar::SpecPolar(SndObj *input, int vecsize, float sr)
                 :SpecMult(input, 0, vecsize, sr){
}

SpecPolar::~SpecPolar(){
}


short
SpecPolar::DoProcess(){

if(!m_error){
 if(m_input){
	 float a, b;
	 for(m_vecpos = 1; m_vecpos < m_vecsize; m_vecpos+=2) {
		 
		// every complex pair
		 if(m_enable) {     
        // convert 
		   a = m_input->Output(m_vecpos); 	               
		   b  = m_input->Output(m_vecpos+1);
           convert(&a, &b);
           m_output[m_vecpos] = a; 
           m_output[m_vecpos+1] = b;
		}
		 else 
		m_output[m_vecpos+1] = m_output[m_vecpos] = 0.f;
	 } 
 return 1;
 } else {
	m_error = 3;
	return 0;
 }
}
else return 0;

}
