#pragma once


#include <string>
#include <map>
#include <list>

#include <AllegroFlare/Timer.hpp>

#include <allegro5/allegro_font.h>

namespace AllegroFlare
{
   class Profiler
   {
   private:
      std::map<std::string, AllegroFlare::Timer> timers;
      std::map<std::string, std::vector<std::chrono::high_resolution_clock::time_point>> event_buckets;

      AllegroFlare::Timer *find_or_create(std::string name);

   public:
      Profiler();
      ~Profiler();

      std::map<std::string, AllegroFlare::Timer> get_timers();
      std::map<std::string, std::vector<std::chrono::high_resolution_clock::time_point>> get_event_buckets();
      std::list<std::string> get_event_bucket_names();
      int get_event_bucket_num_samples(std::string event_bucket_name);
      int get_event_bucket_duration_between_last_two_samples(std::string event_bucket_name);

      void start(std::string name);
      void pause(std::string name);
      void reset(std::string name);
      void clear();

      void emit(std::string name);
      std::vector<std::chrono::high_resolution_clock::time_point> get_event_samples(
         std::string name,
         int max_samples=10
      );

      void draw(float x, float y, ALLEGRO_FONT *font);
   };
}


