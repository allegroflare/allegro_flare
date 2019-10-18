#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <AllegroFlare/Bin.hpp>


namespace AllegroFlare
{
   class BitmapBin : public Bin<std::string, ALLEGRO_BITMAP *>
   {
   public:
      BitmapBin();
      ~BitmapBin();
      ALLEGRO_BITMAP *load_data(std::string identifier);
      void destroy_data(ALLEGRO_BITMAP *bmp);
   };
}


