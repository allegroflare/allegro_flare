#pragma once


#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <AllegroFlare/Bin.hpp>


namespace AllegroFlare
{
   class FontBin : public Bin<std::string, ALLEGRO_FONT *>
   {
   private:
      int _get_valid_font_size(std::string num);
   public:
      FontBin();
      ~FontBin();
      ALLEGRO_FONT *load_data(std::string identifier);
      void destroy_data(ALLEGRO_FONT *f);
   };
}


