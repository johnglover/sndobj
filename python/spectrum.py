#####################################
#  oscilloscope example
#  
#   VL, 01/07

from sndobj import *
from Tkinter import *
import display

# window size, refresh interval, norm factor
# highest frequency of display
window_size = 300
time_interval = 0.2
norm = 32768.0/20
highest = 16000

# display callback
def callb(data):
    sig  = []
    fft  = data[0]
    disp = data[1]
    sr = fft.GetSr()
    end = int(fft.GetFFTSize()*2*highest/sr)
    for i in range(0,end,2):
         sig.append((fft.Output(i)/norm,fft.Output(i+1)/norm))
    disp.draw(sig,(sr/fft.GetHopSize())*time_interval)
    
# SndObj chain and process thread       
saw = HarmTable(10000,40,2)
sine = HarmTable(10000,1,1)
mod = Oscili(sine, 1, 50)
osc = Oscili(saw, 400, 10000, mod)
win = HammingTable(1024,0.5)
fft = FFT(win,osc)
thread = SndRTThread(2, 4096, 4)

# display object
disp = display.Spectrum(Tk(), window_size, thread.ProcOff, "red", "blue")
dat = (fft,disp)

# thread set-up
thread.SetProcessCallback(callb, dat)
thread.AddObj(mod)
thread.AddOutput(1, osc)
thread.AddObj(fft)
thread.ProcOn()

# run the display
disp.mainloop()





