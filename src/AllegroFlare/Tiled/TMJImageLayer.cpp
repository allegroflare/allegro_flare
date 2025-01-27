

#include <AllegroFlare/Tiled/TMJImageLayer.hpp>

#include <AllegroFlare/Tiled/TMJDataLoader.hpp>


namespace AllegroFlare
{
namespace Tiled
{


TMJImageLayer::TMJImageLayer(int id, std::string name, std::string image_filename, float offset_x, float offset_y, float parallax_x, float parallax_y, bool repeat_x, bool repeat_y, float opacity, bool tint_color_is_set, ALLEGRO_COLOR tint_color)
   : id(id)
   , name(name)
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


TMJImageLayer::~TMJImageLayer()
{
}


std::string TMJImageLayer::extract_image_basename_with_extension()
{
   return AllegroFlare::Tiled::TMJDataLoader::extract_last_fragment(image_filename);
}


} // namespace Tiled
} // namespace AllegroFlare


