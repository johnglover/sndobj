//////////////////////////////////////////////////////////
// LADSPAplug class: this class models a LADSPA plugin
//       and is designed to act as an interface for building
//       plugins with SndObj classes
//
//       This class supports plugins based on single SndObj objects,
//       but can be extended to support larger SndObj processing
//       chains.

#ifndef _LADSPAPLUG_H
#define _LADSPAPLUG_H

#include <SndObj/AudioDefs.h>
#include <ladspa.h>


class LADSPAplug {
 
  protected:

  // sndobjs
  SndObj *m_inobj;
  SndObj *m_procobj;

  // controls
  int			  m_controls;
  float			 *m_value;
  char			**m_message;
  LADSPA_Data	**m_parameter;

  // data ports
  LADSPA_Data  *m_insig;
  LADSPA_Data  *m_outsig;

  // SndObj vectorsize etc...
  int	          m_sndobj_vecsize;
  float           m_sr;
  int             m_pos;

  public:

  LADSPAplug(SndObj *procobj, int controls, char **message,
  int vecsize, float sr);
  ~LADSPAplug();

  // these methods connect the audio IO ports
  void ConnectInput(LADSPA_Data *p) { m_insig = p; }
  void ConnectOutput(LADSPA_Data *p) { m_outsig = p; }

  // this method connects the control ports (if there are any)
  bool ConnectControl(LADSPA_Data *p, int control) { 
	  if((control >= 0) && (control < m_controls)){
	  m_parameter[control] = p; return true;
	  }
      else return false;
  }

  // this is the processing ("run") method
  // It is overridable, so that it can be tailored
  // to suit any arrangement of SndObjs
  virtual void Process(unsigned long bsize);
  
};


#endif
