%module sndobj
%{

#ifndef NOPTHREAD
#include "SndThread.h" // needs pthread library
#endif  

// Base Classes
#include "SndObj.h"
#include "SndIO.h" 
#include "Table.h"
// SndObj-derived
#include "Oscil.h"    // Oscillators
#include "Oscilt.h"
#include "Oscili.h"
#include "FastOsc.h"
#include "Osc.h"
#include "Osci.h"
#include "PhOscili.h"

#include "SndIn.h"    // Sound input
#include "SndRead.h"  // audio file input

#if defined(OSS) || defined(SGI) || defined(WIN)
#include "MidiIn.h"   // Midi input
#include  "Bend.h"    // pitch bend
#include "MidiMap.h" 
#endif

#include "ADSR.h"     // Envelopes
#include "IADSR.h" 
#include "Buzz.h"     // Buzzer
#include "Balance.h"  // Balance of signals
#include "DelayLine.h" // Delay line
#include  "Tap.h"      // Truncating tap
#include  "Tapi.h"     // Time-varying tap
#include  "Comb.h"     // Comb filter
#include  "Allpass.h"  // Allpass filter
#include  "StringFlt.h" // String filter
#include   "Pluck.h"    // Karplus-Strong
#include   "VDelay.h"   // Variable delay
#include   "Pitch.h"    // Pitch transposer
#include   "Loop.h"     // Looping
#include   "Fir.h"      // direct convolution
#include   "Filter.h"    // Fixed-freq/BW reson
#include   "TpTz.h"      // Two-pole Two-zero
#include    "Reson.h"    // Variable reson
#include    "Lp.h"       // Variable LP with resonance
#include    "ButtBP.h"   // Butterworth filters
#include    "ButtBR.h" 
#include    "ButtHP.h" 
#include    "ButtLP.h" 
#include    "Ap.h"       // 2nd order all-pass
#include    "LowPass.h"  // 1st order LP
#include    "HiPass.h"   // 1st order HP
#include    "Hilb.h"     // Hilbert transformer
#include    "SyncGrain.h" // granular synthesis
#include    "Mix.h"      // Mixer
#include    "Pan.h"     // panning
#include    "Gain.h"    // gain 
#include    "Interp.h"  // curve segments
#include    "Phase.h"    // phase accumulator
#include    "Ring.h"     // general-purpose multiplier
#include    "Unit.h"     // test signals
#include   "Lookup.h"     // table lookup
#include   "Lookupi.h"  
#include  "Rand.h"     // Noise
#include  "Randh.h"    // Band-limited noise
#include  "Randi.h"    // interpolated

// Spectral stuff
#include "FFT.h"        // windowed overlapping FFT
#include "IFFT.h"       // overlap-add IFFT
#include "PVA.h"        // pvoc analysis/synthesis
#include "PVS.h" 
#include "PVRead.h"                
#include "IFGram.h"
#include "SinAnal.h"    // sinusoidal analysis
#include "SinSyn.h"     // sinusoidal resynthesis
#include "AdSyn.h"		// additive resynthesis
#include "ReSyn.h"      // additive resynthesis
#include  "IFAdd.h"      // additive resynthesis
#include  "SpecMult.h"    // spectral multiplication
#include  "SpecInterp.h"  // spectral interpolation
#include  "PVMask.h"	  // spectral masking
#include   "PVTransp.h"  // transposition
#include   "PVMix.h"     // mixing
#include   "PVBlur.h"    // blurring
#include   "PVFilter.h"    // mag filtering
#include  "PVMorph.h"     // pvoc morphing 
#include  "SpecPolar.h"  // polar converstion
#include  "SpecSplit.h"  // polar conversion & split
#include  "SpecThresh.h" // threshold filter
#include  "SpecVoc.h"    // impose magnitudes
#include  "SpecCart.h"   // cartesian conversion
#include  "SpecCombine.h" // combine phases & mags
#include   "SpecIn.h"   // spectral file input
#include "Convol.h"     // table-based convolution

// SndIO-derived
#include "SndFIO.h"   // Raw file IO 
#include "SndWave.h"  // RIFF-Wave
#include "SndWaveX.h" // waveformatextensible
#include "SndPVOCEX.h" // pvocex
#include "SndSinIO.h"  // sinusex
#include "SndAiff.h"  // AIFF
#include "SndBuffer.h" // memory buffer
 
#if defined(OSS) || defined(SGI) || defined(WIN)
#include "SndMidi.h"  // midi IO
#include "SndMidiIn.h"
#endif

#include "SndRTIO.h" // WinMME/OSS/SGI RT IO
#ifdef _MBCS
#include "SndAsio.h" // ASIO-driver IO
#endif
#ifdef JACK
#include "SndJackIO.h" // Jack IO
#endif
#ifdef MACOSX
#include "SndCoreAudio.h" // Core Audio support
#endif

// Table-derived 
#include "HarmTable.h"    // wavetables
#include "UsrHarmTable.h"
#include "TrisegTable.h"  // envelope
#include  "EnvTable.h"    // envelope curves
#include "SndTable.h"     // soundfile input
#include "PlnTable.h"     // Polynomials
#include "HammingTable.h" // Windows
#include "NoteTable.h"    // midi note conversion
#include "UsrDefTable.h"  // user-definable
#include "LoPassTable.h"    // lowpass impulse response 
#include "SpecEnvTable.h"    // spectral envelope
#include "PVEnvTable.h"      // PV envelope
#include "PVTable.h"         // PV  frame
#include "ImpulseTable.h"    // linear FIR coeffs 

%}

