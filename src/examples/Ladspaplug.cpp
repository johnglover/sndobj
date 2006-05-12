//////////////////////////////////////////////////
// LADSPAplug.cpp: implementation of the LADSPAplug
//                 Linux Audio Developers 
//				   Simple Plugin API
//                 Model


#include "Ladspaplug.h"
#include <string.h>

LADSPAplug::LADSPAplug(SndObj *procobj, int controls, 
			      char **message, int vecsize, float sr)
{

// initialise members
m_sndobj_vecsize = vecsize;
m_sr = sr;
m_pos = 0;

// instantiate input SndObj
m_inobj = new SndObj(0,m_sndobj_vecsize,m_sr);

// set processing object
m_procobj = procobj;
procobj->Connect("input", m_inobj);

// set controls
m_controls = controls;

// if there are any controls
if(m_controls){
m_message = new char*[m_controls];
m_value = new float[m_controls];
m_parameter = new LADSPA_Data*[m_controls];

for(int i = 0; i < m_controls; i++){
  m_message[i] = strdup(message[i]);
  m_value[i] = 0.f;
}
}

}

LADSPAplug::~LADSPAplug(){

// dispose of dynamic objects
// including the processing SndObj

delete[] m_message;
delete[] m_parameter;
delete[] m_value;
delete m_procobj;
delete m_inobj;

}


void
LADSPAplug::Process(unsigned long blocksize){

 // if the blocksize is bigger than the
 // SndObj vectorsize than we will have to
 // loop to create the output
 
 // otherwise, we will process input only when
 // the SndObj input buffer is full

 // The only requirement is that one
 // is a factor of the other. 

 // One way of guarateeing this for all cases
 // is to set sndobj_vecsize to 1, which is
 // very unefficient.

 //  However, it is reasonable to assume blocksizes
 //  to be power-of-two sizes, so we can set 
 //  sndobj_vecsize to a power-of-two (say 256,
 //  the default).
 
 int i;
 int samples = blocksize < m_sndobj_vecsize   ? 
                     blocksize : m_sndobj_vecsize;

 // set the control values
 
 for(i=0; i < m_controls;i++){

 if(m_value[i] != *m_parameter[i]) {
	 m_value[i] = *m_parameter[i];
     m_procobj->Set(m_message[i], m_value[i]);
 }

 }
 
 // process loop

 for(int i = 0; i < blocksize; i += m_sndobj_vecsize){

   // this will only loop if the input blocksize is
   // bigger than the SndObj vectorsize
   // if so, we will read along different positions of
   // the input buffer
   // otherwise, it will only execute once

     m_pos = m_inobj->PushIn(m_insig+i, samples);

   // DoProcess() will always be called if the 
   // blocksize is bigger than the SndObj vectorsize
   // otherwise it will only be called if the sndobj
   // input buffer is full

	 if(m_pos == m_sndobj_vecsize) m_procobj->DoProcess();

   // if the input blocksize is bigger than the SndObj
   // vectorsize we will write to different positions
   // along the output buffer
   // otherwise, we will write a single whole buffer

	 m_procobj->PopOut(m_outsig+i, samples);
 
 }


}


