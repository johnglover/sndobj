 
////////////////////////////////////////////////////////////////////////
// This file is part of the SndObj library
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
//
////////////////////////////////////////////////
// SndJackIO.h : interface of the SndJackIO class
//           jack IO client support 
//
//

#ifndef _SNDJACKIO_H
#define _SNDJACKIO_H

#include "SndIO.h"
#include <jack/jack.h>

class SndJackIO : public SndIO {

 protected:

  float **m_inbuff;
  float **m_outbuff;
  bool  *m_inused;
  bool *m_outused;

  int m_curbuff;
  int m_outcurbuff;
  int m_incurbuff;
  int m_incount;
  int m_outcount;
  int m_buffno;
  

  jack_nframes_t  m_bufframes;
  int m_items;

  jack_client_t *m_client;  
  jack_port_t **m_inport;  // arrays of ports
  jack_port_t **m_outport; // one per channel
  int m_mode;

 public:

  SndJackIO(char* name, int channels=2, int mode=SND_IO, int
	    buffnos=2, SndObj** inObjs=0, int vecsize=DEF_VECSIZE,
            float sr=DEF_SR);

  ~SndJackIO();

  int ConnectIn(int channel, char* port);
  int ConnectOut(int channel, char* port);

  int DisconnectIn(int channel, char* port);
  int DisconnectOut(int channel, char* port);

  jack_client_t *GetClient() { return m_client; }
  jack_port_t *GetInPort(int channel) { return m_inport[channel-1];}
  jack_port_t *GetOutPort(int channel) { return m_outport[channel-1];}


  short Read();
  short Write();

  char *ErrorMessage();
  
  int JProcess(jack_nframes_t nframes);
  void JShutdown();
  
  int BufferResize(jack_nframes_t nframes);

};



#endif // _SNDJACKIO_H


