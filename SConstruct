####################################################################
# This file is part of the SndObj library
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
#
#
# scons build system for SndObj
# 
# Copyright (C) 2005 by Tim Blechmann and Victor Lazzarini
#
#  See License.txt for for a disclaimer of all warranties
#  and licensing information

import sys
import os
import distutils.sysconfig

env = Environment(ENV = {'PATH' : os.environ['PATH']})
env.SConsignFile()
# env.CacheDir('./obj')

######################################################################
#
# general configuration



def getVersion():
    return sys.version[:3]    

def getPlatform():
    if sys.platform[:5] == 'linux':
        return 'linux'
    elif sys.platform[:3] == 'win':
        if env['PLATFORM'] == 'win32':
        	return 'win'
	else:
		return 'cygwin'
    elif sys.platform[:6] == 'darwin':
        return 'macosx'
    elif sys.platform[:4] == 'irix' :
        return 'sgi'
    else:
        return 'unsupported'

opt = Options(['options.cache'])
opt.AddOptions(
	BoolOption('alsa', 'on linux, build with alsa support', True),
	BoolOption('oss',  'on unix or linux, build with OSS support', False),
        BoolOption('jack', 'on linux or OSX, build with Jack support', True),
	('flags', 'additional compile flags', ""),
	('prefix', 'install prefix of headers, static lib and shared lib', '/usr/local'),
        ('instdir', 'base directory', ''), 
        ('pddir', 'PD directory on windows', 'C:\\PureData'),
        BoolOption('nostaticlib', 'do not build static library', True),
        BoolOption('pythonmodule', 'build python module', False),
        BoolOption('javamodule', 'build java module', False),
        BoolOption('lispmodule', 'build CFFI module', False),
        BoolOption('examples', 'build C++ examples', False),
        ('install_name', 'on OSX, the dynamic library full install pathname (before installation)', 'lib/libsndobj.dylib'),
        ('pythonpath', 'python include path (defaults to usual places)', ''),
        ('pythonlibpath', 'python lib path (WIN only,defaults to usual places)', ''),
        ('javapath', 'java headers path (defaults to usual places)', ''),
        ('customCPPPATH', '',''),
        ('customCCFLAGS', '',''),
        ('customCXXFLAGS','',''),
        ('customLIBS','',''),
        ('customLIBPATH','',''),
        ('customSHLINKFLAGS','',''),
        ('customSWIGFLAGS','',''),
        ('version', 'library version','2.6.5')
	)

opt.Update(env)
opt.Save('options.cache',env)
Help(opt.GenerateHelpText(env))
version = env['version']
print "SndObj Library version is " + version
 
customCPPPATH = env['customCPPPATH']
env.Prepend(CPPPATH = customCPPPATH)
customCCFLAGS = env['customCCFLAGS']
env.Prepend(CCFLAGS = customCCFLAGS)
customCXXFLAGS = env['customCXXFLAGS']
env.Prepend(CXXFLAGS = customCXXFLAGS)
customLIBS = env['customLIBS']
env.Prepend(LIBS = customLIBS)
customLIBPATH = env['customLIBPATH']
env.Prepend(LIBPATH = customLIBPATH)
customSHLINKFLAGS = env['customSHLINKFLAGS']
env.Prepend(SHLINKFLAGS = customSHLINKFLAGS)
customSWIGFLAGS = env['customSWIGFLAGS']
env.Prepend(SWIGFLAGS = customSWIGFLAGS)

print "Building the Sound Object Library"
configure = env.Configure()

