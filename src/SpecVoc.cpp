// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "SpecVoc.h"

SpecVoc::SpecVoc(){
}

SpecVoc::SpecVoc(SndObj *input, SndObj *input2, int vecsize, float sr)
                 :SpecPolar(input,vecsize, sr){
m_input2 = input2;
}

SpecVoc::~SpecVoc(){
}


short
SpecVoc::DoProcess(){

if(!m_error){
 if(m_input && m_input2){ 
	if(m_enable) {  
	 float a, b, c, d; 
	 for(m_vecpos = 2; m_vecpos < m_vecsize; m_vecpos+=2){
     a = m_input->Output(m_vecpos);
	 b = m_input->Output(m_vecpos+1);     
	 c = m_input2->Output(m_vecpos);
	 d = m_input2->Output(m_vecpos+1);
     convert(&a, &b);
	 convert(&c, &d);
	 m_output[m_vecpos] = a*cos(d);
	 m_output[m_vecpos+1] = a*sin(d);    
	 }
	 m_output[1] = m_input->Output(1);
	 m_output[0] = m_input->Output(0);
}
	else 
	for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos+=2)
		m_output[m_vecpos] = m_output[m_vecpos+1] = 0.f;
 
		 return 1;

 } else {
	m_error = 3;
	return 0;
 }
}
else return 0;

}
