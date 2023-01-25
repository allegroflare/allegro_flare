#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   class ProfilerRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::string quote;
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      ProfilerRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Hello!");
      ~ProfilerRenderer();

      void render();
   };
}



