

#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Locations
{


Basic::Basic(std::string label, float width, float height)
   : AllegroFlare::WorldMaps::Locations::Base(AllegroFlare::WorldMaps::Locations::Basic::TYPE)
   , label(label)
   , width(width)
   , height(height)
{
}


Basic::~Basic()
{
}


void Basic::set_label(std::string label)
{
   this->label = label;
}


void Basic::set_width(float width)
{
   this->width = width;
}


void Basic::set_height(float height)
{
   this->height = height;
}


std::string Basic::get_label() const
{
   return label;
}


float Basic::get_width() const
{
   return width;
}


float Basic::get_height() const
{
   return height;
}


bool Basic::collides(float point_x, float point_y)
{
   // TODO: Test

   // Offset the inputs to make collision calculation simpler
   point_x += width*0.5;
   point_y += height*0.5;

   // Calculate the collision
   if (point_x < get_x()) return false;
   if (point_y < get_y()) return false;
   if (point_x > get_x()+width) return false;
   if (point_y > get_y()+height) return false;
   return true;
}


} // namespace Locations
} // namespace WorldMaps
} // namespace AllegroFlare


