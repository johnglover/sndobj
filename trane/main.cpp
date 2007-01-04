#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Group.H>
#include <stdio.h>
#include "Instrument.h"

struct InstData {
  Instrument trane;
  Fl_Value_Slider *str_fr[4], *loop_gain[4];
  Fl_Dial *str_gain[4], *decay[4];
  Fl_Light_Button *str_bt[4], *loop_bt[4];
  Fl_Button *resamp_bt[4];
};

static void fr_callback(Fl_Widget* o, void* d) {
  InstData *p = (InstData *) d;
  for(int i=0; i < 4; i++)
    if(o == p->str_fr[i]){
      p->trane.SetFreq(i,((Fl_Value_Slider *)o)->value());
    }
}

static void str_callback(Fl_Widget* o, void* d) {

  InstData *p = (InstData *) d;
  for(int i=0; i < 4; i++)
    if(o == p->str_bt[i]){
      if(((Fl_Button *)o)->value())
	p->trane.StringOn(i);
      else
	p->trane.StringOff(i);
    }
}

static void loop_callback(Fl_Widget* o, void* d) {
  InstData *p = (InstData *) d;
  for(int i=0; i < 4; i++)
    if(o == p->loop_bt[i]){
      if(((Fl_Button *)o)->value())
	p->trane.LoopOn(i);
      else
	p->trane.LoopOff(i);
    }
}

static void resample_callback(Fl_Widget* o, void *d) {

  InstData *p = (InstData *) d;
  for(int i=0; i < 4; i++)
    if(o == p->resamp_bt[i]) 
      p->trane.ReSample(i);
    
}

static void sgain_callback(Fl_Widget* o, void *d) {
  InstData *p = (InstData *) d;
  for(int i=0; i < 4; i++)
    if(o == p->str_gain[i])
      p->trane.SetStrGain(i,((Fl_Dial *)o)->value());
   
}

static void sdecay_callback(Fl_Widget* o, void *d) {
  InstData *p = (InstData *) d;
  for(int i=0; i < 4; i++)
    if(o == p->decay[i])
      p->trane.SetDec(i,-((Fl_Dial *)o)->value());
   
}
static void lgain_callback(Fl_Widget* o, void *d) {
  InstData *p = (InstData *) d;
  for(int i=0; i < 4; i++)
    if(o == p->loop_gain[i])
      p->trane.SetLoopGain(i,((Fl_Value_Slider *)o)->value());
}

int main(int argc, char **argv) {

  InstData  inst; 
  char mess1[4][10], mess2[4][10];
  int red = fl_rgb_color(200,10,40);
  int redish = fl_rgb_color(180, 60, 60);
  Fl_Window *window = new Fl_Window(460,660, "The Trane Thing Computer Instrument");
  window->color(FL_DARK_BLUE);
  Fl_Group *strings = new Fl_Group(5,15,450,245);
  strings->box(FL_ENGRAVED_BOX);
  strings->color(red);
  strings->end();
  Fl_Group *loops = new Fl_Group(5,270,450,385);
  loops->box(FL_ENGRAVED_BOX);
  loops->color(red);
  loops->end();

  for(int i=0; i < 4; i++) {
    // strings
    sprintf(mess1[i], "string %d", i+1);
    inst.str_bt[i] = new Fl_Light_Button(15,25+i*60, 70, 30, mess1[i]);
    inst.str_bt[i]->type(FL_TOGGLE_BUTTON);
    inst.str_bt[i]->color(redish);
    inst.str_bt[i]->callback((Fl_Callback*)str_callback, (void *) &inst);
    strings->add(inst.str_bt[i]);
    if(i==3)
      inst.str_fr[i] = new Fl_Value_Slider(105, 20+i*60, 230, 40, "frequency");
    else
      inst.str_fr[i] = new Fl_Value_Slider(105, 20+i*60, 230, 40);
    inst.str_fr[i]->range(inst.trane.GetFreq(i),inst.trane.GetFreq(i)*4);
    inst.str_fr[i]->value(inst.trane.GetFreq(i));
    inst.str_fr[i]->type(5);
    inst.str_fr[i]->callback((Fl_Callback*)fr_callback, (void *)&inst);
    inst.str_fr[i]->color(red);
    inst.str_fr[i]->box(FL_FLAT_BOX);
    strings->add(inst.str_fr[i]);
    if(i==3)
      inst.str_gain[i] = new Fl_Dial(355, 20+i*60, 40, 40, "Gain");
    else
      inst.str_gain[i] = new Fl_Dial(355, 20+i*60, 40, 40);
    inst.str_gain[i]->callback((Fl_Callback*)sgain_callback, (void *)&inst);
    inst.str_gain[i]->range(0,1.0);
    inst.str_gain[i]->value(inst.trane.GetStrGain(i));
    inst.str_gain[i]->box(FL_ROUND_UP_BOX);
    strings->add(inst.str_gain[i]);
    if(i==3)
      inst.decay[i] = new Fl_Dial(405, 20+i*60, 40, 40, "Decay");
    else
      inst.decay[i] = new Fl_Dial(405, 20+i*60, 40, 40);
    inst.decay[i]->callback((Fl_Callback*)sdecay_callback, (void *)&inst);
    inst.decay[i]->range(-48.0,-6.0);
    inst.decay[i]->value(-inst.trane.GetDec(i));
    inst.decay[i]->box(FL_ROUND_UP_BOX);
    strings->add(inst.str_gain[i]);

     // loops
    sprintf(mess2[i], "sample %d", i+1);
    inst.loop_bt[i] = new Fl_Light_Button(15+i*115,280, 80, 30, mess2[i]);
    inst.loop_bt[i]->type(FL_TOGGLE_BUTTON);
    inst.loop_bt[i]->color(redish);
    inst.loop_bt[i]->callback((Fl_Callback*)loop_callback, (void *) &inst);
    loops->add(inst.loop_bt[i]);
    inst.loop_gain[i] = new Fl_Value_Slider(35+i*115,330, 40, 250, "gain(dB)");
    inst.loop_gain[i]->range(24,-24);
    inst.loop_gain[i]->color(redish);
    inst.loop_gain[i]->type(FL_VERT_NICE_SLIDER);
    inst.loop_gain[i]->callback((Fl_Callback*)lgain_callback, (void *)&inst);
    loops->add(inst.loop_gain[i]);
    inst.resamp_bt[i] = new Fl_Button(15+i*115,600, 80, 30, "resample");
    inst.resamp_bt[i]->box(FL_ROUND_UP_BOX);
    inst.resamp_bt[i]->type(0);
    inst.resamp_bt[i]->callback((Fl_Callback*)resample_callback, (void *) &inst);
    loops->add(inst.resamp_bt[i]);
  }
  window->end();
  window->show();
  inst.trane.ProcessOn();
  Fl::run();
  return 0;
}