cffipath = ''
pythonlibpath = []
print "Checking for Realtime IO support..." 
if getPlatform() == 'linux':
        msvctools = False
        print "OS is Linux..."
        hdrs = env.Command('include/SndObj/AudioDefs.h', 'src/AudioDefs.h', "cp -f src/*.h include/SndObj")
	alsaFound = configure.CheckHeader("alsa/asoundlib.h", language = "C")
	ossFound = configure.CheckHeader("soundcard.h", language="C")
	jackFound = configure.CheckHeader("jack/jack.h", language = "C")
	if alsaFound and env['alsa']:
	  env.Append(CPPDEFINES="ALSA")
          swigdef = ['-DALSA']
          env.Append(LIBS=['asound'])
          print "The library realtime IO (class SndRTIO) will be configured for ALSA"
	  rtio = True 
	elif ossFound and env['oss']:
	  env.Append(CPPDEFINES="OSS")
          print "The library realtime IO (class SndRTIO) will be configured for OSS"
          rtio = True
        else:
          print "No alsa or OSS RT support"
          rtio = False  
	if jackFound:
          env.Append(CPPDEFINES=Split('JACK'))
          env.Append(LIBS=['jack'])
          swigdef.append('-DJACK')
          print "The library will include support for Jack (Class SndJackIO)"
        pythonincpath = ['/usr/include/python' + getVersion(), env['pythonpath']]
        javapath =   ['/usr/lib/java/jvm/include', env['javapath']]
       
   
if getPlatform() == 'win':
        print "OS is Windows, environment is win32..."
	env.Append(CPPDEFINES="WIN")
        swigdef = ['-DWIN', '-DSWIGFIX', '-D_MSBC']
        if 'msvc'in env['TOOLS']: # MSVC
          msvctools = True
          hdrs = env.Command('include/SndObj/AudioDefs.h', 'src/AudioDefs.h', "copy  src\\*.h include\\SndObj")
          separateLibs = False
          print 'using MSVC...'
          includes = "C:\\Program Files\\Microsoft Visual Studio\\VC98\\include"
          libs = "C:\\Program Files\\Microsoft Visual Studio\\VC98\\lib"
          env.Append(CPPPATH=['msvc6.0'])
          pythonlib=''
          env.Append(LIBS=['pthreadVC', 'advapi32', 'user32'])
        else: # mingw ? Set any outstanding mingwin paths here
          msvctools = False
          hdrs = env.Command('include/SndObj/AudioDefs.h', 'src/AudioDefs.h', "cp -f src/*.h include/SndObj")
          separateLibs = True
          print 'using MINGW...'
          env.Append(CPPDEFINES=['GCC', 'USE_WIN32THREADS'])
          swigdef.append(['-DUSE_WIN32THREADS'])
          includes = ''
          libs     = ''
          pythonlib = 'python%c%c'% (getVersion()[0], getVersion()[2])
        env.Append(CPPPATH=[includes])
 	env.Append(LIBPATH=[libs])
 	env.Append(LIBPATH=['lib'])
        env.Append(LIBS=['winmm'])
        rtio = True
        jackFound = False
        pythonincpath = ['c:\\Python%c%c\include' % (getVersion()[0], getVersion()[2]), env['pythonpath']]
        pythonlibpath.append('c:\\Python%c%c\libs' % (getVersion()[0], getVersion()[2]))
        pythonlibpath.append(env['pythonlibpath'])
        javapath = ["C:\\Program Files\\Java\\jdk1.5.0_05",env['javapath']]

if getPlatform() == 'cygwin':
        print "OS is Windows, environment is Cygwin..."
        msvctools = False
	env.Append(CPPDEFINES=['WIN', 'GCC'])
        swigdef = ['-DWIN', '-DSWIGFIX', '-D_MBCS']
        env.Append(LIBS=['winmm', 'pthread'])
        env.Append(LIBPATH=['lib'])
        rtio = True
        jackFound = False
        pythonincpath = ['/usr/include/python' + getVersion(), env['pythonpath']]
        javapath =   ['/usr/lib/java/jvm/include', env['javapath']]

if getPlatform() == 'macosx':
        print "OS is MacOSX"
        msvctools = False
        hdrs = env.Command('include/SndObj/AudioDefs.h', 'src/AudioDefs.h', "cp -f src/*.h include/SndObj")
	env.Append(CPPDEFINES="MACOSX")
        swigdef = ['-DMACOSX']
	env.Append(CPPPATH=["/system/library/Frameworks/CoreAudio.framework/Headers"])
        env.Append(LINKFLAGS= ['-framework', 'coreaudio'])
        jackFound = configure.CheckHeader("jack/jack.h", language = "C")
        if jackFound:
	  env.Append(CPPDEFINES=Split('JACK'))
          env.Append(LIBS=Split('jack'))
          swigdef.append('-DJACK')
          print "The library will include support for Jack (Class SndJackIO)" 
        rtio = True
        pythonincpath = [env['pythonpath'], '/Library/Frameworks/Python.framework/Headers', '/System/Library/Frameworks/Python.framework/Headers']
        javapath = ['/System/Library/Frameworks/JavaVM.framework', env['javapath']]  


