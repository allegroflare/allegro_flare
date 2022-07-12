

#include <AllegroFlare/Elements/Backgrounds/ParallaxLayer.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


ParallaxLayer::ParallaxLayer(float anchor_x, float anchor_y, float offset_rate, ALLEGRO_BITMAP* bitmap)
   : anchor_x(anchor_x)
   , anchor_y(anchor_y)
   , offset_rate(offset_rate)
   , bitmap(bitmap)
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


float ParallaxLayer::get_anchor_x()
{
   return anchor_x;
}


float ParallaxLayer::get_anchor_y()
{
   return anchor_y;
}


float ParallaxLayer::get_offset_rate()
{
   return offset_rate;
}


ALLEGRO_BITMAP* ParallaxLayer::get_bitmap()
{
   return bitmap;
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


