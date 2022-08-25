

#include <AllegroFlare/Elements/Backgrounds/Image.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


Image::Image(AllegroFlare::BitmapBin* bitmap_bin, std::string image_filename)
   : AllegroFlare::Elements::Backgrounds::Base("Image")
   , bitmap_bin(bitmap_bin)
   , image_filename(image_filename)
   , image_file_location_prefix("backgrounds/")
   , reveal_counter(0)
   , reveal_speed(1.0f/60.0f)
{
}


Image::~Image()
{
}


float Image::get_reveal_counter() const
{
   return reveal_counter;
}


void Image::render()
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "Image" << "::" << "render" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   float o = infer_opacity();
   ALLEGRO_COLOR revealing_white = ALLEGRO_COLOR{o, o, o, o};
   AllegroFlare::Placement2D background_image_placement{1920/2, 1080/2, 1920/2, 1080/2};
   float scale = 2.0f;
   background_image_placement.scale.x = background_image_placement.scale.y = scale;

   ALLEGRO_BITMAP *bitmap = obtain_background_bitmap();
   background_image_placement.start_transform();
   al_draw_tinted_bitmap(bitmap, revealing_white, 0, 0, 0);
   background_image_placement.restore_transform();
   return;
}

ALLEGRO_BITMAP* Image::obtain_background_bitmap()
{
   std::string full_identifier = image_file_location_prefix + image_filename;
   return bitmap_bin->auto_get(full_identifier);
}

void Image::activate()
{
   reveal_counter = 1.0;
   return;
}

void Image::deactivate()
{
   reveal_counter = 0.0;
   return;
}

void Image::update()
{
   reveal_counter += reveal_speed;
   if (reveal_counter >= 1.0) reveal_counter = 1.0f;
   if (reveal_counter < 0.0) reveal_counter = 0.0f;
   return;
}

float Image::infer_opacity()
{
   return get_reveal_counter();
}
} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


