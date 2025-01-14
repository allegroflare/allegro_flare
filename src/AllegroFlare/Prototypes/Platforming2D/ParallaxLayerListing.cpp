

#include <AllegroFlare/Prototypes/Platforming2D/ParallaxLayerListing.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


ParallaxLayerListing::ParallaxLayerListing(float anchor_x, float anchor_y, float offset_rate, std::string bitmap_identifier)
   : anchor_x(anchor_x)
   , anchor_y(anchor_y)
   , offset_rate(offset_rate)
   , bitmap_identifier(bitmap_identifier)
{
}


ParallaxLayerListing::~ParallaxLayerListing()
{
}


void ParallaxLayerListing::set_anchor_x(float anchor_x)
{
   this->anchor_x = anchor_x;
}


void ParallaxLayerListing::set_anchor_y(float anchor_y)
{
   this->anchor_y = anchor_y;
}


void ParallaxLayerListing::set_offset_rate(float offset_rate)
{
   this->offset_rate = offset_rate;
}


void ParallaxLayerListing::set_bitmap_identifier(std::string bitmap_identifier)
{
   this->bitmap_identifier = bitmap_identifier;
}


float ParallaxLayerListing::get_anchor_x() const
{
   return anchor_x;
}


float ParallaxLayerListing::get_anchor_y() const
{
   return anchor_y;
}


float ParallaxLayerListing::get_offset_rate() const
{
   return offset_rate;
}


std::string ParallaxLayerListing::get_bitmap_identifier() const
{
   return bitmap_identifier;
}




} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


