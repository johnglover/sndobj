// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#ifndef _IFADD_H
#define _IFADD_H

#include "ReSyn.h"
#include "IFGram.h"

class IFAdd : public ReSyn {

 protected:

 

 public:

 IFAdd();
 IFAdd(IFGram* input, int bins, Table* table, float pitch=1.f, float scale=1.f,
        float tscal=1.f, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
 ~IFAdd();
 short DoProcess();


};

#endif
