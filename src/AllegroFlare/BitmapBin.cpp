

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


   bool BitmapBin::validate()
   {
      if (!al_is_image_addon_initialized())
      {
         std::cout << "[BitmapBin::validate] not properly initialized (requires al_init_image_addon()). "
                   << " Will crash probably crash." << std::endl;
         return false;
      }
      return true;
   }


   ALLEGRO_BITMAP *BitmapBin::load_data(std::string identifier)
   {
      validate();
      return al_load_bitmap(identifier.c_str());
   }


   void BitmapBin::destroy_data(ALLEGRO_BITMAP *bmp)
   {
      al_destroy_bitmap(bmp);
   }
}


