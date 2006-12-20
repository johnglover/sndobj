// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

// LoPassTable.h: interface for the LoPassTable class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _LOPASSTABLE_H
#define _LOPASSTABLE_H



#include "Table.h"


class LoPassTable : public Table  
{	
protected:

	float m_fr;
	float m_sr;
public:
	char* ErrorMessage();
	short MakeTable();
        
        void SetFreq(float fr) { m_fr=fr ; }
        void SetSr(float sr) { m_sr =sr; }
        
	LoPassTable(int impulsesize, float fr, float sr=44100);
	LoPassTable();
	virtual ~LoPassTable();

};

#endif 
