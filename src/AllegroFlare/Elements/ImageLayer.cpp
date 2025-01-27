

#include <AllegroFlare/Elements/ImageLayer.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace Elements
{


ImageLayer::ImageLayer(int tmj_id, std::string name, std::string image_filename, ALLEGRO_BITMAP* bitmap, bool bitmap_is_owned, int pixel_scale, float offset_x, float offset_y, float parallax_x, float parallax_y, bool repeat_x, bool repeat_y, float opacity, bool tint_color_is_set, ALLEGRO_COLOR tint_color, bool destroyed)
   : tmj_id(tmj_id)
   , name(name)
   , image_filename(image_filename)
   , bitmap(bitmap)
   , bitmap_is_owned(bitmap_is_owned)
   , pixel_scale(pixel_scale)
   , offset_x(offset_x)
   , offset_y(offset_y)
   , parallax_x(parallax_x)
   , parallax_y(parallax_y)
   , repeat_x(repeat_x)
   , repeat_y(repeat_y)
   , opacity(opacity)
   , tint_color_is_set(tint_color_is_set)
   , tint_color(tint_color)
   , destroyed(destroyed)
{
}


ImageLayer::~ImageLayer()
{
   if (bitmap_is_owned)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Elements::ImageLayer",
         "This object owns a bitmaps that should be destroyed since \"clone_and_own_bitmap()\" was "
            "called on this object. Be sure to call \"destroy_bitmaps_if_owned()\" before destruction."
      );
   }
   destroyed = true;
   return;
}


void ImageLayer::destroy_bitmap_if_owned()
{
   if (!bitmap_is_owned) return;
   al_destroy_bitmap(bitmap);
   bitmap = nullptr;
   bitmap_is_owned = false;
   pixel_scale = 1;
   return;
}


} // namespace Elements
} // namespace AllegroFlare


