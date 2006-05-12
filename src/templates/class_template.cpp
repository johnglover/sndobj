//////////////////////////////////////////////////
// SndObj-derived class template      
// VL, 2001
//
//////////////////////////////////////////////////

#include "MyClass.h"

MyClass::MyClass(){
     
	// Default constructor
	// initialise your member variables
	// here to the default values
        // perform any other necessary
	// initialisation (i.e. memory allocation,
	// etc.)



	// use m_error to set values for ErrorMessage();
	// if needed
}

MyClass::MyClass(SndObj* input, /* include here
					   any extra parameters
					   needed */
					   int vecsize, float sr):
SndObj(input, vecsize, sr){

	// initialise your member variables here
        // and perform any other necessary
	// initialisation (i.e. memory allocation,
	// etc.)
	


    // use m_error to set values for ErrorMessage();
    // if needed
}

MyClass::~MyClass(){

   // perform any necessary de-allocation etc
   // here

}

short
MyClass::DoProcess(){

if(!m_error){
 if(m_input){
	 for(m_vecpos = 0; m_vecpos < m_vecsize; m_vecpos++) {
		if(m_enable) {
        
		// implement your processing algorithm here 

		// to obtain an input signal use:
	        // m_input->Output(m_vecpos);
	
		// place the resulting samples in m_ouput as in:
		// m_output[m_vecpos] = processing_result;

		// e.g. m_output[m_vecpos] = m_input->Output(m_vecpos);
		// copies the input into the output
			
		}
     else m_output[m_vecpos] = 0.f;
	 } 
 return 1;
 } else {
	m_error = 3;
	return 0;
 }
}
else return 0;
}

char*
MyClass::ErrorMessage(){
 
  char* message;
   
  switch(m_error){

  // handle your error codes here 

  default:
  message = SndObj::ErrorMessage();
  break;
  
  }

 return message;

}
