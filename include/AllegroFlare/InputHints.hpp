#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   class InputHints
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::vector<std::pair<std::string, std::string>> input_hints;

   public:
      InputHints(AllegroFlare::FontBin* font_bin=nullptr);
      ~InputHints();

      void render();
      static std::vector<std::pair<std::string, std::string>> build_placeholder_input_hints();
      ALLEGRO_FONT* obtain_font();
   };
}



