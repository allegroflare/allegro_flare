#pragma once


#include <string>
#include <allegro5/allegro.h>



class ControlStrategyBase
{
private:
   std::string type;

public:
   ControlStrategyBase(std::string type="ControlStrategyBase");
   virtual ~ControlStrategyBase();

   virtual void on_activate();
   virtual void on_deactivate();

   virtual void key_up_func(ALLEGRO_EVENT *ev=nullptr);
   virtual void key_down_func(ALLEGRO_EVENT *ev=nullptr);
   virtual void key_char_func(ALLEGRO_EVENT *ev=nullptr);
   virtual void primary_timer_func();
};


