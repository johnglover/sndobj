// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information


#include "SpecEnvTable.h"

SpecEnvTable :: SpecEnvTable() : m_pi(8 * atan(1.)){

double phi = 0.f;
double delay = (m_L-1)/2;
double re, im;

     for(int i=2, j=2; i < m_L; i+=2, j++){
     phi = -(delay*j*2*m_pi)/m_L;
     re = m_table[i]*cos(phi);
     im = m_table[i]*sin(phi);
     m_table[i] = (float)re;
	 m_table[i+1] = (float)im;
	 }
}

SpecEnvTable :: SpecEnvTable(long L, int segments, float start, 
					 float* points, float* lengths, 
					 float type, float nyquistamp) :
PVEnvTable(L,segments,start,points,lengths,type,44100.f,nyquistamp),
m_pi(8 * atan(1.)) 
{

double phi = 0.f;
double delay = (m_L-1)/2;
double re, im;

     for(int i=2, j=2; i < m_L; i+=2, j++){
     phi = -(delay*j*2*m_pi)/m_L;
     re = m_table[i]*cos(phi);
     im = m_table[i]*sin(phi);
     m_table[i] = (float)re;
	 m_table[i+1] = (float)im;
	 }
}


SpecEnvTable::~SpecEnvTable(){
                         }

short
SpecEnvTable :: MakeTable(){   
	PVEnvTable::MakeTable();

double phi = 0.f;
double delay = (m_L-1)/2;
double re, im;

     for(int i=2, j=2; i < m_L; i+=2, j++){
     phi = -(delay*j*2*m_pi)/m_L;
     re = m_table[i]*cos(phi);
     im = m_table[i]*sin(phi);
     m_table[i] = (float)re;
	 m_table[i+1] = (float)im;
	 }

return 1;
}

