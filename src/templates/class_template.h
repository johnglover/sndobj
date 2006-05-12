
#ifndef _MYCLASS_H
#define _MY_CLASS_H
#include "SndObj.h"


class MyClass: public SndObj {


   protected:

   // Place your variable declarations here
   // as well as any internal-operation methods


   public:

   // constructors / destructor
   MyClass();
   MyClass(SndObj* input,/* place any other construction
						parameters here */
		    int vecisize=DEF_VECSIZE, float sr=DEF_SR);

   ~MyClass();
   
   // you need to re-define at least these 
   short DoProcess();
   char* ErrorMessage();

};
	
#endif