if getPlatform() == 'sgi':
        print "OS is SGI/Irix..."
        msvctools = False
        hdrs = env.Command('include/SndObj/AudioDefs.h', 'src/AudioDefs.h', "cp -f src/*.h include/SndObj")
        env.Append(CPPDEFINES="SGI")
        swigdef = ['-DSGI']
        env.Append(LIBS=['audio', 'midi', 'pthread'])
        rtio = True
        jackFound = False
        pythonincpath = ['/usr/include/python' + getVersion(), env['pythonpath']]
        javapath =   ['/usr/lib/java/jvm/include', env['javapath']]
       

if getPlatform() == 'unsupported':
       print "Realtime IO not supported on this platform: %s" % sys.platform
       hdrs = env.Command('include/SndObj/AudioDefs.h', 'src/AudioDefs.h', "cp -f src/*.h include/SndObj")
       rtio = False
       swigdef = ['-DNO_RTIO']
       env.Append(LIBS=['pthread'])
       msvctools = False
       jackFound = False
       pythonincpath = ['/usr/include/python%c%c' % (getVersion()[0], getVersion()[2]), env['pythonpath']]      
       javapath = ['/usr/java/include', env['javapath']]

if not msvctools:
   flags = "-O2" + env['flags']
else:
   flags = "-GX -GB -O2" + env['flags']
   
#check endianness
if sys.byteorder == "big":
    print "Host is big endian"
    env.Append(CPPFLAGS="-DWORDS_BIGENDIAN")
else:
    print "Host is little endian"

if not rtio:
   env.Prepend(CPPDEFINES=['NO_RTIO'])

env.Prepend(CPPPATH= ['include','include/rfftw'])
swigcheck = 'swig' in env['TOOLS']
print 'swig %s' % (["doesn't exist", "exists..."][int(swigcheck)])

pythonh = configure.CheckHeader("Python.h", language = "C")
if not pythonh:
 for i in pythonincpath:
    pythonh = configure.CheckHeader("%s/Python.h" % i, language = "C")
    if pythonh:
      print "Python version is " + getVersion()
      break

if not pythonh:
    print "Python headers are missing... cannot build python module"

pysndobj = env.Copy()
jsndobj = env.Copy()
cffisndobj = env.Copy()
examples = env.Copy()

if getPlatform() == 'linux':
      env.Append(SHLINKFLAGS=['-Wl,-soname=libsndobj.so.%s'% version])
######################################################################
#
# sources

sndobjsources = Split("""Oscil.cpp Oscilt.cpp Oscili.cpp 
PhOscili.cpp ADSR.cpp IADSR.cpp Buzz.cpp 
Balance.cpp DelayLine.cpp Tap.cpp Tapi.cpp 
Comb.cpp Allpass.cpp StringFlt.cpp Pluck.cpp 
VDelay.cpp Pitch.cpp Loop.cpp Filter.cpp 
Reson.cpp Lp.cpp ButtBP.cpp ButtBR.cpp 
ButtHP.cpp ButtLP.cpp Mix.cpp Pan.cpp 
Gain.cpp SyncGrain.cpp Interp.cpp Phase.cpp 
Lookup.cpp Lookupi.cpp Ring.cpp Rand.cpp 
Randh.cpp Randi.cpp Unit.cpp Ap.cpp 
Hilb.cpp SndIn.cpp SndObj.cpp MidiIn.cpp 
MidiMap.cpp Bend.cpp Fir.cpp FFT.cpp 
IFFT.cpp Convol.cpp FastOsc.cpp Osc.cpp 
Osci.cpp PVA.cpp IFGram.cpp HiPass.cpp 
LowPass.cpp TpTz.cpp PVS.cpp PVMorph.cpp 
PVFilter.cpp PVMask.cpp PVMix.cpp 
PVTransp.cpp PVBlur.cpp PVRead.cpp 
SinAnal.cpp SinSyn.cpp AdSyn.cpp ReSyn.cpp IFAdd.cpp 
SndRead.cpp SpecIn.cpp SpecMult.cpp 
SpecCart.cpp SpecCombine.cpp SpecInterp.cpp 
SpecPolar.cpp SpecSplit.cpp SpecThresh.cpp 
SpecVoc.cpp  Ptrack.cpp""")

