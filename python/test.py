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
    data[0].SetFreq(data[1].get(),data[2])
    #data[1].set(data[1].get()+1)

t = SndThread()

harm = HarmTable(10000,1,1)
osc = Oscili(harm, 440, 10000)
mod = Oscili(harm, 2, 5)
osc.SetFreq(440, mod)
tes = test(100)
dat = (osc, tes, mod)
t.SetPythonCallback(callb, dat)
outp = SndRTIO(osc)
t.AddObj(osc)
t.AddObj(mod)
t.AddObj(outp, SNDIO_OUT)
t.ProcOn()
time.sleep(2)
t.LimitVectorSize(64)
tes.set(100)
t.DeleteObj(mod)
time.sleep(2)
tes.set(100)
t.RestoreVectorSize()
time.sleep(2)
t.ProcOff()

#while(True):
 # osc.DoProcess()
 # outp.Write()


