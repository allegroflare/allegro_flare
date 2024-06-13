

#include <AllegroFlare/Elements/Backgrounds/Image.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


Image::Image(AllegroFlare::BitmapBin* bitmap_bin, std::string image_filename)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::Image::TYPE)
   , bitmap_bin(bitmap_bin)
   , image_filename(image_filename)
{
}


Image::~Image()
{
}


void Image::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Image::set_image_filename(std::string image_filename)
{
   this->image_filename = image_filename;
}


AllegroFlare::BitmapBin* Image::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::string Image::get_image_filename() const
{
   return image_filename;
}


void Image::render()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Image::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Image::render]: error: guard \"bitmap_bin\" not met");
   }
   int surface_width = 1920; // TDOO: Consider having this value be a property on the class
   int surface_height = 1080; // TDOO: Consider having this value be a property on the class
   ALLEGRO_BITMAP *bitmap = obtain_background_bitmap();
   AllegroFlare::Placement2D background_image_placement(
      surface_width * 0.5f,
      surface_height * 0.5f,
      al_get_bitmap_width(bitmap),
      al_get_bitmap_height(bitmap)
   );

   background_image_placement.start_transform();
   al_draw_bitmap(bitmap, 0, 0, 0);
   background_image_placement.restore_transform();
   return;
}

ALLEGRO_BITMAP* Image::obtain_background_bitmap()
{
   std::string full_identifier = image_filename;
   return bitmap_bin->auto_get(full_identifier);
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


