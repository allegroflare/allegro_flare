

#include <AllegroFlare/BitmapBin.hpp>


namespace AllegroFlare
{
   BitmapBin::BitmapBin()
      : Bin<std::string, ALLEGRO_BITMAP *>()
   {}


   BitmapBin::~BitmapBin()
   {
      clear();
   }


   ALLEGRO_BITMAP *BitmapBin::load_data(std::string identifier)
   {
      return al_load_bitmap(identifier.c_str());
   }


   void BitmapBin::destroy_data(ALLEGRO_BITMAP *bmp)
   {
      al_destroy_bitmap(bmp);
   }
}


