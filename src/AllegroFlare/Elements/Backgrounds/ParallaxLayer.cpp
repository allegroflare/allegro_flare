

#include <AllegroFlare/Elements/Backgrounds/ParallaxLayer.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


ParallaxLayer::ParallaxLayer(float anchor_x, float anchor_y, float offset_rate, ALLEGRO_BITMAP* bitmap, int tmj_id, std::string name, std::string image_filename, float offset_x, float offset_y, float parallax_x, float parallax_y, bool repeat_x, bool repeat_y, float opacity, bool tint_color_is_set, ALLEGRO_COLOR tint_color)
   : anchor_x(anchor_x)
   , anchor_y(anchor_y)
   , offset_rate(offset_rate)
   , bitmap(bitmap)
   , tmj_id(tmj_id)
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


ParallaxLayer::~ParallaxLayer()
{
}


void ParallaxLayer::set_anchor_x(float anchor_x)
{
   this->anchor_x = anchor_x;
}


void ParallaxLayer::set_anchor_y(float anchor_y)
{
   this->anchor_y = anchor_y;
}


void ParallaxLayer::set_offset_rate(float offset_rate)
{
   this->offset_rate = offset_rate;
}


void ParallaxLayer::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


float ParallaxLayer::get_anchor_x() const
{
   return anchor_x;
}


float ParallaxLayer::get_anchor_y() const
{
   return anchor_y;
}


float ParallaxLayer::get_offset_rate() const
{
   return offset_rate;
}


ALLEGRO_BITMAP* ParallaxLayer::get_bitmap() const
{
   return bitmap;
}




} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


