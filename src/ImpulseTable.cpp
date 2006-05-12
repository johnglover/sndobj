// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information


#include "ImpulseTable.h"

ImpulseTable :: ImpulseTable() {
m_window = 0;
m_plan = rfftw_create_plan(m_L, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE);
m_ffttmp = new float[m_L+1];
MakeTable();
}

ImpulseTable :: ImpulseTable(long L, 
							  int segments, float start, 
					 float* points, float* lengths, 
					 float type, 
					 Table* window,
					 float nyquistamp) :
SpecEnvTable(L,segments,start,points,lengths,type,nyquistamp)
{

m_window = window;
m_plan = rfftw_create_plan(m_L, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE);
m_ffttmp = new float[m_L+1];
MakeTable(); 
}


ImpulseTable::~ImpulseTable(){
	delete[] m_ffttmp;
	rfftw_destroy_plan(m_plan);
                         }

short
ImpulseTable :: MakeTable(){   
	
	SpecEnvTable::MakeTable();
int i, i2;
// get input FFT frame and
// prepare data for fftw

m_ffttmp[0] = m_table[0]; 
m_ffttmp[m_L/2] = m_table[1];
for(i=2,  i2=1; i<m_L; i+=2){
i2 = i/2;
m_ffttmp[i2] = m_table[i];
m_ffttmp[m_L-(i2)] = m_table[i+1];
}	

// Inverse FFT function
rfftw_one(m_plan, m_ffttmp, m_table);

if(m_window && (m_window->GetLen() == m_L))
     for(i=0; i<m_L; i++) 
         m_table[i] *= m_window->Lookup(i);

m_table[m_L] = m_table[m_L-1];
return 1;
}