sndiosources = Split("""SndIO.cpp SndRTIO.cpp SndFIO.cpp 
SndWave.cpp SndAiff.cpp SndBuffer.cpp 
SndMidi.cpp SndMidiIn.cpp SndWaveX.cpp 
SndPVOCEX.cpp SndSinIO.cpp  SndCoreAudio.cpp SndJackIO.cpp SndASIO.cpp """)

tablesources = Split("""HarmTable.cpp UsrHarmTable.cpp 
TrisegTable.cpp SndTable.cpp PlnTable.cpp 
HammingTable.cpp NoteTable.cpp UsrDefTable.cpp 
LoPassTable.cpp ImpulseTable.cpp 
SpecEnvTable.cpp  EnvTable.cpp PVEnvTable.cpp PVTable.cpp""")
					 
sndthrsources = Split("""SndThread.cpp SndRTThread.cpp""")

fftwsources = Split("""config.c  fcr_9.c fhf_6.c fn_8.c  frc_1.c  ftw_16.c ftwi_7.c \
executor.c fftwnd.c fhf_7.c fn_9.c  frc_10.c ftw_2.c  ftwi_8.c 
fcr_1.c fhb_10.c fhf_8.c fni_1.c frc_11.c ftw_3.c  ftwi_9.c 
fcr_10.c  fhb_16.c fhf_9.c fni_10.c frc_12.c ftw_32.c generic.c 
fcr_11.c  fhb_2.c fn_1.c fni_11.c frc_128.c ftw_4.c  malloc.c 
fcr_12.c  fhb_3.c fn_10.c fni_12.c frc_13.c ftw_5.c  planner.c 
fcr_128.c fhb_32.c fn_11.c fni_13.c frc_14.c ftw_6.c  putils.c 
fcr_13.c  fhb_4.c fn_12.c fni_14.c frc_15.c ftw_64.c rader.c 
fcr_14.c  fhb_5.c fn_13.c fni_15.c frc_16.c ftw_7.c  rconfig.c 
fcr_15.c  fhb_6.c fn_14.c fni_16.c frc_2.c  ftw_8.c  rexec.c 
fcr_16.c  fhb_7.c fn_15.c fni_2.c frc_3.c  ftw_9.c  rexec2.c 
fcr_2.c fhb_8.c fn_16.c fni_3.c frc_32.c ftwi_10.c rfftwf77.c 
fcr_3.c fhb_9.c fn_2.c fni_32.c frc_4.c  ftwi_16.c rfftwnd.c 
fcr_32.c  fhf_10.c fn_3.c fni_4.c frc_5.c  ftwi_2.c rgeneric.c 
fcr_4.c fhf_16.c fn_32.c fni_5.c frc_6.c  ftwi_3.c rplanner.c 
fcr_5.c fhf_2.c fn_4.c fni_6.c frc_64.c ftwi_32.c timer.c 
fcr_6.c fhf_3.c fn_5.c fni_64.c frc_7.c  ftwi_4.c twiddle.c 
fcr_64.c  fhf_32.c fn_6.c fni_7.c frc_8.c  ftwi_5.c wisdom.c 
fcr_7.c fhf_4.c fn_64.c fni_8.c frc_9.c  ftwi_6.c wisdomio.c 
fcr_8.c fhf_5.c fn_7.c fni_9.c ftw_10.c ftwi_64.c cfft.c""")
asios = Split("""iasiothiscallresolver.cpp asiodrivers.cpp asio.cpp asiolist.cpp""")


sndsources = map(lambda x: './src/' + x, sndobjsources + sndiosources \
			  + tablesources + sndthrsources) 
