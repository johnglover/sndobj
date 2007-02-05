# Microsoft Developer Studio Project File - Name="SndObj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SndObj - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SndObj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SndObj.mak" CFG="SndObj - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SndObj - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /w /W0 /O2 /I "..\include" /I "." /I "..\include\rfftw" /D "_LIB" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "WIN" /D "WINPTHREAD" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copying files
PostBuild_Cmds=copy release\SndObj.lib ..\lib\SndObj.lib	copy ..\src\*.h ..\include\SndObj
# End Special Build Tool
# Begin Target

# Name "SndObj - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "fftw"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\rfftw\config.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\executor.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_1.c
# ADD CPP /W3
# SUBTRACT CPP /O<none>
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_11.c
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_12.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_128.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_13.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_14.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_15.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_64.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fcr_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fftwnd.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhb_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fhf_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_1.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_11.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_12.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_13.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_14.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_15.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_64.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fn_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_1.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_11.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_12.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_13.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_14.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_15.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_64.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\fni_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_1.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_11.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_12.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_128.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_13.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_14.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_15.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_64.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\frc_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_64.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftw_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_10.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_16.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_3.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_32.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_4.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_5.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_6.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_64.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_7.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_8.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\ftwi_9.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\generic.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\malloc.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\planner.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\putils.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rader.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rconfig.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rexec.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rexec2.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rfftwf77.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rfftwnd.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rgeneric.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\rplanner.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\timer.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\twiddle.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\wisdom.c
# End Source File
# Begin Source File

SOURCE=..\src\rfftw\wisdomio.c
# End Source File
# End Group
# Begin Group "asio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\asio\asio.cpp
# End Source File
# Begin Source File

SOURCE=..\src\asio\asiodrivers.cpp
# End Source File
# Begin Source File

SOURCE=..\src\asio\asiolist.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\ADSR.cpp
# End Source File
# Begin Source File

SOURCE=..\src\AdSyn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Allpass.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Ap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Balance.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Bend.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ButtBP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ButtBR.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ButtHP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ButtLP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Buzz.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Comb.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Convol.cpp
# End Source File
# Begin Source File

SOURCE=..\src\DelayLine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\EnvTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\FastOsc.cpp
# End Source File
# Begin Source File

SOURCE=..\src\FFT.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Filter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Fir.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Gain.cpp
# End Source File
# Begin Source File

SOURCE=..\src\HammingTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\HarmTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Hilb.cpp
# End Source File
# Begin Source File

SOURCE=..\src\HiPass.cpp
# End Source File
# Begin Source File

SOURCE=..\src\IADSR.cpp
# End Source File
# Begin Source File

SOURCE=..\src\IFAdd.cpp
# End Source File
# Begin Source File

SOURCE=..\src\IFFT.cpp
# End Source File
# Begin Source File

SOURCE=..\src\IFGram.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ImpulseTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Interp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Lookup.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Lookupi.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Loop.cpp
# End Source File
# Begin Source File

SOURCE=..\src\LoPassTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\LowPass.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Lp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\MidiIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\MidiMap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\NoteTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Osc.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Osci.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Oscil.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Oscili.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Oscilt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Pan.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Phase.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PhOscili.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Pitch.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PlnTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Pluck.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVA.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVBlur.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVEnvTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVMask.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVMix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVMorph.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVRead.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVS.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PVTransp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Rand.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Randh.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Randi.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Reson.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ReSyn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Ring.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SinAnal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SinSyn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndAiff.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndASIO.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndFIO.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndIO.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndMidi.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndMidiIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndObj.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndPVOCEX.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndRead.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndRTIO.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndSinIO.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndThread.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndWave.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SndWaveX.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecCart.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecCombine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecEnvTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecInterp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecMult.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecPolar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecSplit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecThresh.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SpecVoc.cpp
# End Source File
# Begin Source File

SOURCE=..\src\StringFlt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SyncGrain.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Tap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Tapi.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TpTz.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TrisegTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Unit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\UsrDefTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\UsrHarmTable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\VDelay.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\ADSR.h
# End Source File
# Begin Source File

SOURCE=..\src\AdSyn.h
# End Source File
# Begin Source File

