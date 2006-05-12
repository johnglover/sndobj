// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

#include <stdio.h>
#include <m_pd.h>
#include <SndObj/AudioDefs.h>

extern "C"{
void morph_tilde_setup();
}

static t_class *morph_tilde_class;

struct t_morph_tilde {
    t_object x_obj;
	HammingTable* window;
	SndObj* inobj1;
        SndObj* inobj2;
        PVA*  spec1;
	PVA*  spec2;
	PVS*  synth;
	PVMorph* morph; 
	t_float f;

};

t_int  
*morph_tilde_perform(t_int *w){

t_sample *in1 = (t_sample *) w[1];
t_sample *in2 = (t_sample *) w[2];
t_sample *out = (t_sample *) w[3];
t_int  size = (t_int) w[4];
t_morph_tilde *x = (t_morph_tilde *) w[5];

int pos = x->inobj1->PushIn(in1, size);
          x->inobj2->PushIn(in2, size);
          x->synth->PopOut(out, size);
	  
if(pos == DEF_VECSIZE){

       x->spec1->DoProcess();
       x->spec2->DoProcess();
       x->morph->DoProcess();
       x->synth->DoProcess();
	}
	 
return (w+6);

}

void morph_tilde_dsp(t_morph_tilde *x, t_signal **sp){

  dsp_add(morph_tilde_perform, 5, sp[0]->s_vec,
	sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n, x);

}


void *morph_tilde_new(t_symbol *s, int argc, t_atom *argv){

float sr;
float morpha, morphfr; 
int i; 
t_morph_tilde *x = (t_morph_tilde *) pd_new(morph_tilde_class);
sr = sys_getsr();

switch (argc) {
case 1:
morpha = (atom_getfloat(&argv[0]));
morphfr = 0.f;
break;
case 2:
morpha = (atom_getfloat(&argv[0]));
morphfr = (atom_getfloat(&argv[1]));
break;
default:
morpha = morphfr = 0.f;
}

morpha = morpha < 1 ? (morpha > 0 ? morpha : 0.f)
						: 1.f; 
morphfr = morphfr < 1 ? (morphfr > 0 ? morphfr : 0.f)
						: 1.f; 
inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("frequency factor"));
inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("amplitude factor"));

x->window = new HammingTable(1024, 0.5);
x->inobj1 = new SndObj(0, DEF_VECSIZE, sr);
x->inobj2 = new SndObj(0, DEF_VECSIZE, sr);
x->spec1 = new PVA(x->window, x->inobj1, .5f, DEF_FFTSIZE, DEF_VECSIZE, sr);
x->spec2 = new PVA(x->window, x->inobj2, .5f, DEF_FFTSIZE, DEF_VECSIZE, sr);
x->morph = new PVMorph(morphfr, morpha, x->spec1, x->spec2, 0,0,DEF_FFTSIZE, sr);
x->synth = new PVS(x->window, x->morph, DEF_FFTSIZE, DEF_VECSIZE, sr);
outlet_new(&x->x_obj, &s_signal);
return (void *) x;
}

void morph_tilde_destroy(t_morph_tilde *x){

  
delete x->synth;
delete x->spec1;
delete x->spec2;
delete x->inobj1;
delete x->inobj2;
delete x->window;
  

}

void
morph_tilde_amp(t_morph_tilde *x, t_floatarg amp){
    float morpha = amp < 1 ? (amp > 0 ? amp : 0.f)
						: 1.f;
    x->morph->SetAmpMorph((float) morpha);

}

void
morph_tilde_freq(t_morph_tilde *x, t_floatarg freq){
    float morphfr = freq < 1 ? (freq > 0 ? freq : 0.f)
						: 1.f; 
    x->morph->SetFreqMorph((float) morphfr);
}


void morph_tilde_setup(void) {
morph_tilde_class = class_new(gensym("morph~"),
							(t_newmethod)morph_tilde_new,
							(t_method)morph_tilde_destroy, 
							sizeof(t_morph_tilde),
							CLASS_DEFAULT,
						A_GIMME, 0);

class_addmethod(morph_tilde_class, (t_method) morph_tilde_dsp, 
				gensym("dsp"), (t_atomtype) 0);
class_addmethod(morph_tilde_class, (t_method) morph_tilde_amp,
				gensym("amplitude factor"), A_DEFFLOAT, 0);
class_addmethod(morph_tilde_class, (t_method) morph_tilde_freq,
				gensym("frequency factor"), A_DEFFLOAT, 0);

CLASS_MAINSIGNALIN(morph_tilde_class,t_morph_tilde,f);
 post("\nmorph~ 1.0\n Based on SndObj library spectral classes");
 post("(c) V Lazzarini, 2004\n");
}








