

#include <AllegroFlare/Profiler.hpp>

#include <iostream>
#include <sstream>
#include <algorithm>


#include <allegro5/allegro_color.h> // for the profiler renderer
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


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


std::map<std::string, std::vector<std::chrono::high_resolution_clock::time_point>> Profiler::get_event_buckets()
{
   return this->event_buckets;
}


std::list<std::string> Profiler::get_event_bucket_names()
{
   std::list<std::string> result;
   for (auto &event_bucket : event_buckets)
   {
      result.push_back(event_bucket.first);
   }
   return result;
}


int Profiler::get_event_bucket_num_samples(std::string event_bucket_name)
{
   if (event_buckets.find(event_bucket_name) == event_buckets.end()) return 0;
   return event_buckets[event_bucket_name].size();
}


int Profiler::get_event_bucket_duration_between_last_two_samples(std::string event_bucket_name)
{
   if (event_buckets.find(event_bucket_name) == event_buckets.end()) return 0;

   std::vector<std::chrono::high_resolution_clock::time_point> &bucket = event_buckets[event_bucket_name];
   if (bucket.size() <= 1) return 0;

   std::chrono::high_resolution_clock::time_point &most_recent_event_time = bucket[bucket.size() - 1];
   std::chrono::high_resolution_clock::time_point &second_most_recent_event_time = bucket[bucket.size() - 2];

   return std::chrono::duration_cast<std::chrono::microseconds>(
         most_recent_event_time - second_most_recent_event_time
      ).count();
}


void Profiler::start(std::string name)
{
   find_or_create(name)->start();
}


void Profiler::pause(std::string name)
{
   find_or_create(name)->pause();
}


void Profiler::stop(std::string name)
{
   find_or_create(name)->stop();
}


void Profiler::reset(std::string name)
{
   find_or_create(name)->reset();
}


void Profiler::emit(std::string name)
{
   std::chrono::high_resolution_clock::time_point event_time = std::chrono::high_resolution_clock::now();
   event_buckets[name].push_back(event_time);
}


std::vector<std::chrono::high_resolution_clock::time_point> Profiler::get_event_samples(
   std::string name,
   int max_samples
)
{
   std::vector<std::chrono::high_resolution_clock::time_point> &events_for_this_bucket = event_buckets[name];
   if (max_samples < 0) max_samples = 0;
   if (max_samples > events_for_this_bucket.size()) max_samples = events_for_this_bucket.size();

   std::vector<std::chrono::high_resolution_clock::time_point> events_to_return
      (events_for_this_bucket.end() - max_samples, events_for_this_bucket.end());
   return events_to_return;
}


void Profiler::clear()
{
   timers.clear();
   event_buckets.clear();
}


void Profiler::draw(float x, float y, ALLEGRO_FONT *font)
{
   // TODO: include Profiler "draw" as a metric in the graph, add a bool allowing "hiding" it.
   if (!font) throw std::runtime_error("cannot Profiler::draw with nullptr font");

   ALLEGRO_COLOR bg_color = al_color_name("black");
   float w = 300;
   float line_height = 25;
   float pad = 20;
   float h = timers.size()*line_height + pad*2;
   int i=0;
   char buff[32];
   float target_microseconds = 16666;
   float horizontal_scale = 0.01f;

   // draw the background
   al_draw_filled_rounded_rectangle(x, y, x+w, y+h, 8, 8, bg_color);

   if (timers.empty())
   {
      // Draw empty state when no timers are present
      int font_line_height = al_get_font_line_height(font);
      ALLEGRO_COLOR timer_empty_text_color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
      std::string text = "Profiler is not tracking any timers. [Press F1 to close]";
      al_draw_text(
         font,
         timer_empty_text_color,
         x + w/2,
         y+h/2-font_line_height/2,
         ALLEGRO_ALIGN_CENTER,
         text.c_str()
      );
   }
   else
   {
      // Draw the graph
      ALLEGRO_COLOR bg_color = al_color_name("black");
      ALLEGRO_COLOR bar_color = al_color_name("orange");
      ALLEGRO_COLOR font_color = al_color_name("white");
      ALLEGRO_COLOR limit_bar_color = al_color_name("lightblue");

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
         sprintf(buff, "%d", duration_microseconds);
         al_draw_text(font, font_color, x+pad+300, y+pad+line_height*i, ALLEGRO_ALIGN_RIGHT, buff);
         i++;
      }

      // draws our marker at 16666 (the number of microseconds in a frame)
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


} // AllegroFlare