SOURCE=..\src\Allpass.h
# End Source File
# Begin Source File

SOURCE=..\src\Ap.h
# End Source File
# Begin Source File

SOURCE=..\src\AudioDefs.h
# End Source File
# Begin Source File

SOURCE=..\src\Balance.h
# End Source File
# Begin Source File

SOURCE=..\src\Bend.h
# End Source File
# Begin Source File

SOURCE=..\src\ButtBP.h
# End Source File
# Begin Source File

SOURCE=..\src\ButtBR.h
# End Source File
# Begin Source File

SOURCE=..\src\ButtHP.h
# End Source File
# Begin Source File

SOURCE=..\src\ButtLP.h
# End Source File
# Begin Source File

SOURCE=..\src\Buzz.h
# End Source File
# Begin Source File

SOURCE=..\src\Comb.h
# End Source File
# Begin Source File

SOURCE=..\src\Convol.h
# End Source File
# Begin Source File

SOURCE=..\src\DelayLine.h
# End Source File
# Begin Source File

SOURCE=..\src\EnvTable.h
# End Source File
# Begin Source File

SOURCE=..\src\FastOsc.h
# End Source File
# Begin Source File

SOURCE=..\src\FFT.h
# End Source File
# Begin Source File

SOURCE=..\src\Filter.h
# End Source File
# Begin Source File

SOURCE=..\src\Fir.h
# End Source File
# Begin Source File

SOURCE=..\src\Gain.h
# End Source File
# Begin Source File

SOURCE=..\src\HammingTable.h
# End Source File
# Begin Source File

SOURCE=..\src\HarmTable.h
# End Source File
# Begin Source File

SOURCE=..\src\Hilb.h
# End Source File
# Begin Source File

SOURCE=..\src\HiPass.h
# End Source File
# Begin Source File

SOURCE=..\src\IADSR.h
# End Source File
# Begin Source File

SOURCE=..\src\IFAdd.h
# End Source File
# Begin Source File

SOURCE=..\src\IFFT.h
# End Source File
# Begin Source File

SOURCE=..\src\IFGram.h
# End Source File
# Begin Source File

SOURCE=..\src\ImpulseTable.h
# End Source File
# Begin Source File

SOURCE=..\src\Interp.h
# End Source File
# Begin Source File

SOURCE=..\src\Lookup.h
# End Source File
# Begin Source File

SOURCE=..\src\Lookupi.h
# End Source File
# Begin Source File

SOURCE=..\src\Loop.h
# End Source File
# Begin Source File

SOURCE=..\src\LoPassTable.h
# End Source File
# Begin Source File

SOURCE=..\src\LowPass.h
# End Source File
# Begin Source File

SOURCE=..\src\Lp.h
# End Source File
# Begin Source File

SOURCE=..\src\MidiIn.h
# End Source File
# Begin Source File

SOURCE=..\src\MidiMap.h
# End Source File
# Begin Source File

SOURCE=..\src\Mix.h
# End Source File
# Begin Source File

SOURCE=..\src\NoteTable.h
# End Source File
# Begin Source File

SOURCE=..\src\Osc.h
# End Source File
# Begin Source File

SOURCE=..\src\Osci.h
# End Source File
# Begin Source File

SOURCE=..\src\Oscil.h
# End Source File
# Begin Source File

SOURCE=..\src\Oscili.h
# End Source File
# Begin Source File

SOURCE=..\src\Oscilt.h
# End Source File
# Begin Source File

SOURCE=..\src\Pan.h
# End Source File
# Begin Source File

SOURCE=..\src\Phase.h
# End Source File
# Begin Source File

SOURCE=..\src\PhOscili.h
# End Source File
# Begin Source File

SOURCE=..\src\Pitch.h
# End Source File
# Begin Source File

SOURCE=..\src\PlnTable.h
# End Source File
# Begin Source File

SOURCE=..\src\Pluck.h
# End Source File
# Begin Source File

SOURCE=..\src\PVA.h
# End Source File
# Begin Source File

SOURCE=..\src\PVBlur.h
# End Source File
# Begin Source File

SOURCE=..\src\PVEnvTable.h
# End Source File
# Begin Source File

