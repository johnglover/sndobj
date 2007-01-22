#!/usr/bin/python
###################################
# Stereo echo demonstrating the SndRTThread class
#
#  VL, 01/07

from sndobj import *
import time
import sys

if len(sys.argv) > 1:
    dur = sys.argv[1]
else:
    dur = 60

# SndRTThread object has its own IO objects
# by the default it is created wth 2 channels
t = SndRTThread(2)
# Echo objects take input from SndRTThread inputs
comb_left =  Comb(0.48, 0.6, t.GetInput(1))
comb_right = Comb(0.52, 0.6, t.GetInput(1))
# We add the echo objects to the output channels
t.AddOutput(1, comb_left)
t.AddOutput(2, comb_right)
t.Direct(1)
t.Direct(2)
# Processing
t.ProcOn()
time.sleep(float(dur))
t.ProcOff()
time.sleep(0.1)
