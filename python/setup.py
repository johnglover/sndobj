from distutils.core import setup, Extension
import os

# detect platform
platform = os.uname()[0] if hasattr(os, 'uname') else 'Windows'

# TODO: Test on more platforms
if platform != 'Darwin':
    print "Warning: This script is untested on your platform."
    print "         You can also install the Python module using the main scons script."

# options
use_asio = False
use_numpy = True

# get numpy include directory
try:
    import numpy
    try:
        numpy_include = numpy.get_include()
    except AttributeError:
        numpy_include = numpy.get_numpy_include()
except ImportError:
    print "Error: Numpy was not found."
    exit(1)

# sources
obj_sources = """
    Oscil.cpp Oscilt.cpp Oscili.cpp 
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
    SpecVoc.cpp  Ptrack.cpp
    """.split()

sndio_sources = """
    SndIO.cpp SndRTIO.cpp SndFIO.cpp 
    SndWave.cpp SndAiff.cpp SndBuffer.cpp 
    SndMidi.cpp SndMidiIn.cpp SndWaveX.cpp 
    SndPVOCEX.cpp SndSinIO.cpp  SndCoreAudio.cpp SndJackIO.cpp 
    """.split()

table_sources = """
    HarmTable.cpp UsrHarmTable.cpp 
    TrisegTable.cpp SndTable.cpp PlnTable.cpp 
    HammingTable.cpp NoteTable.cpp UsrDefTable.cpp 
    LoPassTable.cpp ImpulseTable.cpp 
    SpecEnvTable.cpp  EnvTable.cpp PVEnvTable.cpp PVTable.cpp
    """.split()

sndthr_sources = """SndThread.cpp SndRTThread.cpp""".split()

fftw_sources = """
    config.c  fcr_9.c fhf_6.c fn_8.c  frc_1.c  ftw_16.c ftwi_7.c
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
    fcr_8.c fhf_5.c fn_7.c fni_9.c ftw_10.c ftwi_64.c cfft.c
    """.split()

sndobj_sources = map(lambda x: '../src/' + x, obj_sources + sndio_sources \
    + table_sources + sndthr_sources) 
sndobj_sources.extend(map(lambda x: '../src/rfftw/' + x, fftw_sources))
sndobj_sources.append("AudioDefs.i")
if use_asio:
    sndobj_sources.append("../src/SndASIO.cpp")
    asios =  """iasiothiscallresolver.cpp asiodrivers.cpp asio.cpp asiolist.cpp""".split()
    sndobj_sources.extend(map(lambda x: '../src/asio/' + x, asios))

link_args = [] 
macros = [('PYTHON_WRAP', None)]
swig_opts = ['-c++', '-I../src']
if use_numpy:
    swig_opts.append('-DNUMPY')
include_dirs = [numpy_include, '/usr/local/include', 
    '../include', '../include/rfftw', '../src/'] 

# OS X 
if platform == 'Darwin':
    macros.append(('MACOSX', None))
    link_args.extend(['-framework', 'CoreAudio'])
    include_dirs.append('/system/library/Frameworks/CoreAudio.framework/Headers')

pysndobj = Extension("_sndobj", 
                     sources=sndobj_sources,
                     include_dirs=include_dirs,
                     define_macros=macros,
                     extra_link_args=link_args,
                     swig_opts=swig_opts)

setup(name='SndObj',
      version='2.6.99',
      description='SndObj Library',
      author='Victor Lazzarini',
      author_email='Victor.Lazzarini@nuim.ie',
      url='http://sndobj.sourceforget.net',
      ext_modules=[pysndobj],
      py_modules=['sndobj'])