SOURCE=..\src\PVFilter.h
# End Source File
# Begin Source File

SOURCE=..\src\PVMask.h
# End Source File
# Begin Source File

SOURCE=..\src\PVMix.h
# End Source File
# Begin Source File

SOURCE=..\src\PVMorph.h
# End Source File
# Begin Source File

SOURCE=..\src\PVRead.h
# End Source File
# Begin Source File

SOURCE=..\src\PVS.h
# End Source File
# Begin Source File

SOURCE=..\src\PVTable.h
# End Source File
# Begin Source File

SOURCE=..\src\PVTransp.h
# End Source File
# Begin Source File

SOURCE=..\src\Rand.h
# End Source File
# Begin Source File

SOURCE=..\src\Randh.h
# End Source File
# Begin Source File

SOURCE=..\src\Randi.h
# End Source File
# Begin Source File

SOURCE=..\src\Reson.h
# End Source File
# Begin Source File

SOURCE=..\src\ReSyn.h
# End Source File
# Begin Source File

SOURCE=..\src\Ring.h
# End Source File
# Begin Source File

SOURCE=..\src\SinAnal.h
# End Source File
# Begin Source File

SOURCE=..\src\SinSyn.h
# End Source File
# Begin Source File

SOURCE=..\src\SndAiff.h
# End Source File
# Begin Source File

SOURCE=..\src\SndASIO.h
# End Source File
# Begin Source File

SOURCE=..\src\SndBuffer.h
# End Source File
# Begin Source File

SOURCE=..\src\SndFIO.h
# End Source File
# Begin Source File

SOURCE=..\src\SndIn.h
# End Source File
# Begin Source File

SOURCE=..\src\SndIO.h
# End Source File
# Begin Source File

SOURCE=..\src\SndMidi.h
# End Source File
# Begin Source File

SOURCE=..\src\SndMidiIn.h
# End Source File
# Begin Source File

SOURCE=..\src\SndObj.h
# End Source File
# Begin Source File

SOURCE=..\src\SndPVOCEX.h
# End Source File
# Begin Source File

SOURCE=..\src\SndRead.h
# End Source File
# Begin Source File

SOURCE=..\src\SndRTIO.h
# End Source File
# Begin Source File

SOURCE=..\src\SndSinIO.h
# End Source File
# Begin Source File

SOURCE=..\src\SndTable.h
# End Source File
# Begin Source File

SOURCE=..\src\SndThread.h
# End Source File
# Begin Source File

SOURCE=..\src\SndWave.h
# End Source File
# Begin Source File

SOURCE=..\src\SndWaveX.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecCart.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecCombine.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecEnvTable.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecIn.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecInterp.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecMult.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecPolar.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecSplit.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecThresh.h
# End Source File
# Begin Source File

SOURCE=..\src\SpecVoc.h
# End Source File
# Begin Source File

SOURCE=..\src\StringFlt.h
# End Source File
# Begin Source File

SOURCE=..\src\SyncGrain.h
# End Source File
# Begin Source File

SOURCE=..\src\Table.h
# End Source File
# Begin Source File

SOURCE=..\src\Tap.h
# End Source File
# Begin Source File

SOURCE=..\src\Tapi.h
# End Source File
# Begin Source File

SOURCE=..\src\TpTz.h
# End Source File
# Begin Source File

SOURCE=..\src\TrisegTable.h
# End Source File
# Begin Source File

SOURCE=..\src\Unit.h
# End Source File
# Begin Source File

SOURCE=..\src\UsrDefTable.h
# End Source File
# Begin Source File

SOURCE=..\src\UsrHarmTable.h
# End Source File
# Begin Source File

SOURCE=..\src\VDelay.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Makefile
# End Source File
# Begin Source File

SOURCE=..\src\Makefile
# End Source File
# Begin Source File

SOURCE=..\src\Makefile.alsa
# End Source File
# Begin Source File

SOURCE=..\src\Makefile.mosx
# End Source File
# Begin Source File

SOURCE=..\src\Makefile.oss
# End Source File
# Begin Source File

SOURCE=..\src\Makefile.win
# End Source File
# End Target
# End Project
