// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include "NoteTable.h"


NoteTable::NoteTable(){

m_L = 127;
m_lowernote = 69;
m_uppernote = 81;
m_upperfreq = 880.f;
m_lowerfreq = 440.f;

m_table = new float[m_L+1];
MakeTable();

}

NoteTable::NoteTable(short lowernote, short uppernote, 
float lowerfreq, float upperfreq){

m_L = 127;
m_lowernote = lowernote;
m_uppernote = uppernote;
m_lowerfreq = lowerfreq;
m_upperfreq = upperfreq;

m_table = new float[m_L+1];
MakeTable();

}

NoteTable::~NoteTable(){

delete[] m_table;

}


void
NoteTable::SetFreqInterval(float lowerfreq, float upperfreq){
 m_lowerfreq = lowerfreq;
 m_upperfreq = upperfreq;
}

void
NoteTable::SetNoteInterval(short lowernote, short uppernote){
m_lowernote = lowernote;
m_uppernote = uppernote;
}



short
NoteTable::MakeTable(){

for(int i=0; i<127; i++)
m_table[i] = (float)( m_lowerfreq + (m_upperfreq - m_lowerfreq) * 
           (pow(2., (i - (double)m_lowernote)/(m_uppernote - m_lowernote)) - 1.));


return 1;
}

char*
NoteTable::ErrorMessage(){
  
  char* message;
   
  switch(m_error){

  case 0:
  message = "No error.";
  break; 

  case 1:
  message = "";
  break;

  default:
  message = "Undefined error";
  break;
  }

 return message;

}