rfftsources = map(lambda x: './src/rfftw/' + x, fftwsources)

asiosources = map(lambda x: './src/asio/' + x, asios)

######################################################################
#
# build

if getPlatform() != 'win':
  sources = sndsources + rfftsources 
  env.Prepend(CCFLAGS = flags)
  if getPlatform() == 'macosx':
   env.Append(LINKFLAGS=['-install_name', env['install_name']])
   sndobjlib = env.SharedLibrary(env['install_name'], sources)
  else:
   sndobjlib = env.SharedLibrary('lib/libsndobj.so' + '.' + version, sources, SHLIBPREFIX = '', SHLIBSUFFIX = '')
   os.spawnvp(os.P_WAIT, 'rm', ['rm', '-f', 'lib/libsndobj.so'])
   os.symlink('libsndobj.so' + '.' + version, 'lib/libsndobj.so')
   sndobjlink = 'lib/libsndobj.so'
  deplibs = [sndobjlib]
  baselibs = ['sndobj']
  if not env['nostaticlib']:
    sndobjliba =  env.Library('lib/sndobj',sources)
    deplibs.append([sndobjliba])
    Depends(sndobjliba, hdrs)
else:
  if separateLibs:
   rfftwlib = env.Library('lib/rfftw', rfftsources, CCFLAGS=flags)
   sndobjlib = env.Library('lib/sndobj', sndsources+asiosources, CCFLAGS=flags)
   deplibs = [sndobjlib, rfftwlib]
   baselibs = ['sndobj', 'rfftw']
   libdest = 'libsndobj.a'
  else:
   sndobjlib = env.Library('lib/sndobj', sndsources+rfftsources+asiosources, CCFLAGS=flags)
   deplibs = [sndobjlib]
   baselibs = ['sndobj']
Depends(sndobjlib, hdrs)


####################################################################
# 
# Python module

if swigcheck and env['pythonmodule'] and pythonh:
  pswigdef = swigdef
  pswigdef.append(['-lcarrays.i', '-c++', '-python','-Isrc', '-v'])
  pysndobj.Append(SWIGFLAGS=pswigdef)
  pysndobj.Append(LIBPATH='./lib')
  pysndobj.Append(CPPDEFINES=['SWIG','PYTHON_WRAP'])
  pysndobj.Prepend(LIBS=baselibs)
  pysndobj.Prepend(CPPPATH=['src'])
  pysndobj.Prepend(CCFLAGS=flags)
  pysndobj.Append(SWIGFLAGS=['-outdir', '.' ])
  if getPlatform() == 'macosx':
    for i in pythonincpath:
      if i != '':
        pysndobj.Prepend(CPPPATH=[i])
    pysndobj.Prepend(LINKFLAGS=['-bundle', '-framework', 'python'])
    pywrap = pysndobj.SharedObject('python/AudioDefs.i')
    pymod = pysndobj.Program('python/_sndobj.so', pywrap)
    pysndobj.Command('python/sndobj.py', 'sndobj.py', 'cp sndobj.py python/sndobj.py')
    if env['install_name'] == 'lib/libsndobj.dylib':
       pysndobj.Command('link', 'lib/libsndobj.dylib', 'cd python/lib; ln -sf ../../lib/libsndobj.dylib libsndobj.dylib')
    else:
       pysndobj.Command('link', 'lib/libsndobj.dylib', 'cd python/lib; ln -sf %s libsndobj.dylib' % env['install_name'])
  elif getPlatform() == 'win' or getPlatform() == 'cygwin':
    for i in pythonincpath:
      if i != '':
       pysndobj.Prepend(CPPPATH=[i])
    for i in pythonlibpath:
      if i != '':
       pysndobj.Prepend(LIBPATH=[i])
    pysndobj.Append(LIBS=[pythonlib, 'ole32'])
    pywrap = pysndobj.SharedObject('python/AudioDefs.i')
    pymod = pysndobj.SharedLibrary('python/sndobj', pywrap, SHLIBPREFIX='_', SHLIBSUFFIX='.pyd')
  else:
    for i in pythonincpath:
      if i != '':
       pysndobj.Prepend(CPPPATH=[i])
    pysndobj.Prepend(LIBS=['python'+getVersion()])
    pymod = pysndobj.SharedLibrary('python/sndobj', 'python/AudioDefs.i', SHLIBPREFIX='_')
    pysndobj.Command('python/sndobj.py', 'sndobj.py', 'cp sndobj.py python/sndobj.py')
  Depends(pymod,sndobjlib)


