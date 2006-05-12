///////////////////////////////////////////////////////
// ladspa_example.cpp: 
//       this is an example of a 
//       LADSPA plugin using SndObj classes
//       that makes use of a LADSPAplug object
//       This models a LADSPA plugin, 
//       which takes one SndObj as its main 
//       processing object.
//       In this case, a StringFlt object is
//       used (I'm found of that sound!)
//
//       VL, 2004


#include <string.h>
#include "Ladspaplug.h"

static LADSPA_Descriptor* plug_descriptor = NULL;

LADSPA_Handle 
Instantiate(const LADSPA_Descriptor *Descriptor,
                               unsigned long  SampleRate)
{
   // default SndObj vector size
   int vecsize = DEF_VECSIZE;

   // this is the processing object
   // it is allocated here, but the plugin object will
   // destroy it when it's all over
   StringFlt *procobj = new StringFlt(129.f, 0.99f, 0,0,vecsize,SampleRate);
   
   // 2 controls
   int controls  = 2;
   
   // control messages 
   char** messages = new char*[2];
   messages[0] = strdup("frequency");
   messages[1] = strdup("feedback gain");

   //  this is the plugin object
   LADSPAplug *plugin = new LADSPAplug(procobj, controls, messages, vecsize, SampleRate);
   
   //  return the plugin instance
   return (LADSPA_Handle) plugin;
}


void
CleanUp(LADSPA_Handle handle){
     
	// destroy the plugin
  delete (LADSPAplug *)handle;

}

void ConnectPort(LADSPA_Handle Instance,
                 unsigned long Port,
                 LADSPA_Data * DataLocation){
  
   LADSPAplug *plugin = (LADSPAplug *)Instance;
  
	switch(Port){

    case 0: // input port
	plugin->ConnectInput(DataLocation); break;
    case 1: // output port
	plugin->ConnectOutput(DataLocation); break;
	// we have set up some controls, so we'll 
	// connect them 
    case 2: // frequency
    plugin->ConnectControl(DataLocation, 0); break;
    case 3: // feedback gain
    plugin->ConnectControl(DataLocation, 1); break;
	}
 
}

void 
Run(LADSPA_Handle handle, unsigned long blocksize){

   // LADSPAplug::Process() is the plugin "run" method
   ((LADSPAplug *)handle)->Process(blocksize);

}

   // this is the standard plugin library entry point.
const LADSPA_Descriptor* 
ladspa_descriptor(unsigned long index)
{
  if(index != 0) return NULL;
  if(plug_descriptor != NULL) return plug_descriptor;
 
  plug_descriptor =  new LADSPA_Descriptor;
  if(plug_descriptor == NULL) return NULL;
 
  // We'll initialise the descriptor 
  // see ladspa.h for a description of the struct fields
  plug_descriptor->Maker = strdup("Victor Lazzarini");
  plug_descriptor->Name = strdup("SndObj plugin example");
  plug_descriptor->Label = strdup("SndObj_plugin");
  plug_descriptor->UniqueID = 180969; 
  plug_descriptor->Copyright = strdup("Victor Lazzarini, 2004");
  plug_descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
  plug_descriptor->PortCount = 4;

  plug_descriptor->instantiate = Instantiate;
  plug_descriptor->connect_port = ConnectPort;
  plug_descriptor->activate = NULL;
  plug_descriptor->run = Run;
  plug_descriptor->run_adding = NULL;
  plug_descriptor->set_run_adding_gain = NULL;
  plug_descriptor->deactivate = NULL;
  plug_descriptor->cleanup = CleanUp;

  LADSPA_PortDescriptor 
  *PortDescriptors = new LADSPA_PortDescriptor[plug_descriptor->PortCount];
  char **PortNames = new char*[plug_descriptor->PortCount];
  LADSPA_PortRangeHint
  *PortRangeHints = new LADSPA_PortRangeHint[plug_descriptor->PortCount]; 

  PortNames[0] = strdup("input");
  PortDescriptors[0] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
  PortNames[1] = strdup("output");
  PortDescriptors[1] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
  PortNames[2] = strdup("frequency(Hz)");
  PortDescriptors[2] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
  PortNames[3] = strdup("feedback(0-1)");
  PortDescriptors[3] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;


  PortRangeHints[2].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW |
                                     LADSPA_HINT_BOUNDED_ABOVE |
                                       LADSPA_HINT_LOGARITHMIC |
                                           LADSPA_HINT_INTEGER | 
                                        LADSPA_HINT_DEFAULT_440;
  PortRangeHints[2].LowerBound = 22.5f;
  PortRangeHints[2].UpperBound = 3520.f;

  PortRangeHints[3].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW |
                                     LADSPA_HINT_BOUNDED_ABOVE |
                                     LADSPA_HINT_DEFAULT_MIDDLE;
  PortRangeHints[3].LowerBound = 0.9f;
  PortRangeHints[3].UpperBound = 0.9999f;
  

  plug_descriptor->PortRangeHints = (const LADSPA_PortRangeHint *) PortRangeHints;
  plug_descriptor->PortNames = (const char **)PortNames;
  plug_descriptor->PortDescriptors =  
    (const LADSPA_PortDescriptor *)PortDescriptors;

  return plug_descriptor;
}

// this is the descriptor clean-up function
// called when we are done with the plugin
void _fini()
{
  if (plug_descriptor != NULL)
    {
      delete[] plug_descriptor->PortNames;
      delete[] plug_descriptor->PortDescriptors;
      delete[] plug_descriptor->PortRangeHints; 
      delete[] plug_descriptor->Label;
      delete[] plug_descriptor->Name;
      delete[] plug_descriptor->Copyright;
      delete[] plug_descriptor->Maker;
      delete plug_descriptor;
      plug_descriptor = NULL;
    }
}
