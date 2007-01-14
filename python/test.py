from sndobj import *
import time

class test:
    def get(self):
       return self.i
    def set(self,val):
        self.i = val
    def __init__(self,val):
       self.i = val

def callb(data):
    data[0].SetFreq(data[1].get())
    data[1].set(data[1].get()+1)

t = SndThread()

harm = HarmTable(10000,1,1)
osc = Oscili(harm, 440, 10000)
tes = test(100)
dat = (osc, tes)
t.SetPythonCallback(callb, dat)
outp = SndRTIO(osc)
t.AddObj(osc)
t.AddObj(outp, SNDIO_OUT)
t.ProcOn()
time.sleep(2)
t.ProcOff()

#while(True):
 # osc.DoProcess()
 # outp.Write()