%insert("lisphead") %{

(defpackage :sndobj
  (:use :common-lisp :cffi))

(in-package #:sndobj)

(defvar *libsndobj*
  (let ((type #+(or darwin macos macosx) "dylib"
              #+(or linux linux-target (and unix pc386) freebsd) "so"
              #+(or win32 microsoft-32 cygwin) "dll")
        (paths (list (concatenate 'string (namestring (make-pathname :directory (pathname-directory *load-pathname*))) "./"))))
    (loop for d in paths
       for p = (make-pathname :name "SndObj_wrapper" :type type
			      :directory d
                              :defaults d)

       when (probe-file p) do (return p)
       finally  
         (error "Library \"sndobj_wrapper.~A\" not found. Fix *libsndobj*."
                type))))

(ccl::open-shared-library (namestring *libsndobj*))

(defctype :sndobj :pointer)
(defctype :sndobj_sndobj :pointer)
(defctype :sndobj_sndio :pointer)
(defctype :sndobj_table :pointer)
(defctype :sndobj_oscil :pointer)
(defctype :sndobj_oscilt :pointer)
(defctype :sndobj_oscili :pointer)
(defctype :sndobj_phoscili :pointer)
(defctype :sndobj_fastosc :pointer)
(defctype :sndobj_osc :pointer)
(defctype :sndobj_osci :pointer)
(defctype :sndobj_sndin :pointer)
(defctype :sndobj_sndread :pointer)
(defctype :sndobj_adsr :pointer)
(defctype :sndobj_iadsr :pointer)
(defctype :sndobj_buzz :pointer)
(defctype :sndobj_balance :pointer)
(defctype :sndobj_delayline :pointer)
(defctype :sndobj_tap :pointer)
(defctype :sndobj_tapi :pointer)
(defctype :sndobj_comb :pointer)
(defctype :sndobj_allpass :pointer)
(defctype :sndobj_stringflt :pointer)
(defctype :sndobj_pluck :pointer)
(defctype :sndobj_vdelay :pointer)
(defctype :sndobj_pitch :pointer)
(defctype :sndobj_loop :pointer)
(defctype :sndobj_fir :pointer)
(defctype :sndobj_filter :pointer)
(defctype :sndobj_tptz :pointer)
(defctype :sndobj_reson :pointer)
(defctype :sndobj_lp :pointer)
(defctype :sndobj_buttbp :pointer)
(defctype :sndobj_buttbr :pointer)
(defctype :sndobj_butthp :pointer)
(defctype :sndobj_buttlp :pointer)
(defctype :sndobj_ap :pointer)
(defctype :sndobj_lopass :pointer)
(defctype :sndobj_hipass :pointer)
(defctype :sndobj_hilb :pointer)
(defctype :sndobj_syncgrain :pointer)
(defctype :sndobj_mix :pointer)
(defctype :sndobj_pan :pointer)
(defctype :sndobj_gain :pointer)
(defctype :sndobj_interp :pointer)
(defctype :sndobj_phase :pointer)
(defctype :sndobj_ring :pointer)
(defctype :sndobj_unit :pointer)
(defctype :sndobj_lookup :pointer)
(defctype :sndobj_lookupi :pointer)
(defctype :sndobj_rand :pointer)
(defctype :sndobj_randh :pointer)
(defctype :sndobj_randi :pointer)
(defctype :sndobj_fft :pointer)
(defctype :sndobj_ifft :pointer)
(defctype :sndobj_pva :pointer)
(defctype :sndobj_pvs :pointer)
(defctype :sndobj_pvread :pointer)
(defctype :sndobj_ifgram :pointer)
(defctype :sndobj_sinanal :pointer)
(defctype :sndobj_sinsyn :pointer)
(defctype :sndobj_resyn :pointer)
(defctype :sndobj_adsyn :pointer)
(defctype :sndobj_ifadd :pointer)
(defctype :sndobj_specmult :pointer)
(defctype :sndobj_specinterp :pointer)
(defctype :sndobj_pvmask :pointer)
(defctype :sndobj_pvtransp :pointer)
(defctype :sndobj_pvmix :pointer)
(defctype :sndobj_pvblur :pointer)
(defctype :sndobj_pvfilter :pointer)
(defctype :sndobj_pvmorph :pointer)
(defctype :sndobj_specpolar :pointer)
(defctype :sndobj_specsplit :pointer)
(defctype :sndobj_specthresh :pointer)
(defctype :sndobj_specvoc :pointer)
(defctype :sndobj_speccart :pointer)
(defctype :sndobj_speccombine :pointer)
(defctype :sndobj_specin :pointer)
(defctype :sndobj_convol :pointer)
(defctype :sndobj_sndfio :pointer)
(defctype :sndobj_sndwave :pointer)
(defctype :sndobj_sndwavex :pointer)
(defctype :sndobj_sndpvocex :pointer)
(defctype :sndobj_sndsinio :pointer)
(defctype :sndobj_sndaiff :pointer)
(defctype :sndobj_sndbuffer :pointer)
(defctype :sndobj_sndcoreaudio :pointer)
(defctype :sndobj_harmtable :pointer)
(defctype :sndobj_usrharmtable :pointer)
(defctype :sndobj_trisegtable :pointer)
(defctype :sndobj_envtable :pointer)
(defctype :sndobj_sndtable :pointer)
(defctype :sndobj_plntable :pointer)
(defctype :sndobj_hammingtable :pointer)
(defctype :sndobj_notetable :pointer)
(defctype :sndobj_usrdeftable :pointer)
(defctype :sndobj_lopasstable :pointer)
(defctype :sndobj_pvenvtable :pointer)
(defctype :sndobj_specenvtable :pointer)
(defctype :sndobj_pvtable :pointer)
(defctype :sndobj_impulsetable :pointer)
(defctype :float* :pointer)
(defctype :char* :pointer)
(defctype :double* :pointer)

%}


%nodefaultctor;
%nodefaultdtor;

%feature("compactdefaultargs");

%clear bool;

%typemap(ctype) bool "bool";
%typemap(ctype) bool "$1_ltype";
%typemap(in) bool "$1 = $input;";
%typemap(out) bool  "$result = $1;";
%typemap(ctype) int64 "$1_ltype";
%typemap(in) int64 "$1 = $input;";
%typemap(out) int64 "$result = $1;";
%typemap(ctype) uint64 "$1_ltype"
%typemap(in) uint64 "$1 = $input;";
%typemap(out) uint64 "$result = $1;";

%typemap(cin) bool ":boolean";
%typemap(cout) bool ":boolean";

%typemap(cin) float* ":float*";
%typemap(cin) double* ":double*";
%typemap(cin) int* ":int*";
%typemap(cin) uint* ":uint*";
%typemap(cin) int64* ":int64*";
%typemap(cin) uint64* ":uint64*";
//%typemap(cin) char* ":char*";

%typemap(cin) float& ":float&";
%typemap(cin) double& ":double&";
%typemap(cin) int& ":int&";
%typemap(cin) uint& ":uint&";
%typemap(cin) int64& ":int64&";
%typemap(cin) uint64& ":uint64&";


//%ignore DoProcess(); 



// SndObj

%typemap(cin) SndObj ":sndobj";
%typemap(cout) SndObj ":sndobj";
%typemap(cin) SndObj* ":sndobj";
%typemap(cout) SndObj* ":sndobj";


%rename("SndObj_empty") SndObj();
//%ignore SndObj::SndObj(SndObj &);

%rename("SndObjEqualSndObj") SndObj::operator=(SndObj obj);
%rename("SndObjSumAssignSndObj") SndObj::operator+=(SndObj& obj);
%rename("SndObjSubtractAssignSndObj") SndObj::operator-=(SndObj& obj);
%rename("SndObjMultiplyAssignSndObj") SndObj::operator*=(SndObj& obj);
%rename("SndObjSumAssignFloat") SndObj::operator+=(float val);
%rename("SndObjSubtractAssignFloat") SndObj::operator-=(float val);
%rename("SndObjMultiplyAssignFloat") SndObj::operator*=(float val);
%rename("SndObjSumSndObj") SndObj::operator+(SndObj& obj);
%rename("SndObjSubtractSndObj") SndObj::operator-(SndObj& obj);
%rename("SndObjMultiplySndObj") SndObj::operator*(SndObj& obj);
%rename("SndObjSumFloat") SndObj::operator+(float val);
%rename("SndObjSubtractFloat") SndObj::operator-(float val);
%rename("SndObjMultiplyFloat") SndObj::operator*(float val);


%rename("SndObjShiftRightSndIO") SndObj::operator>>(SndIO& out);
%rename("SndObjShiftLeftSndIO") SndObj::operator<<(SndIO& in);
%rename("SndObjShiftLeftFloat") SndObj::operator<<(float val);
%rename("SndObjShiftLeftFloatVector") SndObj::operator<<(float *vector);


%include"SndObj.h"

// SndIO
%typemap(cin) SndIO ":sndobj_sndio";
%typemap(cout) SndIO ":sndobj_sndio";
%typemap(cin) SndIO* ":sndobj_sndio";
%typemap(cout) SndIO* ":sndobj_sndio";

%ignore SndIO::Output(int pos);

%include"SndIO.h" 

// Table

%typemap(cin) Table ":sndobj_table";
%typemap(cout) Table ":sndobj_table";
%typemap(cin) Table* ":sndobj_table";
%typemap(cout) Table* ":sndobj_table";

%include"Table.h"


// SndObj-derived

// Oscil
%typemap(cin) Oscil ":sndobj_oscil";
%typemap(cout) Oscil ":sndobj_oscil";
%typemap(cin) Oscil* ":sndobj_oscil";
%typemap(cout) Oscil* ":sndobj_oscil";

%rename("Oscil_empty") Oscil();
%rename("SetFreqSndObj")  Oscil::SetFreq(SndObj* inputfr);
%rename("SetAmpSndObj")  Oscil::SetAmp(SndObj* inputamp);

%include"Oscil.h"    // Oscillators

// Oscilt

%typemap(cin) Oscilt ":sndobj_oscilt";
%typemap(cout) Oscilt ":sndobj_oscilt";
%typemap(cin) Oscilt* ":sndobj_oscilt";
%typemap(cout) Oscilt* ":sndobj_oscilt";

%rename("Oscilt_empty") Oscilt();

%include"Oscilt.h"

// Oscili

%typemap(cin) Oscili ":sndobj_oscili";
%typemap(cout) Oscili ":sndobj_oscili";
%typemap(cin) Oscili* ":sndobj_oscili";
%typemap(cout) Oscili* ":sndobj_oscili";

%rename("Oscili_empty") Oscili();

%include"Oscili.h"

// FastOsc

%typemap(cin) FastOsc ":sndobj_fastosc";
%typemap(cout) FastOsc ":sndobj_fastosc";
%typemap(cin) FastOsc* ":sndobj_fastosc";
%typemap(cout) FastOsc* ":sndobj_fastosc";

%rename("FastOsc_empty") FastOsc();

%include"FastOsc.h"

// Osc

%typemap(cin) Osc ":sndobj_osc";
%typemap(cout) Osc ":sndobj_osc";
%typemap(cin) Osc* ":sndobj_osc";
%typemap(cout) Osc* ":sndobj_osc";

%rename("Osc_empty") Osc();

%include"Osc.h"

// Osci

%typemap(cin) Osci ":sndobj_osci";
%typemap(cout) Osci ":sndobj_osci";
%typemap(cin) Osci* ":sndobj_osci";
%typemap(cout) Osci* ":sndobj_osci";

%rename("Osci_empty") Osci();

%include"Osci.h"

// SndIn
%typemap(cin) SndIn ":sndobj_sndin";
%typemap(cout) SndIn ":sndobj_sndin";
%typemap(cin) SndIn* ":sndobj_sndin";
%typemap(cout) SndIn* ":sndobj_sndin";

%rename("SndIn_empty") SndIn();

%include"SndIn.h"    // Sound input

// SndRead

%typemap(cin) SndRead ":sndobj_sndread";
%typemap(cout) SndRead ":sndobj_sndread";
%typemap(cin) SndRead* ":sndobj_sndread";
%typemap(cout) SndRead* ":sndobj_sndread";

%rename("SndRead_empty") SndRead();

%include"SndRead.h"  // audio file input


// ADSR
%typemap(cin) ADSR ":sndobj_adsr";
%typemap(cout) ADSR ":sndobj_adsr";
%typemap(cin) ADSR* ":sndobj_adsr";
%typemap(cout) ADSR* ":sndobj_adsr";

%rename("ADSR_empty") ADSR();

%include"ADSR.h"     // Envelopes

// IADSR

%typemap(cin) IADSR ":sndobj_iadsr";
%typemap(cout) IADSR ":sndobj_iadsr";
%typemap(cin) IADSR* ":sndobj_iadsr";
%typemap(cout) IADSR* ":sndobj_iadsr";

%rename("IADSR_empty") IADSR();

%include"IADSR.h" 

// Buzz

%typemap(cin) Buzz ":sndobj_buzz";
%typemap(cout) Buzz ":sndobj_buzz";
%typemap(cin) Buzz* ":sndobj_buzz";
%typemap(cout) Buzz* ":sndobj_buzz";

%rename("Buzz_empty") Buzz();

%include"Buzz.h"     // Buzzer

// Balance

%typemap(cin) Balance ":sndobj_balance";
%typemap(cout) Balance ":sndobj_balance";
%typemap(cin) Balance* ":sndobj_balance";
%typemap(cout) Balance* ":sndobj_balance";

%rename("Balance_empty") Balance();

%include"Balance.h"  // Balance of signals

// DelayLine

%typemap(cin) DelayLine ":sndobj_delayLine";
%typemap(cout) DelayLine ":sndobj_delayLine";
%typemap(cin) DelayLine* ":sndobj_delayLine";
%typemap(cout) DelayLine* ":sndobj_delayLine";

%rename("DelayLine_empty") DelayLine();

%include"DelayLine.h" // Delay line

// Tap

%typemap(cin) Tap ":sndobj_tap";
%typemap(cout) Tap ":sndobj_tap";
%typemap(cin) Tap* ":sndobj_tap";
%typemap(cout) Tap* ":sndobj_tap";

%rename("Tap_empty") Tap();

%include "Tap.h"      // Truncating tap

// Tapi

%typemap(cin) Tapi ":sndobj_tapi";
%typemap(cout) Tapi ":sndobj_tapi";
%typemap(cin) Tapi* ":sndobj_tapi";
%typemap(cout) Tapi* ":sndobj_tapi";

%rename("Tapi_empty") Tapi();

%include "Tapi.h"     // Time-varying tap

// Comb

%typemap(cin) Comb ":sndobj_comb";
%typemap(cout) Comb ":sndobj_comb";
%typemap(cin) Comb* ":sndobj_comb";
%typemap(cout) Comb* ":sndobj_comb";

%rename("Comb_empty") Comb();

%include "Comb.h"     // Comb filter

// Allpass

%typemap(cin) Allpass ":sndobj_allpass";
%typemap(cout) Allpass ":sndobj_allpass";
%typemap(cin) Allpass* ":sndobj_allpass";
%typemap(cout) Allpass* ":sndobj_allpass";

%rename("Allpass_empty") Allpass();

%include "Allpass.h"  // Allpass filter

// StringFlt

%typemap(cin) StringFlt ":sndobj_stringflt";
%typemap(cout) StringFlt ":sndobj_stringflt";
%typemap(cin) StringFlt* ":sndobj_stringflt";
%typemap(cout) StringFlt* ":sndobj_stringflt";

%rename("StringFlt_empty") StringFlt();
%rename("StringFlt_decay") StringFlt(float fr, SndObj* inObj, float decay, SndObj* InFrObj=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);

%include "StringFlt.h" // String filter

// Pluck

%typemap(cin) Pluck ":sndobj_pluck";
%typemap(cout) Pluck ":sndobj_pluck";
%typemap(cin) Pluck* ":sndobj_pluck";
%typemap(cout) Pluck* ":sndobj_pluck";

%rename("Pluck_empty") Pluck();%rename("Pluck_decay") Pluck(float fr, float amp, SndObj* InFrObj=0, float decay=20.f,float maxscale=32767.f, int vecsize=DEF_VECSIZE, float sr=DEF_SR);

%include  "Pluck.h"    // Karplus-Strong

// VDelay

%typemap(cin) VDelay ":sndobj_vdelay";
%typemap(cout) VDelay ":sndobj_vdelay";
%typemap(cin) VDelay* ":sndobj_vdelay";
%typemap(cout) VDelay* ":sndobj_vdelay";

%rename("VDelay_empty") VDelay();
%rename("VDelay_delaytime") VDelay(float maxdelaytime, float delaytime, float fdbgain, float fwdgain, float dirgain, SndObj* InObj, SndObj* InVdtime = 0, SndObj* InFdbgain=0, SndObj* InFwdgain=0, SndObj* InDirgain=0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);


%include  "VDelay.h"   // Variable delay

// Pitch

%typemap(cin) Pitch ":sndobj_pitch";
%typemap(cout) Pitch ":sndobj_pitch";
%typemap(cin) Pitch* ":sndobj_pitch";
%typemap(cout) Pitch* ":sndobj_pitch";

%rename("Pitch_empty") Pitch();
%rename("Pitch_semitones") Pitch(float delaytime, SndObj* InObj, int semitones = 0, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
%rename("SetPitch_semitones") Pitch::SetPitch(int semitones);


%include  "Pitch.h"    // Pitch transposer

// Loop

%typemap(cin) Loop ":sndobj_loop";
%typemap(cout) Loop ":sndobj_loop";
%typemap(cin) Loop* ":sndobj_loop";
%typemap(cout) Loop* ":sndobj_loop";

%rename("SndLoop_empty") SndLoop();

%include  "Loop.h"     // Looping

// Fir

%typemap(cin) FIR ":sndobj_fir";
%typemap(cout) FIR ":sndobj_fir";
%typemap(cin) FIR* ":sndobj_fir";
%typemap(cout) FIR* ":sndobj_fir";

%rename("Fir_empty") FIR();%rename("FIR") FIR(Table* coeftable, SndObj* input, int vecsize=DEF_VECSIZE, float sr=DEF_SR);
%rename("FIR_impulse") FIR(float* impulse, int impulsesize, SndObj* input, int vecsize=DEF_VECSIZE, float sr=DEF_SR);

%include  "Fir.h"      // direct convolution

// Filter

%typemap(cin) Filter ":sndobj_filter";
%typemap(cout) Filter ":sndobj_filter";
%typemap(cin) Filter* ":sndobj_filter";
%typemap(cout) Filter* ":sndobj_filter";

%rename("Filter_empty") Filter();

%include  "Filter.h"    // Fixed-freq/BW reson

// TpTz

%typemap(cin) TpTz ":sndobj_tptz";
%typemap(cout) TpTz ":sndobj_tptz";
%typemap(cin) TpTz* ":sndobj_tptz";
%typemap(cout) TpTz* ":sndobj_tptz";

%rename("TpTz_empty") TpTz();

%include  "TpTz.h"      // Two-pole Two-zero

// Reson

%typemap(cin) Reson ":sndobj_reson";
%typemap(cout) Reson ":sndobj_reson";
%typemap(cin) Reson* ":sndobj_reson";
%typemap(cout) Reson* ":sndobj_reson";

%rename("Reson_empty") Reson();

%include   "Reson.h"    // Variable reson

// Lp

%typemap(cin) Lp ":sndobj_lp";
%typemap(cout) Lp ":sndobj_lp";
%typemap(cin) Lp* ":sndobj_lp";
%typemap(cout) Lp* ":sndobj_lp";

%rename("Lp_empty") Lp();

%include   "Lp.h"       // Variable LP with resonance

// ButtBP

%typemap(cin) ButtBP ":sndobj_buttbp";
%typemap(cout) ButtBP ":sndobj_buttbp";
%typemap(cin) ButtBP* ":sndobj_buttbp";
%typemap(cout) ButtBP* ":sndobj_buttbp";

%rename("ButtBP_empty") ButtBP();

%rename("SetFreq_mod") ButtBP::SetFreq(float fr, SndObj* InFrObj);
%rename("SetBW_mod") ButtBP::SetBW(float bw, SndObj* InBWObj);

%include   "ButtBP.h"   // Butterworth filters

// ButtBR

%typemap(cin) ButtBR ":sndobj_buttbr";
%typemap(cout) ButtBR ":sndobj_buttbr";
%typemap(cin) ButtBR* ":sndobj_buttbr";
%typemap(cout) ButtBR* ":sndobj_buttbr";

%rename("ButtBR_empty") ButtBR();

%include   "ButtBR.h" 

// ButtHP

%typemap(cin) ButtHP ":sndobj_butthp";
%typemap(cout) ButtHP ":sndobj_butthp";
%typemap(cin) ButtHP* ":sndobj_butthp";
%typemap(cout) ButtHP* ":sndobj_butthp";

%rename("ButtHP_empty") ButtHP();

%include   "ButtHP.h"

// ButtLP

%typemap(cin) ButtLP ":sndobj_buttlp";
%typemap(cout) ButtLP ":sndobj_buttlp";
%typemap(cin) ButtLP* ":sndobj_buttlp";
%typemap(cout) ButtLP* ":sndobj_buttlp";

%rename("ButtLP_empty") ButtLP();

%include   "ButtLP.h"

// Ap

%typemap(cin) Ap ":sndobj_ap";
%typemap(cout) Ap ":sndobj_ap";
%typemap(cin) Ap* ":sndobj_ap";
%typemap(cout) Ap* ":sndobj_ap";

%rename("Ap_empty") Ap();

%include   "Ap.h"       // 2nd order all-pass

// LowPass

%typemap(cin) LoPass ":sndobj_lopass";
%typemap(cout) LoPass ":sndobj_lopass";
%typemap(cin) LoPass* ":sndobj_lopass";
%typemap(cout) LoPass* ":sndobj_lopass";

%rename("LoPass_empty") LoPass();

%include   "LowPass.h"  // 1st order LP

// HiPass

%typemap(cin) HiPass ":sndobj_hipass";
%typemap(cout) HiPass ":sndobj_hipass";
%typemap(cin) HiPass* ":sndobj_hipass";
%typemap(cout) HiPass* ":sndobj_hipass";

%rename("HiPass_empty") HiPass();

%include   "HiPass.h"   // 1st order HP

// Hilb

%typemap(cin) Hilb ":sndobj_hilb";
%typemap(cout) Hilb ":sndobj_hilb";
%typemap(cin) Hilb* ":sndobj_hilb";
%typemap(cout) Hilb* ":sndobj_hilb";

%rename("Hilb_empty") Hilb();

%include   "Hilb.h"     // Hilbert transformer

// SyncGrain

%typemap(cin) SyncGrain ":sndobj_syncgrain";
%typemap(cout) SyncGrain ":sndobj_syncgrain";
%typemap(cin) SyncGrain* ":sndobj_syncgrain";
%typemap(cout) SyncGrain* ":sndobj_syncgrain";

%rename("SyncGrain_empty") SyncGrain();
%rename("Offset_seconds") SyncGrain::Offset(float secs);

%include   "SyncGrain.h" // granular synthesis

// Mix

%typemap(cin) Mixer ":sndobj_mixer";
%typemap(cout) Mixer ":sndobj_mixer";
%typemap(cin) Mixer* ":sndobj_mixer";
%typemap(cout) Mixer* ":sndobj_mixer";

%rename("Mixer_empty") Mixer();


%include   "Mix.h"      // Mixer

// Pan

%typemap(cin) Pan ":sndobj_pan";
%typemap(cout) Pan ":sndobj_pan";
%typemap(cin) Pan* ":sndobj_pan";
%typemap(cout) Pan* ":sndobj_pan";

%rename("Pan_empty") Pan();

%include   "Pan.h"     // panning

// Gain

%typemap(cin) Gain ":sndobj_gain";
%typemap(cout) Gain ":sndobj_gain";
%typemap(cin) Gain* ":sndobj_gain";
%typemap(cout) Gain* ":sndobj_gain";

%rename("Gain_empty") Gain();

%include   "Gain.h"    // gain 

// Interp

%typemap(cin) Interp ":sndobj_interp";
%typemap(cout) Interp ":sndobj_interp";
%typemap(cin) Interp* ":sndobj_interp";
%typemap(cout) Interp* ":sndobj_interp";

%rename("Interp_empty") Interp();

%include   "Interp.h"  // curve segments

// Phase

%typemap(cin) Phase ":sndobj_phase";
%typemap(cout) Phase ":sndobj_phase";
%typemap(cin) Phase* ":sndobj_phase";
%typemap(cout) Phase* ":sndobj_phase";

%rename("Phase_empty") Phase();

%include   "Phase.h"    // phase accumulator

// Ring

%typemap(cin) Ring ":sndobj_ring";
%typemap(cout) Ring ":sndobj_ring";
%typemap(cin) Ring* ":sndobj_ring";
%typemap(cout) Ring* ":sndobj_ring";

%rename("Ring_empty") Ring();

%include   "Ring.h"     // general-purpose multiplier

// Unit

%typemap(cin) Unit ":sndobj_unit";
%typemap(cout) Unit ":sndobj_unit";
%typemap(cin) Unit* ":sndobj_unit";
%typemap(cout) Unit* ":sndobj_unit";

%rename("Unit_empty") Unit();

%include   "Unit.h"     // test signals

// Lookup

%typemap(cin) Lookup ":sndobj_lookup";
%typemap(cout) Lookup ":sndobj_lookup";
%typemap(cin) Lookup* ":sndobj_lookup";
%typemap(cout) Lookup* ":sndobj_lookup";

%rename("Lookup_empty") Lookup();

%include  "Lookup.h"     // table lookup

// Lookupi

%typemap(cin) Lookupi ":sndobj_lookupi";
%typemap(cout) Lookupi ":sndobj_lookupi";
%typemap(cin) Lookupi* ":sndobj_lookupi";
%typemap(cout) Lookupi* ":sndobj_lookupi";

%rename("Lookupi_empty") Lookupi();

%include  "Lookupi.h"  

// Rand

%typemap(cin) Rand ":sndobj_rand";
%typemap(cout) Rand ":sndobj_rand";
%typemap(cin) Rand* ":sndobj_rand";
%typemap(cout) Rand* ":sndobj_rand";

%rename("Rand_empty") Rand();

%include "Rand.h"     // Noise
//PhOscili
%typemap(cin) PhOscili ":sndobj_phoscili";
%typemap(cout) PhOscili ":sndobj_phoscili";
%typemap(cin) PhOscili* ":sndobj_phoscili";
%typemap(cout) PhOscili* ":sndobj_phoscili";

%rename("PhOscili_empty") PhOscili();
%include "PhOscili.h" 

// Randh

%typemap(cin) Randh ":sndobj_randh";
%typemap(cout) Randh ":sndobj_randh";
%typemap(cin) Randh* ":sndobj_randh";
%typemap(cout) Randh* ":sndobj_randh";

%rename("Randh_empty") Randh();

%include "Randh.h"    // Band-limited noise

// Randi

%typemap(cin) Randi ":sndobj_randi";
%typemap(cout) Randi ":sndobj_randi";
%typemap(cin) Randi* ":sndobj_randi";
%typemap(cout) Randi* ":sndobj_randi";

%rename("Randi_empty") Randi();

%include "Randi.h"    // interpolated

// Spectral stuff

// FFT

%typemap(cin) FFT ":sndobj_fft";
%typemap(cout) FFT ":sndobj_fft";
%typemap(cin) FFT* ":sndobj_fft";
%typemap(cout) FFT* ":sndobj_fft";

%rename("FFT_empty") FFT();

%include "FFT.h"        // windowed overlapping FFT

// IFFT

%typemap(cin) IFFT ":sndobj_ifft";
%typemap(cout) IFFT ":sndobj_ifft";
%typemap(cin) IFFT* ":sndobj_ifft";
%typemap(cout) IFFT* ":sndobj_ifft";

%rename("IFFT_empty") IFFT();

%include "IFFT.h"       // overlap-add IFFT

// PVA 

%typemap(cin) PVA ":sndobj_pva";
%typemap(cout) PVA ":sndobj_pva";
%typemap(cin) PVA* ":sndobj_pva";
%typemap(cout) PVA* ":sndobj_pva";

%rename("PVA_empty") PVA();

%include "PVA.h"        // pvoc analysis/synthesis

// PVS

%typemap(cin) PVS ":sndobj_pvs";
%typemap(cout) PVS ":sndobj_pvs";
%typemap(cin) PVS* ":sndobj_pvs";
%typemap(cout) PVS* ":sndobj_pvs";

%rename("PVS_empty") PVS();

%include "PVS.h" 

// PVRead

%typemap(cin) PVRead ":sndobj_pvread";
%typemap(cout) PVRead ":sndobj_pvread";
%typemap(cin) PVRead* ":sndobj_pvread";
%typemap(cout) PVRead* ":sndobj_pvread";

%rename("PVRead_empty") PVRead();

%include "PVRead.h"

// IFGram

%typemap(cin) IFGram ":sndobj_ifgram";
%typemap(cout) IFGram ":sndobj_ifgram";
%typemap(cin) IFGram* ":sndobj_ifgram";
%typemap(cout) IFGram* ":sndobj_ifgram";

%rename("IFGram_empty") IFGram();
     
%include "IFGram.h"

// SinAnal

%typemap(cin) SinAnal ":sndobj_sinanal";
%typemap(cout) SinAnal ":sndobj_SinAnal";
%typemap(cin) SinAnal* ":sndobj_sinanal";
%typemap(cout) SinAnal* ":sndobj_sinanal";

%rename("SinAnal_empty") SinAnal();

%include "SinAnal.h"    // sinusoidal analysis

// SinSyn

%typemap(cin) SinSyn ":sndobj_sinsyn";
%typemap(cout) SinSyn ":sndobj_sinsyn";
%typemap(cin) SinSyn* ":sndobj_sinsyn";
%typemap(cout) SinSyn* ":sndobj_sinsyn";

%rename("SinSyn_empty") SinSyn();

%include "SinSyn.h"     // sinusoidal resynthesis

// ReSyn

%typemap(cin) ReSyn ":sndobj_resyn";
%typemap(cout) ReSyn ":sndobj_resyn";
%typemap(cin) ReSyn* ":sndobj_resyn";
%typemap(cout) ReSyn* ":sndobj_resyn";

%rename("ReSyn_empty") ReSyn();

%include  "ReSyn.h"      // additive resynthesis

// AdSyn

%typemap(cin) AdSyn ":sndobj_adsyn";
%typemap(cout) AdSyn ":sndobj_adsyn";
%typemap(cin) AdSyn* ":sndobj_adsyn";
%typemap(cout) AdSyn* ":sndobj_adsyn";

%rename("AdSyn_empty") AdSyn();

%include  "AdSyn.h"		// additive resynthesis

// IFAdd

%typemap(cin) IFAdd ":sndobj_ifadd";
%typemap(cout) IFAdd ":sndobj_ifadd";
%typemap(cin) IFAdd* ":sndobj_ifadd";
%typemap(cout) IFAdd* ":sndobj_ifadd";

%rename("IFAdd_empty") IFAdd();

%include   "IFAdd.h"      // additive resynthesis

// SpecMult

%typemap(cin) SpecMult ":sndobj_specmult";
%typemap(cout) SpecMult ":sndobj_specmult";
%typemap(cin) SpecMult* ":sndobj_specmult";
%typemap(cout) SpecMult* ":sndobj_specmult";

%rename("SpecMult_empty") SpecMult();
%rename("SpecMult_table") SpecMult(Table* spectab, SndObj* input1, int vecsize=DEF_FFTSIZE, float sr=DEF_SR);

%include   "SpecMult.h"    // spectral multiplication

// SpecInterp

%typemap(cin) SpecInterp ":sndobj_specinterp";
%typemap(cout) SpecInterp ":sndobj_specinterp";
%typemap(cin) SpecInterp* ":sndobj_specinterp";
%typemap(cout) SpecInterp* ":sndobj_specinterp";

%rename("SpecInterp_empty") SpecInterp();

%include   "SpecInterp.h"  // spectral interpolation

// PVMask

%typemap(cin) PVMask ":sndobj_pvmask";
%typemap(cout) PVMask ":sndobj_pvmask";
%typemap(cin) PVMask* ":sndobj_pvmask";
%typemap(cout) PVMask* ":sndobj_pvmask";

%rename("PVMask_empty") PVMask();
%rename("PVMask_table") PVMask(float maskgain, Table* masktable, SndObj* input, SndObj* inmaskgobj=0, int vecsize=DEF_FFTSIZE, float sr=DEF_SR );
%include   "PVMask.h"	  // spectral masking

// PVTransp

%typemap(cin) PVTransp ":sndobj_pvtransp";
%typemap(cout) PVTransp ":sndobj_pvtransp";
%typemap(cin) PVTransp* ":sndobj_pvtransp";
%typemap(cout) PVTransp* ":sndobj_pvtransp";

%rename("PVTransp_empty") PVTransp();

%include    "PVTransp.h"  // transposition

// PVMix

%typemap(cin) PVMix ":sndobj_pvmix";
%typemap(cout) PVMix ":sndobj_pvmix";
%typemap(cin) PVMix* ":sndobj_pvmix";
%typemap(cout) PVMix* ":sndobj_pvmix";

%rename("PVMix_empty") PVMix();

%include    "PVMix.h"     // mixing

// PVBlur

%typemap(cin) PVBlur ":sndobj_pvblur";
%typemap(cout) PVBlur ":sndobj_pvblur";
%typemap(cin) PVBlur* ":sndobj_pvblur";
%typemap(cout) PVBlur* ":sndobj_pvblur";

%rename("PVBlur_empty") PVBlur();

%include    "PVBlur.h"    // blurring

// PVFilter

%typemap(cin) PVFilter ":sndobj_pvfilter";
%typemap(cout) PVFilter ":sndobj_pvfilter";
%typemap(cin) PVFilter* ":sndobj_pvfilter";
%typemap(cout) PVFilter* ":sndobj_pvfilter";

%rename("PVFilter_empty") PVFilter();
%rename("PVFilter_table") PVFilter(Table* filtertable, SndObj* input, float amnt=1.f, SndObj* amntobj=0, int vecsize=DEF_FFTSIZE, float sr=DEF_SR );


%include    "PVFilter.h"    // mag filtering

// PVMorph

%typemap(cin) PVMorph ":sndobj_pvmorph";
%typemap(cout) PVMorph ":sndobj_pvmorph";
%typemap(cin) PVMorph* ":sndobj_pvmorph";
%typemap(cout) PVMorph* ":sndobj_pvmorph";

%rename("PVMorph_empty") PVMorph();

%include   "PVMorph.h"     // pvoc morphing 

// SpecPolar

%typemap(cin) SpecPolar ":sndobj_specpolar";
%typemap(cout) SpecPolar ":sndobj_specpolar";
%typemap(cin) SpecPolar* ":sndobj_specpolar";
%typemap(cout) SpecPolar* ":sndobj_specpolar";

%rename("SpecPolar_empty") SpecPolar();

%include   "SpecPolar.h"  // polar converstion

// SpecSplit

%typemap(cin) SpecSplit ":sndobj_specsplit";
%typemap(cout) SpecSplit ":sndobj_specsplit";
%typemap(cin) SpecSplit* ":sndobj_specsplit";
%typemap(cout) SpecSplit* ":sndobj_specsplit";

%rename("SpecSplit_empty") SpecSplit();

%include   "SpecSplit.h"  // polar conversion & split

// SpecThresh

%typemap(cin) SpecThresh ":sndobj_specthresh";
%typemap(cout) SpecThresh ":sndobj_specthresh";
%typemap(cin) SpecThresh* ":sndobj_specthresh";
%typemap(cout) SpecThresh* ":sndobj_specthresh";

%rename("SpecThresh_empty") SpecThresh();

%include   "SpecThresh.h" // threshold filter

// SpecVoc

%typemap(cin) SpecVoc ":sndobj_specvoc";
%typemap(cout) SpecVoc ":sndobj_specvoc";
%typemap(cin) SpecVoc* ":sndobj_specvoc";
%typemap(cout) SpecVoc* ":sndobj_specvoc";

%rename("SpecVoc_empty") SpecVoc();

%include   "SpecVoc.h"    // impose magnitudes

// SpecCart

%typemap(cin) SpecCart ":sndobj_speccart";
%typemap(cout) SpecCart ":sndobj_speccart";
%typemap(cin) SpecCart* ":sndobj_speccart";
%typemap(cout) SpecCart* ":sndobj_speccart";

%rename("SpecCart_empty") SpecCart();

%include   "SpecCart.h"   // cartesian conversion

// SpecCombine

%typemap(cin) SpecCombine ":sndobj_speccombine";
%typemap(cout) SpecCombine ":sndobj_speccombine";
%typemap(cin) SpecCombine* ":sndobj_speccombine";
%typemap(cout) SpecCombine* ":sndobj_speccombine";

%rename("SpecCombine_empty") SpecCombine();

%include   "SpecCombine.h" // combine phases & mags

// SpecIn

%typemap(cin) SpecIn ":sndobj_specin";
%typemap(cout) SpecIn ":sndobj_specin";
%typemap(cin) SpecIn* ":sndobj_specin";
%typemap(cout) SpecIn* ":sndobj_specin";

%rename("SpecIn_empty") SpecIn();

%include    "SpecIn.h"   // spectral file input

// Convol

%typemap(cin) Convol ":sndobj_convol";
%typemap(cout) Convol ":sndobj_convol";
%typemap(cin) Convol* ":sndobj_convol";
%typemap(cout) Convol* ":sndobj_convol";

%rename("Convol_empty") Convol();

%include  "Convol.h"     // table-based convolution

// SndIO-derived

// SndFIO

%typemap(cin) SndFIO ":sndobj_sndfio";
%typemap(cout) SndFIO ":sndobj_sndfio";
%typemap(cin) SndFIO* ":sndobj_sndfio";
%typemap(cout) SndFIO* ":sndobj_sndfio";

%rename("SndFIO_empty") SndFIO();
%rename("SetPos_float") SndFIO::SetPos(float pos);

%include  "SndFIO.h"   // Raw file IO 

// SndWave

%typemap(cin) SndWave ":sndobj_sndwave";
%typemap(cout) SndWave ":sndobj_sndwave";
%typemap(cin) SndWave* ":sndobj_sndwave";
%typemap(cout) SndWave* ":sndobj_sndwave";

%rename("SndWave_empty") SndWave();

%include  "SndWave.h"  // RIFF-Wave

// SndWaveX

%typemap(cin) SndWaveX ":sndobj_sndwavex";
%typemap(cout) SndWaveX ":sndobj_sndwavex";
%typemap(cin) SndWaveX* ":sndobj_sndwavex";
%typemap(cout) SndWaveX* ":sndobj_sndwavex";

%rename("SndWaveX_empty") SndWaveX();

%include  "SndWaveX.h" // waveformatextensible

// SndPVOCEX

%typemap(cin) SndPVOCEX ":sndobj_sndpvocex";
%typemap(cout) SndPVOCEX ":sndobj_sndpvocex";
%typemap(cin) SndPVOCEX* ":sndobj_sndpvocex";
%typemap(cout) SndPVOCEX* ":sndobj_sndpvocex";

%rename("SndPVOCEX_empty") SndPVOCEX();

%include  "SndPVOCEX.h" // pvocex

// SndSinIO

%typemap(cin) SndSinIO ":sndobj_sndsinio";
%typemap(cout) SndSinIO ":sndobj_sndsinio";
%typemap(cin) SndSinIO* ":sndobj_sndsinio";
%typemap(cout) SndSinIO* ":sndobj_sndsinio";

%rename("SndSinIO_empty") SndSinIO();

%include  "SndSinIO.h"  // sinusex

// SndAiff

%typemap(cin) SndAiff ":sndobj_sndaiff";
%typemap(cout) SndAiff ":sndobj_sndaiff";
%typemap(cin) SndAiff* ":sndobj_sndaiff";
%typemap(cout) SndAiff* ":sndobj_sndaiff";

%rename("SndAiff_empty") SndAiff();

%include  "SndAiff.h"  // AIFF

// SndBuffer

%typemap(cin) SndBuffer ":sndobj_sndbuffer";
%typemap(cout) SndBuffer ":sndobj_sndbuffer";
%typemap(cin) SndBuffer* ":sndobj_sndbuffer";
%typemap(cout) SndBuffer* ":sndobj_sndbuffer";

%rename("SndBuffer_empty") SndBuffer();

%include  "SndBuffer.h" // memory buffer 

// Table-derived 

// HarmTable

%typemap(cin) HarmTable ":sndobj_harmtable";
%typemap(cout) HarmTable ":sndobj_harmtable";
%typemap(cin) HarmTable* ":sndobj_harmtable";
%typemap(cout) HarmTable* ":sndobj_harmtable";

%rename("HarmTable_empty") HarmTable();

%include  "HarmTable.h"    // wavetables

// UsrHarmTable

%typemap(cin) UsrHarmTable ":sndobj_usrharmtable";
%typemap(cout) UsrHarmTable ":sndobj_usrharmtable";
%typemap(cin) UsrHarmTable* ":sndobj_usrharmtable";
%typemap(cout) UsrHarmTable* ":sndobj_usrharmtable";

%rename("UsrHarmTable_empty") UsrHarmTable();

%include  "UsrHarmTable.h"

// TrisegTable

%typemap(cin) TrisegTable ":sndobj_trisegtable";
%typemap(cout) TrisegTable ":sndobj_trisegtable";
%typemap(cin) TrisegTable* ":sndobj_trisegtable";
%typemap(cout) TrisegTable* ":sndobj_trisegtable";

%rename("TrisegTable_empty") TrisegTable();
%rename("TrisegTable_points") TrisegTable(long L, float* TSPoints, float type = 0.f);
%rename("SetCurve_points") TrisegTable::SetCurve(float* TSPoints, float type = 0.f);

%include  "TrisegTable.h"  // envelope

// EnvTable

%typemap(cin) EnvTable ":sndobj_envtable";
%typemap(cout) EnvTable ":sndobj_envtable";
%typemap(cin) EnvTable* ":sndobj_envtable";
%typemap(cout) EnvTable* ":sndobj_envtable";

%rename("EnvTable_empty") EnvTable();

%include   "EnvTable.h"    // envelope curves

// SndTable

%typemap(cin) SndTable ":sndobj_sndtable";
%typemap(cout) SndTable ":sndobj_sndtable";
%typemap(cin) SndTable* ":sndobj_sndtable";
%typemap(cout) SndTable* ":sndobj_sndtable";

%rename("SndTable_empty") SndTable();

%include  "SndTable.h"     // soundfile input

// PlnTable

%typemap(cin) PlnTable ":sndobj_plntable";
%typemap(cout) PlnTable ":sndobj_plntable";
%typemap(cin) PlnTable* ":sndobj_plntable";
%typemap(cout) PlnTable* ":sndobj_plntable";

%rename("PlnTable_empty") PlnTable();

%include  "PlnTable.h"     // Polynomials

// HammingTable

%typemap(cin) HammingTable ":sndobj_hammingtable";
%typemap(cout) HammingTable ":sndobj_hammingtable";
%typemap(cin) HammingTable* ":sndobj_hammingtable";
%typemap(cout) HammingTable* ":sndobj_hammingtable";

%rename("HammingTable_empty") HammingTable();

%include  "HammingTable.h" // Windows

// NoteTable

%typemap(cin) NoteTable ":sndobj_notetable";
%typemap(cout) NoteTable ":sndobj_notetable";
%typemap(cin) NoteTable* ":sndobj_notetable";
%typemap(cout) NoteTable* ":sndobj_notetable";

%rename("NoteTable_empty") NoteTable();

%include  "NoteTable.h"    // midi note conversion

// UsrDefTable

%typemap(cin) UsrDefTable ":sndobj_usrdeftable";
%typemap(cout) UsrDefTable ":sndobj_usrdeftable";
%typemap(cin) UsrDefTable* ":sndobj_usrdeftable";
%typemap(cout) UsrDefTable* ":sndobj_usrdeftable";

%rename("UsrDefTable_empty") UsrDefTable();

%include  "UsrDefTable.h"  // user-definable

// LoPassTable


%typemap(cin) LoPassTable ":sndobj_lopasstable";
%typemap(cout) LoPassTable ":sndobj_lopasstable";
%typemap(cin) LoPassTable* ":sndobj_lopasstable";
%typemap(cout) LoPassTable* ":sndobj_lopasstable";

%rename("LoPassTable_empty") LoPassTable();

%include  "LoPassTable.h"    // lowpass impulse response 

// PVEnvTable

%typemap(cin) PVEnvTable ":sndobj_pvenvtable";
%typemap(cout) PVEnvTable ":sndobj_pvenvtable";
%typemap(cin) PVEnvTable* ":sndobj_pvenvtable";
%typemap(cout) PVEnvTable* ":sndobj_pvenvtable";

%rename("PVEnvTable_empty") PVEnvTable();

%include  "PVEnvTable.h"      // PV envelope

// SpecEnvTable

%typemap(cin) SpecEnvTable ":sndobj_specenvtable";
%typemap(cout) SpecEnvTable ":sndobj_specenvtable";
%typemap(cin) SpecEnvTable* ":sndobj_specenvtable";
%typemap(cout) SpecEnvTable* ":sndobj_specenvtable";

%rename("SpecEnvTable_empty") SpecEnvTable();

%include  "SpecEnvTable.h"    // spectral envelope

// PVTable

%typemap(cin) PVTable ":sndobj_pvtable";
%typemap(cout) PVTable ":sndobj_pvtable";
%typemap(cin) PVTable* ":sndobj_pvtable";
%typemap(cout) PVTable* ":sndobj_pvtable";

%rename("PVTable_empty") PVTable();

%include  "PVTable.h"         // PV  frame

// ImpulseTable

%typemap(cin) ImpulseTable ":sndobj_impulsetable";
%typemap(cout) ImpulseTable ":sndobj_impulsetable";
%typemap(cin) ImpulseTable* ":sndobj_impulsetable";
%typemap(cout) ImpulseTable* ":sndobj_impulsetable";

%rename("ImpulseTable_empty") ImpulseTable();

%include  "ImpulseTable.h"    // linear FIR coeffs 



%clearnodefaultctor;
%clearnodefaultdtor;

