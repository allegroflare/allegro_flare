

#include <AllegroFlare/BitmapInfo.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


BitmapInfo::BitmapInfo(ALLEGRO_BITMAP* bitmap)
   : bitmap(bitmap)
   , width(0)
   , height(0)
   , pixel_format(0)
   , flags(0)
   , samples(0)
   , is_sub_bitmap(false)
   , sub_bitmap_x(0)
   , sub_bitmap_y(0)
   , parent_bitmap(nullptr)
   , initialized(false)
{
}


BitmapInfo::~BitmapInfo()
{
}


void BitmapInfo::initialize(ALLEGRO_BITMAP* bitmap)
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::BitmapInfo::initialize]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::BitmapInfo::initialize]: error: guard \"bitmap\" not met");
   }
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::BitmapInfo::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::BitmapInfo::initialize]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap = bitmap;
   flags = al_get_bitmap_flags(bitmap);
   pixel_format = al_get_bitmap_format(bitmap);
   //depth = al_get_bitmap_depth(bitmap); // NOTE: Depth cannot be included unless ALLEGRO_UNSTABLE is defined
                                          // before #include <allegro5/allegro.h>. Simply adding AllegroUnstable
                                          // as a dependency here will not get the order correct when the header
                                          // is generated
   width = al_get_bitmap_format(bitmap);
   flags = al_get_bitmap_flags(bitmap);
   samples = al_get_bitmap_flags(bitmap);
   is_sub_bitmap = al_is_sub_bitmap(bitmap);
   sub_bitmap_x = al_get_bitmap_x(bitmap);
   sub_bitmap_y = al_get_bitmap_y(bitmap);
   parent_bitmap = al_get_parent_bitmap(bitmap);
   initialized = true;
}


} // namespace AllegroFlare


