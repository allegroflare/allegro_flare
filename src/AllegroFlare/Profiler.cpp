

#include <AllegroFlare/Profiler.hpp>

#include <iostream>
#include <sstream>
#include <algorithm>


namespace AllegroFlare
{
   Profiler::Profiler()
      : timers()
   {}


   Profiler::~Profiler()
   {
   }


   AllegroFlare::Timer *Profiler::find_or_create(std::string name)
   {
      std::map<std::string, AllegroFlare::Timer>::iterator it = timers.find(name);
      if (it == timers.end())
      {
         timers[name] = AllegroFlare::Timer();
         return &timers[name];
      }
      return &it->second;
   }


   std::map<std::string, AllegroFlare::Timer> Profiler::get_timers()
   {
      return this->timers;
   }


   std::vector<std::tuple<std::string, std::chrono::high_resolution_clock::time_point>> Profiler::get_events()
   {
      return this->events;
   }


   void Profiler::start(std::string name)
   {
      find_or_create(name)->start();
   }


   void Profiler::pause(std::string name)
   {
      find_or_create(name)->pause();
   }


   void Profiler::reset(std::string name)
   {
      find_or_create(name)->reset();
   }


   void Profiler::emit(std::string name)
   {
      std::chrono::high_resolution_clock::time_point event_time = std::chrono::high_resolution_clock::now();
      events.push_back({name, event_time});
   }


   void Profiler::clear()
   {
      timers.clear();
   }


#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
   void Profiler::draw(float x, float y, ALLEGRO_FONT *font)
   {
      if (!font) throw std::runtime_error("cannot Profiler::draw with nullptr font");

      //instance = new Profiler;
      ALLEGRO_COLOR bg_color = al_color_name("black");
      ALLEGRO_COLOR bar_color = al_color_name("orange");
      ALLEGRO_COLOR font_color = al_color_name("white");
      ALLEGRO_COLOR limit_bar_color = al_color_name("lightblue");
      //ALLEGRO_COLOR font = al_create_builtin_font();

      float w = 300;
      float line_height = 25;
      float pad = 20;
      float h = timers.size()*line_height + pad*2;
      //fla duration = 0.0;
      int i=0;
      char time[32];

      float target_microseconds = 16666;
      float horizontal_scale = 0.01f;

      al_draw_filled_rounded_rectangle(x, y, x+w, y+h, 8, 8, bg_color);

      //if (!font) return;

      //std::vector<profile_timer_class *>::iterator it = Profiler::get_instance()->timer.begin();
      for (auto &timer : timers)
      {
         int duration_microseconds = std::get<1>(timer).get_elapsed_time_microseconds();
         float bar_width = duration_microseconds * horizontal_scale;
         al_draw_filled_rectangle(
            x,
            y+pad+line_height*i+15,
            x+bar_width,
            y+pad+line_height*i+20,
            bar_color
         );

         al_draw_text(font, font_color, x+pad, y+pad+line_height*i, 0, timer.first.c_str());
         sprintf(time, "%d", duration_microseconds);
         al_draw_text(font, font_color, x+pad+300, y+pad+line_height*i, ALLEGRO_ALIGN_RIGHT, time);
         i++;
      }

      if (events.size() >= 2)
      {
         std::chrono::high_resolution_clock::time_point first_event_time = std::get<1>(events[0]);

         std::chrono::high_resolution_clock::time_point event_time = std::get<1>(events[events.size()-1]);

         auto event_time_since_start = std::chrono::duration_cast<std::chrono::microseconds>(
               (event_time - first_event_time)
            ).count();

         //al_draw_line(
      }

      al_draw_line(
         target_microseconds * horizontal_scale,
         0,
         target_microseconds * horizontal_scale,
         h,
         ALLEGRO_COLOR{0, 1, 1, 1},
         2.0
      );
   }
}



