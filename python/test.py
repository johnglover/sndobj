from sndobj import *
import time
import sys

class test:
    def get(self):
       return self.i
    def set(self,val):
        self.i = val
    def __init__(self,val):
       self.i = val

def callb(data):
    data[0].SetFreq(data[1].get(),data[2])
    data[1].set(data[1].get()+1)

def callc(data):
    data[0].SetFreq(data[1].get(),data[2])
    data[1].set(data[1].get()-1)

t = SndRTThread()

harm = HarmTable(10000,1,1)
osc = Oscili(harm, 440, 10000)
mod = Oscili(harm, 2, 5)
osc.SetFreq(440, mod)
tes = test(100)
dat = (osc, tes, mod)

t.SetProcessCallback(callb, dat)
t.AddObj(mod)
t.AddOutput(1, osc)

t.ProcOn()
time.sleep(2)
t.LimitVectorSize(64)
tes.set(100)

time.sleep(2)
t.SetProcessCallback(callc,dat)
tes.set(1000)
t.RestoreVectorSize()
time.sleep(2)
t.ProcOff()




