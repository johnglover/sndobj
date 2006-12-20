// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information


#ifdef WIN

#ifndef _SNDASIO_H 

#define _SNDASIO_H

#include "SndIO.h"
#include <asiosys.h>
#include <asio.h>
#include <asiodrivers.h>



class SndASIO : public SndIO {

protected:

float **m_insndbuff;            // app buffers to store audio
float **m_outsndbuff;            
long  m_buffsize;               // needed in callbacks
long m_encoding;
char* m_driver;
int m_mode;
int m_ocount;
int m_icount;
int m_ocurrentbuffer;
int m_icurrentbuffer;
bool m_called_read;

bool m_running;

long  m_ichannels; 
long  m_ochannels;
ASIOBufferInfo* m_bufferinfos;  // ASIO buffer structures
ASIODriverInfo   m_driverinfo;  // ASIO Driver information
ASIOChannelInfo*  m_channelinfos; // ASIO channel information  
ASIOCallbacks    m_asiocallbacks; // ASIO callbacks

public:

SndASIO(int channels, int mode = SND_IO, char* driver = "ASIO Multimedia Driver", SndObj** inputs = 0, 
		int vecsize = DEF_VECSIZE, float sr=DEF_SR); 

~SndASIO();

	  short Write();
	  short Read();
	  char* ErrorMessage();

};

void DriverList();
char* DriverName(int num, char* name);

void bufferSwitch(long index, ASIOBool processNow);
ASIOTime *bufferSwitchTimeInfo(ASIOTime *timeInfo, 
							   long index, ASIOBool processNow);
void sampleRateChanged(ASIOSampleRate sRate);
long asioMessages(long selector, long value, 
				  void* message, double* opt);


 
#endif

#endif