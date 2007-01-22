#!/usr/bin/python
###############################################
# A little toy demonstrating PySndObj
#

from Tkinter import *
import sndobj
import math

# this is our computer instrument
# basically an oscillator and a filter
class Instrument:

    def Output(self):
       sig = self.fil.Output(0)
       return abs(sig)

    def SetFreq(self,freq):
       self.osc.SetFreq(freq*500)

    def SetAmp(self,amp):
       self.amp = amp*5000
       self.osc.SetAmp(self.amp)
       self.fil.SetFreq(self.amp*0.5, None)

    def On(self):
       self.env.SetCurve(0,self.amp)
       self.env.Restart()

    def Off(self):
       self.env.SetCurve(self.amp, 0)
       self.osc.SetAmp(0, self.env)
       self.env.Restart() 

    def __init__(self):
        self.amp = 5000
        self.tab = sndobj.HarmTable(16384, 25, sndobj.SQUARE)
        self.env = sndobj.Interp(0, 0, 0.02)
        self.osc = sndobj.Oscili(self.tab, 440, 0, None, self.env)
        self.fil = sndobj.Lp(100,0.5,self.osc)
        self.outp = sndobj.SndRTIO(self.fil)
        self.thread = sndobj.SndThread(0, None, self.outp)
        self.thread.AddObj(self.env)
        self.thread.AddObj(self.osc)
        self.thread.AddObj(self.fil)
        self.thread.ProcOn()

class Application(Frame):
  
    def move(self,event):
        canvas = event.widget
        x = canvas.canvasx(event.x)
        y = canvas.canvasy(event.y)
        item = canvas.find_withtag("current")[0]
        canvas.coords(item, x+10, y+10, x-10, y-10)
        self.ins.SetFreq(2.0*x/self.size)
        self.ins.SetAmp(2.0*(self.size-y)/self.size)
     
    def play(self,event):
        note = event.widget.find_withtag("current")[0]
        for i in range(1,len(self.notes),2):
            if note == self.notes[i]:
                val = self.notes[i-1]
                self.canvas.itemconfigure(i, fill="red")
                self.ins.On()
                self.ins.SetFreq(val)

    def stop(self,event):
        self.on = False
        note = event.widget.find_withtag("current")[0]
        for i in range(1,len(self.notes),2):
            if note == self.notes[i]:
                val = self.notes[i-1]
                self.ins.Off()
                
    def createCanvas(self):
        self.size = 600
        self.canvas = Canvas(self,height=self.size,width=self.size,bg="violet")
        self.canvas.pack()
    
         
    def createShapes(self):
          item = self.canvas.create_oval(self.size/2-10,self.size/2-10,self.size/2+10,self.size/2+10,fill="black")
          self.items.append(item)
          self.notes.append(440)
          self.notes.append(item)
          self.canvas.tag_bind(item,"<ButtonPress>", self.play)
          self.canvas.tag_bind(item,"<B1-Motion>", self.move)
          self.canvas.tag_bind(item,"<ButtonRelease>", self.stop)

        
    def meter(self):
        iw = 10
        for i in range(0, self.size, iw):
            self.vu.append(self.canvas.create_rectangle(i,self.size-40,i+iw,self.size,fill="grey"))

    def draw(self):
        level = self.ins.Output()
        cnt = 0
        red = (self.size/10)*0.8
        yellow = (self.size/10)*0.6
        for i in self.vu:
          if level > cnt*200:
           if cnt > red:
            self.canvas.itemconfigure(i, fill="red")
           elif cnt > yellow:
            self.canvas.itemconfigure(i, fill="yellow")
           else:
            self.canvas.itemconfigure(i, fill="blue")
          else:
           self.canvas.itemconfigure(i, fill="grey")
          cnt  = cnt + 1
        self.master.after(50,self.draw)
                
    def quit(self):
        self.master.destroy()

    def __init__(self,master=None):
        master.title("PySndObj + Tkinter: just click and play")
        self.items = []
        self.notes = []
        Frame.__init__(self,master)
        self.pack()
        self.createCanvas()  
        self.createShapes()
        self.ins = Instrument()
        self.vu = []
        self.meter()
        master.after(100, self.draw),
        self.master = master
        self.master.protocol("WM_DELETE_WINDOW", self.quit)

app = Application(Tk())
app.mainloop()