####################################################################
# 
# Java module

if swigcheck and env['javamodule']:
  jswigdef = swigdef
  jswigdef.append(['-lcarrays.i', '-c++', '-java','-Isrc', '-Iinclude', '-v'])
  jsndobj.Append(SWIGFLAGS=jswigdef)
  jsndobj.Append(LIBPATH='./lib')
  jsndobj.Prepend(LIBS=baselibs)
  jsndobj.Prepend(CPPPATH=['src'])
  if getPlatform() == 'macosx':
    for i in javapath:
     if i != '':
       jsndobj.Prepend(CPPPATH=["%s/Headers" % i, 'src'])
    jsndobj.Prepend(LINKFLAGS=['-bundle', '-framework', 'JavaVM'])
    jwrap = jsndobj.SharedObject('java/AudioDefs.i', CCFLAGS=flags)
    jmod = jsndobj.Program('java/lib_sndobj.jnilib', pywrap)
    if env['install_name'] == 'lib/libsndobj.dylib':
       jsndobj.Command('link', 'lib/libsndobj.dylib', 'cd java/lib; ln -sf ../../lib/libsndobj.dylib libsndobj.dylib')
    else:
       jsndobj.Command('link', 'lib/libsndobj.dylib', 'cd java/lib; ln -sf %s libsndobj.dylib' % env['install_name'])
  elif getPlatform() == 'win':
    for i in javapath:
     if i != '':
       jsndobj.Prepend(CPPPATH=[i+'\\include',i+'\\include\win32'])
    jsndobj.Prepend(LIBPATH=[javapath+'\\libs'])
    jwrap = jsndobj.SharedObject('java/AudioDefs.i', CCFLAGS=flags)
    jmod = jsndobj.SharedLibrary('java/sndobj', jwrap, SHLIBPREFIX='_')
  else:
    for i in javapath:
     if i != '':
       jsndobj.Prepend(CPPPATH=[i])
    jwrap = jsndobj.SharedObject('java/AudioDefs.i', CCFLAGS=flags)
    jmod = jsndobj.SharedLibrary('java/sndobj', jwrap, SHLIBPREFIX='lib_')
  Depends(jmod,sndobjlib)
  try:
     os.mkdir('java/JSndObj', 0755)
  except:
     pass
  jcode =  jsndobj.Java(target = './java/JSndObj', source = './java')
  #sndobjar = jsndobj.Jar('sndobj.jar', ['.'], JARCHDIR = './java/JSndObj')
  #Depends(sndobjar, jcode)

###################################################################
# Common Lisp - CFFI module
#

