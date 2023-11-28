

#include <AllegroFlare/WorldMaps/Locations/Player.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Locations
{


Player::Player(float x, float y, float width, float height)
   : AllegroFlare::WorldMaps::Locations::Base(AllegroFlare::WorldMaps::Locations::Player::TYPE)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
{
}


Player::~Player()
{
}


void Player::set_x(float x)
{
   this->x = x;
}


void Player::set_y(float y)
{
   this->y = y;
}


void Player::set_width(float width)
{
   this->width = width;
}


void Player::set_height(float height)
{
   this->height = height;
}


float Player::get_x() const
{
   return x;
}


float Player::get_y() const
{
   return y;
}


float Player::get_width() const
{
   return width;
}


float Player::get_height() const
{
   return height;
}


bool Player::collides(float point_x, float point_y)
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


