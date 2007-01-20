#####################################
#  oscilloscope example
#  
#   VL, 01/07

from sndobj import *
from Tkinter import *
import display

# window size, refresh interval and norm factor
window_size = 300
time_interval = 0.1
norm = 32768.0

# callback data structure
class cdata:
    def __init__(self,obj,disp,sig,val):
       self.sig = sig
       self.obj = obj
       self.disp = disp
       self.cnt = val

# display callback
def callb(data):
    j = data.cnt
    for i in range(j,256+j):
        data.sig.append(window_size/2 + (window_size/2)*(data.obj.Output(i)/norm))
    data.cnt = j+256
    if (data.cnt >= time_interval*44100):
       data.disp.draw(data.sig)
       del data.sig[0:len(data.sig)]
       data.cnt = 0

# SndObj chain and process thread       
harm = HarmTable(10000,1,1)
mod = Oscili(harm, 10, 5000)
osc = Oscili(harm, 100, 5000, None, mod)
thread = SndRTThread(2, 4096, 4)

# display object
disp = display.Oscilloscope(Tk(), window_size, thread.ProcOff)
sig = []
dat = cdata(osc,disp,sig,0)

# thread set-up
thread.SetProcessCallback(callb, dat)
thread.AddObj(mod)
thread.AddOutput(1, osc)
thread.ProcOn()

# run the display
disp.mainloop()





