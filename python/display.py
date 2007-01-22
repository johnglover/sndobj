###################################
# PySndObj extensions: display classes
#
# VL, 01/07

from Tkinter import *
import time
import math
import array

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
            del self.item[0:len(self.item)]
            incr = s/self.size
            j = 0
            while(j < s):
              y = self.data[j]*self.size/2 + self.size/2
              self.item.append(self.canvas.create_line(count, self.prev, count+1, y, fill=self.line))
              self.prev = y       
              count += 1
              j += incr
            del self.data[0:s]
      
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
        self.data = array.array('f')
        Frame.__init__(self,master)
        self.pack()
        self.createCanvas()
        self.item = array.array('i')
        self.prev = 0
        self.n = 0
        self.master = master
        self.master.protocol("WM_DELETE_WINDOW", self.quit)

class Spectrum(Oscilloscope):

      def draw(self,re,im,frames):
         s = len(re)
         for i in range(0, s):
            y1 = re[i]
            y2 = im[i]
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
            del self.item[0:len(self.item)]
            s = len(self.spec)
            j = 0.0
            incr = (float(s)/self.size)
            while(j < s):
              y = -math.sqrt(self.spec[int(j)]/frames)*self.size + self.size 
              self.item.append(self.canvas.create_line(count, self.prev, count+1, y, fill=self.line, width=self.width))
              self.prev = y       
              count += 1
              j += incr
            del self.spec[0:s]


      def __init__(self,master,size,end,line="black",bg="white",width=1):
          Oscilloscope.__init__(self,master,size,end,line,bg)
          master.title("Spectrum")
          self.cnt = 0
          self.spec = array.array('f')
          self.error = 0
          self.width = width
          
