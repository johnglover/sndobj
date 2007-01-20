###################################
# PySndObj extensions: display classes
#
#  VL, 01/07

from Tkinter import *
import time

class Oscilloscope(Frame):
                
    def createCanvas(self):
        self.canvas = Canvas(self,height=self.size,width=self.size,bg="white")
        self.canvas.pack()

    def draw(self,what):
        count = 0
        for i in self.item:
           self.canvas.delete(i)
        self.item = []
        incr = (len(what)/float(self.size))
        for i in range(0, len(what), int(incr)):
          self.item.append(self.canvas.create_line(count, self.prev, count+1, what[i]))
          self.prev = what[i]       
          count += 1
      
    def quit(self):
        self.close();
        time.sleep(0.1)
        self.master.destroy()

    def sinal(self):
        sig = []
        size = 16384
        d = self.size/100.0
        for i in range(self.n, self.n+size):
           sig.append(self.size/2+(self.size/3)*math.sin(i/d))
        self.draw(sig)
        self.n += size
        self.master.after(50, self.sinal)

    def __init__(self,master, size, end):
        master.title("Oscilloscope")
        self.size = size
        self.close = end
        self.items = []
        self.notes = []
        Frame.__init__(self,master)
        self.pack()
        self.createCanvas()
        self.item = []
        self.prev = 0
        self.n = 0
        self.master = master
        self.master.protocol("WM_DELETE_WINDOW", self.quit)