if swigcheck and env['lispmodule']:
  lswigdef = swigdef
  lswigdef.append(['-lcarrays.i', '-c++', '-cffi','-Isrc', '-Iinclude', '-v'])
  cffisndobj.Append(SWIGFLAGS=lswigdef)
  cffisndobj.Append(CPPDEFINES=['SWIG','SWIGCFFI'])
  cffisndobj.Append(LIBPATH='./lib')
  cffisndobj.Prepend(LIBS=baselibs)
  if getPlatform() == 'macosx':
    cffisndobj.Prepend(CCFLAGS='-fpascal-strings')
    cffisndobj.Prepend(CPPPATH=["%s/Headers" % lisppath, 'src'])
    cffisndobj.Prepend(LINKFLAGS=['-framework', 'Carbon', '-framework', 'CoreMIDI',  '-framework', 'OpenGL', '-framework', 'AGL', '-framework', 'QuickTime'])
    cffiwrap = cffisndobj.SharedObject('cffi/AudioDefs.i', CCFLAGS=flags)
    cffimod = cffisndobj.ShareLibrary('cffi/sndobj', cffiwrap)
    if env['install_name'] == 'lib/libsndobj.dylib':
       jsndobj.Command('link', 'lib/libsndobj.dylib', 'cd cffi/lib; ln -sf ../../lib/libsndobj.dylib libsndobj.dylib')
    else:
       jsndobj.Command('link', 'lib/libsndobj.dylib', 'cd cffi/lib; ln -sf %s libsndobj.dylib' % env['install_name'])
  elif getPlatform() == 'win':
    cffisndobj.Prepend(CPPPATH=[cffipath+'\\include', 'src',cffipath+'\\include\win32'])
    cffisndobj.Prepend(LIBPATH=[cffipath+'\\libs'])
    cffiwrap = cffisndobj.SharedObject('cffi/AudioDefs.i', CCFLAGS=flags)
    cffimod = cffisndobj.SharedLibrary('cffi/sndobj', cffiwrap, SHLIBPREFIX='_')
  else:
    cffisndobj.Prepend(CPPPATH=[cffipath, 'src'])
    cffiwrap = cffisndobj.SharedObject('cffi/AudioDefs.i', CCFLAGS=flags)
    cffimod = cffisndobj.SharedLibrary('cffi/sndobj', cffiwrap, SHLIBPREFIX='lib_')
  Depends(cffimod,sndobjlib)



####################################################################
#
# example programs


examples.Append(LIBPATH='./lib')
examples.Prepend(LIBS=baselibs)

def BuildExample(prog, example, source):
    if env['examples']:
     obj = examples.Object(example, source, CCFLAGS=flags)
     prg = examples.Program(prog, example)
     Depends(prg, obj)
     return obj
    else:
     return None

# jack examples
if jackFound:
       examples.Append(LIBS= ['jack'])
       schroeder_jack = BuildExample('./bin/jack_schroeder','./obj/jack_schroeder.o', 'src/examples/jack_schroeder.cpp')
       examples.Depends(schroeder_jack, deplibs)
       streson_jack =   BuildExample('./bin/jack_streson', './obj/jack_streson.o', 'src/examples/jack_streson.cpp')
       Depends(streson_jack, deplibs)
# realtime IO examples
if rtio:
	rtschroeder = BuildExample('./bin/rtschroeder','./obj/rtschroeder.o', 'src/examples/rtschroeder.cpp')
        Depends(rtschroeder, deplibs)
	streson = BuildExample('./bin/streson','./obj/streson.o', 'src/examples/streson.cpp')
        Depends(streson, deplibs)       
	blurring = BuildExample('./bin/blurring','./obj/blurring.o', 'src/examples/blurring.cpp')
        Depends(blurring, deplibs)
	harmonise = BuildExample('./bin/harmonise','./obj/harmonise.o', 'src/examples/harmonise.cpp')
        Depends(harmonise, deplibs)
	transpose = BuildExample('./bin/transpose','./obj/transpose.o', 'src/examples/transpose.cpp')
        Depends(transpose, deplibs)
# schroeder
schroeder = BuildExample('./bin/schroeder','./obj/schroeder.o', 'src/examples/schroeder.cpp')
Depends(schroeder, deplibs)
# cvoc
cvoc = BuildExample('./bin/cvoc','./obj/cvoc.o', 'src/examples/cvoc.cpp')
Depends(cvoc, deplibs)
# denoiser
denoiser = BuildExample('./bin/denoiser','./obj/denoiser.o', 'src/examples/denoiser.cpp')
Depends(denoiser, deplibs)
# FIR
fir = BuildExample('./bin/fir','./obj/fir.o', 'src/examples/fir.cpp')
Depends(fir, deplibs)
# sinus
sinus = BuildExample('./bin/sinus','./obj/sinus.o', 'src/examples/sinus.cpp')
Depends(sinus, deplibs)

