

#include <AllegroFlare/Elements/ImageLayer.hpp>




namespace AllegroFlare
{
namespace Elements
{


ImageLayer::ImageLayer(int tmj_id, std::string name, ALLEGRO_BITMAP* bitmap, std::string image_filename, float offset_x, float offset_y, float parallax_x, float parallax_y, bool repeat_x, bool repeat_y, float opacity, bool tint_color_is_set, ALLEGRO_COLOR tint_color)
   : tmj_id(tmj_id)
   , name(name)
   , bitmap(bitmap)
   , image_filename(image_filename)
   , offset_x(offset_x)
   , offset_y(offset_y)
   , parallax_x(parallax_x)
   , parallax_y(parallax_y)
   , repeat_x(repeat_x)
   , repeat_y(repeat_y)
   , opacity(opacity)
   , tint_color_is_set(tint_color_is_set)
   , tint_color(tint_color)
{
}


ImageLayer::~ImageLayer()
{
}




} // namespace Elements
} // namespace AllegroFlare


