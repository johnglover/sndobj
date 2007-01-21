###################################
# PySndObj extensions: display classes
#
# VL, 01/07

from Tkinter import *
import time
import math

class Oscilloscope(Frame):
                
    def createCanvas(self):
        self.canvas = Canvas(self,height=self.size,width=self.size,bg=self.bg)
        self.canvas.pack()

    def draw(self,what,samples):
        for i in what:
           self.data.append(i);
        s = len(self.data)
        if s >= samples:
            count = 0
            for i in self.item:
               self.canvas.delete(i)
            self.item = []
            incr = s/self.size
            j = 0
            while(j < s):
              y = self.data[j]*self.size/2 + self.size/2
              self.item.append(self.canvas.create_line(count, self.prev, count+1, y, fill=self.line))
              self.prev = y       
              count += 1
              j += incr
            self.data = []
      
    def quit(self):
        self.close();
        time.sleep(0.1)
        self.master.destroy()

    def __init__(self,master, size, end, line="black", bg="white"):
        master.title("Oscilloscope")
        self.size = size
        self.close = end
        self.line = line
        self.bg = bg
        self.items = []
        self.notes = []
        self.data = []
        Frame.__init__(self,master)
        self.pack()
        self.createCanvas()
        self.item = []
        self.prev = 0
        self.n = 0
        self.master = master
        self.master.protocol("WM_DELETE_WINDOW", self.quit)

class Spectrum(Oscilloscope):

      def draw(self,what,frames):
         s = len(what)
         for i in range(0, s):
            y1 = what[i][0]
            y2 = what[i][1]
            if self.cnt == 0:
              self.spec.append(y1*y1+y2*y2)
            else:
              self.spec[i] = (y1*y1+y2*y2+self.spec[i])
         self.cnt += 1
         if self.cnt >= frames:
            self.cnt = 0
            count = 0
            for i in self.item:
               self.canvas.delete(i)
            self.item = []
            s = len(self.spec)
            j = 0.0
            incr = (float(s)/self.size)
            while(j < s):
              y = -math.sqrt(self.spec[int(j)]/frames)*self.size + self.size
              self.item.append(self.canvas.create_line(count, self.prev, count+1, y, fill=self.line))
              self.prev = y       
              count += 1
              j += incr
            self.spec = []


      def __init__(self,master,size,end,line="black",bg="white"):
          Oscilloscope.__init__(self,master,size,end,line,bg)
          master.title("Spectrum")
          self.cnt = 0
          self.spec = []
          
