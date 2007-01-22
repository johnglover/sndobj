#!/usr/bin/python
#####################################
#  spectrum example
#  
#   VL, 01/07

from sndobj import *
from Tkinter import *
import array
import display

# window size, refresh interval, norm factor
# highest frequency of display
window_size = 300
time_interval = 0.1
norm = 32768.0/10
highest = 10000

# display callback
def callb(data):
    re  = array.array('f')
    im  = array.array('f')
    fft  = data[0]
    disp = data[1]
    sr = fft.GetSr()
    end = int(fft.GetFFTSize()*2*highest/sr)
    for i in range(0,end,2):
         re.append(fft.Output(i)/norm)
         im.append(fft.Output(i+1)/norm)
    if not disp.error:
      disp.draw(re,im,(sr/fft.GetHopSize())*time_interval)
    
# SndObj chain and process thread       
win = HammingTable(1024,0.5)
thread = SndThread()
inp = SndRTIO(1, SND_INPUT)
sig = SndIn(inp, 1)
fft = FFT(win,sig);

# display object
disp = display.Spectrum(Tk(), window_size, thread.ProcOff, "red", "blue")
dat = (fft,disp)

# thread set-up
thread.SetProcessCallback(callb, dat)
thread.AddObj(inp, SNDIO_IN)
thread.AddObj(sig)
thread.AddObj(fft)
thread.ProcOn()

# run the display
disp.mainloop()





