// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

//************************************************************//
//  TrisegTable.h: interface of the TrisegTable class         //
//              (three- segment function table).              //
//                                                            //
//                                                            //
//************************************************************//

#ifndef _TRISEGTABLE_H
#define _TRISEGTABLE_H

#include "Table.h"

class TrisegTable : public Table {

      protected:

      float m_initial; // points to be drawn
      float m_point1;
      float m_point2;
      float m_fin;

      float m_seg1;   // segment durations 
      float m_seg2;
      float m_seg3;

      float m_typec;       // type of curve (LOG OR LINEAR)

      public:

  void SetCurve(float init, float seg1, 
            float p1, float seg2, float p2,
            float seg3, float fin, float type = 0.f);
  void SetCurve(float* TSPoints, float type = 0.f);     
  char* ErrorMessage();
  short MakeTable();
  TrisegTable();
  TrisegTable(long L, float init, float seg1, 
            float p1, float seg2, float p2,
            float seg3, float fin, float type = 0.f);
  TrisegTable(long L, float* TSPoints, float type = 0.f);

  ~TrisegTable();

        };

#endif
