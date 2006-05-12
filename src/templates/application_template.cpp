///////////////////////////////////////////////////////////
// Application template using SndThread
// 
// Victor Lazzarini, 2001
///////////////////////////////////////////////////////////

#include <SndObj/AudioDefs.h>
#include <string.h>


int
main(int argc, char** argv){

  char command[10];
  int status;
  SndThread thread;

  // declare your SndObj, SndIO & Table 
  // objects here

   
  // use thread.AddObj() to add the 
  // objects to the processing thread


  status = thread.GetStatus();
  while(1){
   cout << "Type a command: on, off or end\n";
   cin >> command;

   if(!strcmp(command, "on") && !status) 
        status = thread.ProcOn();// processing ON

   if(!strcmp(command, "off"))   // processing OFF
     status = thread.ProcOff();

   if(!strcmp(command, "end")){   // exit
     if(status) // if processing still ON
       thread.ProcOff(); 
     break;
   }
  }
  return 1;
}




