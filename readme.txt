The Sound Object Library 
========================

The build system has been tested on Linux, OSX and
Windows (under MSVC and mingw; but is untested under cygwin)

Thanks to Tim Blechmann for the original 
SConstruct code.


VL, 2006


Build instructions
------------------

1. Requirements
   a. ANSI C/C++ compilers (such as gcc/g++)
   b. Python (www.python.org)
   c. Scons  (www.scons.org)
   d. For realtime audio: 
      On Linux either OSS (www.4front-tech.com) 
               or AlSA (www.alsa-project.org), 
               and/or JACK (jack.sf.net)
      On OSX and SGI, the library
      uses the supplied system audio drivers.   
      On Windows (under MSVC/mingw) ASIO is also used

2. On the top-level directory, run 'scons'. If on
   Linux and using OSS, add option OSS=true
   
3. For more options, including install directory
   prefix, etc, try 'scons -H' (basic options)
   and 'scons -h' (SndObj-specific options)


Note for OS X 10.6 Users:
-------------------------

To build the Python module for both 32-bit and 64-bit architectures, you may need to call scons with the following argument:

    customCCFLAGS='-arch x86_64 -arch i386 -isysroot /Developer/SDKs/MacOSX10.6.sdk' 
