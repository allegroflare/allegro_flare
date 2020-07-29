

#include <AllegroFlare/Profiler.hpp>

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


   void Profiler::start(std::string name)
   {
      find_or_create(name)->start();
   }


   void Profiler::pause(std::string name)
   {
      find_or_create(name)->pause();
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

      al_draw_filled_rounded_rectangle(x, y, x+w, y+h, 8, 8, bg_color);

      //if (!font) return;

      //std::vector<profile_timer_class *>::iterator it = Profiler::get_instance()->timer.begin();
      for (auto &timer : timers)
      {
         // multipliers are off.  for reference, 1 sec = 1000 msec
         float duration = timer.second.get_elapsed_time_msec() * 0.001f;//(*it)->stop_time - (*it)->start_time;
         al_draw_filled_rectangle(x, y+pad+line_height*i+15, x+duration*10000, y+pad+line_height*i+20, bar_color);
         al_draw_text(font, font_color, x+pad, y+pad+line_height*i, 0, timer.first.c_str());
         sprintf(time, "%d", duration*1000);
         al_draw_text(font, font_color, x+pad+200, y+pad+line_height*i, 0, time);
         i++;
      }
      al_draw_line(x+ALLEGRO_BPS_TO_SECS(60)*10000, y, x+ALLEGRO_BPS_TO_SECS(60)*10000, y+h, limit_bar_color, 1.0);
      //al_draw_line(x+ALLEGRO_BPS_TO_SECS(72)*10000, y, x+ALLEGRO_BPS_TO_SECS(72)*10000, y+h, limit_bar_color, 1.0);
   }
}



