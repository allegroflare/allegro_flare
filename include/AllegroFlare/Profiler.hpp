#pragma once


#include <string>
#include <map>

#include <AllegroFlare/Timer.hpp>

#include <allegro5/allegro_font.h>

namespace AllegroFlare
{
   class Profiler
   {
   private:
      std::map<std::string, AllegroFlare::Timer> timers;

      AllegroFlare::Timer *find_or_create(std::string name);

   public:
      Profiler();
      ~Profiler();

      std::map<std::string, AllegroFlare::Timer> get_timers();

      void start(std::string name);
      void pause(std::string name);
      void clear();

      void draw(float x, float y, ALLEGRO_FONT *font);
   };
}


