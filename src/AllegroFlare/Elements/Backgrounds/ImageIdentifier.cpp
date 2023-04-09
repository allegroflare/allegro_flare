

#include <AllegroFlare/Elements/Backgrounds/ImageIdentifier.hpp>

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


ImageIdentifier::ImageIdentifier(AllegroFlare::BitmapBin* bitmap_bin, std::string image_filename)
   : AllegroFlare::Elements::Backgrounds::Base("AllegroFlare/Elements/Backgrounds/ImageIdentifier")
   , bitmap_bin(bitmap_bin)
   , image_filename(image_filename)
{
}


ImageIdentifier::~ImageIdentifier()
{
}


void ImageIdentifier::render()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[ImageIdentifier::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ImageIdentifier::render: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Placement2D background_image_placement(1920/2, 1080/2, 1920/2, 1080/2);
   float scale = 2.0f;
   background_image_placement.scale = AllegroFlare::Vec2D(scale, scale);

   ALLEGRO_BITMAP *bitmap = obtain_background_bitmap();
   background_image_placement.start_transform();
   al_draw_bitmap(bitmap, 0, 0, 0);
   background_image_placement.restore_transform();
   return;
}

ALLEGRO_BITMAP* ImageIdentifier::obtain_background_bitmap()
{
   std::string full_identifier = image_filename;
   return bitmap_bin->auto_get(full_identifier);
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


