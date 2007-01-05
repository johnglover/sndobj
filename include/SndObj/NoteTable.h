// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _NOTETABLE_H
#define _NOTETABLE_H

#include "Table.h"

class NoteTable : public Table {

 protected:

  short m_lowernote;
  short m_uppernote;
  float m_lowerfreq;
  float m_upperfreq;

 public:

  void
    SetFreqInterval(float lowerfreq, float upperfreq);
  void
    SetNoteInterval(short lowernote, short uppernote);

  NoteTable();
  NoteTable(short lowernote, short uppernote, 
	    float lowerfreq, float upperfreq);
  ~NoteTable();

  short MakeTable();
  char* ErrorMessage();

};



#endif

