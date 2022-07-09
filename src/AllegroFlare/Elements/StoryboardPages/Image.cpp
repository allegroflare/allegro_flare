

#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


Image::Image(ALLEGRO_BITMAP* bitmap)
   : AllegroFlare::Elements::StoryboardPages::Base("Image")
   , bitmap(bitmap)
{
}


Image::~Image()
{
}


void Image::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


ALLEGRO_BITMAP* Image::get_bitmap()
{
   return bitmap;
}


void Image::start()
{
   return;
}

void Image::update()
{
   return;
}

void Image::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Image" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_get_current_display()))
      {
         std::stringstream error_message;
         error_message << "Image" << "::" << "render" << ": error: " << "guard \"al_get_current_display()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!bitmap) return;

   AllegroFlare::Placement2D image_place;
   image_place.position.x = 1920/2;
   image_place.position.y = 1080/2;
   image_place.size.x = al_get_bitmap_width(bitmap);
   image_place.size.y = al_get_bitmap_height(bitmap);

   image_place.start_transform();

   al_draw_bitmap(bitmap, 0, 0, 0);

   image_place.restore_transform();

   return;
}

void Image::advance()
{
   return;
}
} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