# morph PD class
if configure.CheckHeader("m_pd.h", language="C") and env['examples']:
    if getPlatform() == 'linux':
       morph = examples.SharedLibrary('./bin/morph~','src/examples/morph_tilde.cpp',  
            SHLIBPREFIX = '', SHLIBSUFFIX= '.pd_linux', CCFLAGS=flags)
    elif getPlatform() == 'macosx':
       morphex = examples.Copy()
       morphex.Append(LINKFLAGS=['-bundle', '-flat_namespace', '-undefined', 'suppress'])
       morpho = morphex.Object('obj/morph_tilde.obj', 'src/examples/morph_tilde.cpp', CCFLAGS=flags)
       morph = morphex.Program('bin/morph~.pd_darwin', 'obj/morph_tilde.obj')
       Depends(morpho, deplibs)
       Depends(morph,morpho)
    elif getPlatform() == 'win':
       pdbin = env['pddir'] + "//bin"
       examples.Append(LIBPATH=Split(pdbin))
       examples.Append(LIBS=Split("pd"))
       morph = examples.SharedLibrary('./bin/morph~', 'src/examples/morph_tilde.cpp', CCFLAGS=flags)       
    Depends(morph, deplibs)

# LADSPA plugin example
if configure.CheckHeader("ladspa.h", language="C") and getPlatform() == 'linux' and env['examples']:
   ladspa_srcs = ['src/examples/Ladspaplug.cpp', 'src/examples/ladspa_example.cpp']
   ladspa = examples.SharedLibrary('bin/ladspaex', ladspa_srcs, CCFLAGS=flags)   
   Depends(ladspa, deplibs)


######################################################################
#
# install

pydest = env['instdir'] + distutils.sysconfig.get_python_lib()
prefix = env['instdir'] + env['prefix']
print env['instdir']

if not msvctools:

  if getPlatform() == 'macosx':
    libdest = prefix+'/lib/libsndobj.dylib'
    inst = env.Command('libsndobj.dylib', sndobjlib, "cp ./lib/libsndobj.dylib .;install_name_tool -id %s %s" % (libdest, 'libsndobj.dylib'))
    env.InstallAs(libdest, inst)
    if env['pythonmodule']:
     pytems = [ 'sndobj.py', '_sndobj.so']
     for i in pytems: 
       env.Install(pydest,os.path.join('python/',i))

  elif getPlatform() == 'win' or getPlatform() == 'cygwin':
   if not msvctools:
    libdest = prefix+'/lib/libsndobj.a'
    env.InstallAs(libdest, sndobjlib)
    if separateLibs:
         rfftwlibdest = prefix+'/lib/librfftw.a'
         env.InstallAs(rfftwlibdest, rfftwlib)

  # Linux or other OSs (unix-like)
  else: 
    libdest = prefix + '/lib/libsndobj.so'
    env.InstallAs(libdest + '.' + version, sndobjlib)
    env.InstallAs(libdest, sndobjlink)
    if env['pythonmodule']:
     print "installing python module in %s" % pydest
     pytems = [ 'sndobj.py', '_sndobj.so']
     for i in pytems:
        env.InstallAs(os.path.join(pydest, i),os.path.join('python', i))
     #licensedest = prefix + '/share/SndObj/License.txt'
     #env.InstallAs(licensedest, 'License.txt')

  if not env['nostaticlib']:
	env.Install(libdest, sndobjliba)
  incdest = prefix + '/include/SndObj/'
  headers = map(lambda x: './include/SndObj/' + x, os.listdir('./include/SndObj'))
  for header in headers:
    #  env.Execute(Chmod(header, 0555)
    if(header != './include/SndObj/CVS'):
  	env.Install(incdest, header)
  rfftw_headers = map(lambda x: './include/rfftw/' + x, os.listdir('./include/rfftw'))
  rfftw_incdest = prefix + '/include/rfftw/'
  for header in rfftw_headers:
    #	env.Execute(Chmod(header, 0555)
    if(header != './include/rfftw/CVS'):
  	env.Install(rfftw_incdest, header)
  if getPlatform() == 'win':
   other_headers = map(lambda x: './include/' + x, os.listdir('./include/'))
   other_incdest = prefix + '/include/'
   for header in other_headers:
     #  env.Execute(Chmod(header, 0555)
     if(header != './include/rfftw'):
       if(header != './include/CVS'):
         if(header != './include/SndObj'):
  	   env.Install(other_incdest, header)

env.Alias('install', [prefix,pydest]) 
