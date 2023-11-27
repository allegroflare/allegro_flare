

#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Locations
{


Basic::Basic(std::string label, float x, float y, float width, float height)
   : AllegroFlare::WorldMaps::Locations::Base(AllegroFlare::WorldMaps::Locations::Basic::TYPE)
   , label(label)
   , x(x)
   , y(y)
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


void Basic::set_x(float x)
{
   this->x = x;
}


void Basic::set_y(float y)
{
   this->y = y;
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


float Basic::get_x() const
{
   return x;
}


float Basic::get_y() const
{
   return y;
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
   if (point_x < x) return false;
   if (point_y < y) return false;
   if (point_x > x+width) return false;
   if (point_y > y+height) return false;
   return true;
}


} // namespace Locations
} // namespace WorldMaps
} // namespace AllegroFlare


