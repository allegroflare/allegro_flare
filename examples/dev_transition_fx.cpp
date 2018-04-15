///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


#include <allegro5/allegro.h>


namespace TransitionFX
{
   class Base
   {
   private:
      ALLEGRO_BITMAP *display_bitmap;
      ALLEGRO_BITMAP *surface_A;
      ALLEGRO_BITMAP *surface_B;
      float duration;
      float position;
      bool finished;

   public:
      Base(ALLEGRO_BITMAP *display_bitmap);
      ~Base();

      ALLEGRO_BITMAP *get_surface_A();
      ALLEGRO_BITMAP *get_surface_B();

      bool is_finished();

      virtual void draw();
      virtual void update();
   };
};


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


//#include <models/transition_fx/base.hpp>

#include <allegro_flare/color.h>


namespace TransitionFX
{


Base::Base(ALLEGRO_BITMAP *display_bitmap)
   : display_bitmap(display_bitmap)
   , surface_A(al_create_bitmap(al_get_bitmap_width(display_bitmap), al_get_bitmap_height(display_bitmap)))
   , surface_B(al_create_bitmap(al_get_bitmap_width(display_bitmap), al_get_bitmap_height(display_bitmap)))
   , duration(1.0)
   , position(0)
   , finished(false)
{
}


Base::~Base()
{
}


ALLEGRO_BITMAP *Base::get_surface_A()
{
   return surface_A;
}


ALLEGRO_BITMAP *Base::get_surface_B()
{
   return surface_B;
}


bool Base::is_finished()
{
   return finished;
}


void Base::draw()
{
   float alpha = 1.0 - (duration - position) / duration;
   //float alpha = 0.5;
   al_set_target_bitmap(display_bitmap);
   al_draw_bitmap(surface_A, 0, 0, 0);
   al_draw_tinted_bitmap(surface_B, color::color(color::white, alpha), 0, 0, 0);
}


void Base::update()
{
   position += 1.0 / 60.0;
   if (position >= duration) finished = true;
}


} // namespace TransitionFX


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


#include <allegro_flare/allegro_flare.h>
#include <cmath>


#define START_TRANSITION_USER_EVENT ALLEGRO_GET_EVENT_TYPE('x','s','f','d')
#define FINISH_TRANSITION_USER_EVENT ALLEGRO_GET_EVENT_TYPE('!','x','f','d')


class ScreenA : public Screen
{
private:
   TextObject text;
   ALLEGRO_COLOR background_color;

public:
   ScreenA(Display *display) : Screen(display), text("HOWDY"), background_color(color::blue)
   {
      text.font(Framework::font("DroidSans.ttf 300")).color(color::white);
   }
   ~ScreenA() {};

   void primary_timer_func() override
   {
      text.align(0.5, 0.5);
      text.position(display->width()/2, display->height()/2);
      text.rotation(sin(al_get_time())*0.1);
      al_clear_to_color(background_color);
      text.draw();
   }
};


class ScreenB : public Screen
{
private:
   TextObject text;
   ALLEGRO_COLOR background_color;

public:
   ScreenB(Display *display) : Screen(display), text("DOODIE!"), background_color(color::red)
   {
      text.font(Framework::font("DroidSans.ttf 300")).color(color::white);
   }
   ~ScreenB() {}

   void primary_timer_func() override
   {
      text.align(0.5, 0.5);
      text.position(display->width()/2, display->height()/2);
      text.rotation(sin(al_get_time())*-0.12);
      al_clear_to_color(background_color);
      text.draw();
   }
};


class DevTransitionFXScreen : public Screen
{
private:
   ScreenA screen_a;
   ScreenB screen_b;
   TransitionFX::Base *transition_fx;
   //UserEventEmitter user_event_emitter;

public:
   DevTransitionFXScreen(Display *display)
      : Screen(display)
      , screen_a(display)
      , screen_b(display)
      , transition_fx(nullptr)
      //, user_event_emitter()
   {
      UserEventEmitter::emit_event(START_TRANSITION_USER_EVENT);
   }
   ~DevTransitionFXScreen() {}

   void start_transition()
   {
      if (transition_fx) return;
      transition_fx = new TransitionFX::Base(al_get_backbuffer(display->al_display));
      screen_a.create_and_use_backbuffer_sub_bitmap_of(transition_fx->get_surface_A());
      screen_b.create_and_use_backbuffer_sub_bitmap_of(transition_fx->get_surface_B());
   }

   void end_transition()
   {
      if (transition_fx)
      {
         delete transition_fx;
         transition_fx = nullptr;
      }
   }

   void key_down_func() override
   {
      UserEventEmitter::emit_event(START_TRANSITION_USER_EVENT);
   }

   void user_event_func() override
   {
      switch(Framework::current_event->type)
      {
      case START_TRANSITION_USER_EVENT:
         std::cout << "starting crossfade...";
         start_transition();
         std::cout << "done" << std::endl;
         break;
      case FINISH_TRANSITION_USER_EVENT:
         std::cout << "finishing crossfade...";
         screen_a.create_and_use_backbuffer_sub_bitmap_of(al_get_backbuffer(display->al_display));
         screen_b.create_and_use_backbuffer_sub_bitmap_of(al_get_backbuffer(display->al_display));
         delete transition_fx;
         transition_fx = nullptr;
         std::cout << "done" << std::endl;
         break;
      default:
         break;
      }
   }

   void primary_timer_func() override
   {
      if (transition_fx)
      {
         transition_fx->update();
         transition_fx->draw();

         if (transition_fx->is_finished()) UserEventEmitter::emit_event(FINISH_TRANSITION_USER_EVENT);
      }
   }
};


int main(int, char**)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   DevTransitionFXScreen *dev_transition_fx_screen = new DevTransitionFXScreen(display);
   Framework::run_loop();
   return 0;
}


