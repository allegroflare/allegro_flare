#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro_font.h>
#include <map>
#include <string>


namespace AllegroFlare
{
   class ProfilerRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::map<std::string, AllegroFlare::Timer*> timers;
      float x;
      float y;
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      ProfilerRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::map<std::string, AllegroFlare::Timer*> timers={}, float x=0, float y=0);
      ~ProfilerRenderer();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_timers(std::map<std::string, AllegroFlare::Timer*> timers);
      void set_x(float x);
      void set_y(float y);
      AllegroFlare::FontBin* get_font_bin() const;
      std::map<std::string, AllegroFlare::Timer*> get_timers() const;
      float get_x() const;
      float get_y() const;
      void render();
   };
}



