// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//*******************************************************//
//     Lookup.cpp : implementation of the Lookup object
//                  truncated table lookup 
//
//
//*******************************************************//

#include "Lookup.h"

//////////////// CONSTRUCTION / DESTRUCTION ////////////////
Lookup::Lookup(){
m_ptable = 0;
m_size = 0;
m_offset = 0;
m_mode = 0;
m_normal = 0;
AddMsg("read mode", 21);
AddMsg("index type", 22);
AddMsg("offset", 23);
AddMsg("table", 24);

}

Lookup::Lookup(Table* table, long offset, SndObj* InObj, int mode,
			   int normal,int vecsize, float sr):
            SndObj(InObj, vecsize, sr)
              {
m_ptable = table;
m_offset = offset;
m_size = m_ptable->GetLen();
m_mode = mode;
m_normal = normal;
AddMsg("read mode", 21);
AddMsg("index type", 22);
AddMsg("offset", 23);
AddMsg("table", 24);

	      }

Lookup::~Lookup(){
}
/////////// OPERATIONS ////////////////////////////////
int
Lookup::Set(char* mess, float value){

	switch(FindMsg(mess)){

	case 21:
	SetMode((int) value, m_normal);
	return 1;

	case 22:
	SetMode(m_mode, (int) value);
	return 1;

	case 23:
	Offset((int)value);
	return 1;

	default:
	return SndObj::Set(mess, value);

	}

}


int
Lookup::Connect(char* mess, void* input){

	switch(FindMsg(mess)){

	case 24:
	m_ptable = (Table *) input;
	return 1;

	default:
	return SndObj::Connect(mess, input);

	}

}

void 
Lookup::SetTable(Table* table){
m_ptable = table;
m_size = m_ptable->GetLen();
  }

short
Lookup::DoProcess()
                 { 
if(!m_error){
 if(m_ptable && m_input){ 
  float i;
  for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++){
   if(m_enable){ 
     i = m_input->Output(m_vecpos);
	 if(m_normal) i *= m_size; // if normalised 
    // modulus
	 if(m_mode){
     while(i >= m_size)
	     i -= m_size;        
     while (i < 0)
	     i += m_size;
	 }
	 else if(i >= m_size || i > 0) 
		  i = (i >= m_size) ? m_size - 1.f : 0.f;
    // truncating lookup :
     m_output[m_vecpos] = m_ptable->GetTable()[Ftoi(i) + m_offset]; 
        
   }
  else m_output[m_vecpos] =  0.f;
  }
  return 1;
 } else {
	 m_error = 3;
	 return 0;
 }
}
else return 0;		  
}  


