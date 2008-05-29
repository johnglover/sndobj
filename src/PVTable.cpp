 
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

#include "PVTable.h"

PVTable::PVTable(){
  m_L = 1024;
  m_file = 0;
  m_sr = 44100.f;
  m_start = m_end = 0;
  m_in = 0;
  m_analysis = 0;
  m_table = new float[m_L+1];
  m_amps =  new double[m_L];
  m_freqs = new double[m_L];
	
  MakeTable();
}


PVTable::PVTable(int L, SndFIO* soundfile, Table* window, 
		 float start, float end){
  m_L = L;
  m_file = soundfile;
  m_vecsize = m_file->GetVectorSize();
  m_sr = m_file->GetSr();
  m_end = (unsigned long)(end*m_sr/m_vecsize);
  m_start = start;
  m_file->SetPos(m_start);
  m_in = new SndIn(m_file, 1, m_vecsize, m_sr);
  m_analysis = new PVA(window, m_in, 1.f, m_L, m_vecsize, m_sr);
  m_framecount = 0;
	
  m_amps =  new double[m_L/2];
  m_freqs = new double[m_L/2];
  m_table = new float[m_L+1];
	
  MakeTable();
	
}

PVTable::~PVTable(){
	
  delete m_in;
  delete m_analysis;
  delete[] m_table;
  delete[] m_amps;
  delete[] m_freqs;
	
}

void
PVTable::SetTable(SndFIO* soundfile, Table* window, 
		  float start, float end){
	
  m_file = soundfile;
  m_vecsize = m_file->GetVectorSize();
  m_sr = m_file->GetSr();
  m_end = (unsigned long) (end*m_sr/m_vecsize);
  m_start = start;
  m_file->SetPos(m_start);
  m_in = new SndIn(m_file, 1, m_vecsize, m_sr);
  m_analysis = new PVA(window, m_in, 1.f, m_L, m_vecsize, m_sr);
  m_framecount = 0;
	
  MakeTable();
	
}

short
PVTable::MakeTable() {
	
  int i,j;
  if(m_file) {
		
    float freq, amp;
    for(i=0; i < (int) m_end && !m_file->Eof(); i++){
      // analysis
      m_file->Read();
      m_in->DoProcess();
      m_analysis->DoProcess();
      m_framecount++;
			
      for(i=0, j=0;i<m_L; i+=2, j++){
	amp = m_analysis->Output(i);
	freq = m_analysis->Output(i+1);
	m_amps[j] += amp;
	m_freqs[j] += (freq >= 0  ? freq : -freq);
      }
    }
    for(i=0, j=0;i<m_L; i+=2, j++){
      m_table[i] = m_amps[j]/m_framecount;
      m_table[i+1]= m_freqs[j]/m_framecount;
    }
  }
  else for(i=0; i < m_L; i++) m_table[i] = 0.f; 

  m_framecount = 0;
  return 1;
}

char*
PVTable::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
    message = "No error.";
    break; 

  default:
    message = "Undefined error";
    break;
  }

  return message;

}
