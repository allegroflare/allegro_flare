

#include <AllegroFlare/Physics/AABB2D.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Physics
{


AABB2D::AABB2D(float x, float y, float w, float h, float velocity_x, float velocity_y)
   : x(x)
   , y(y)
   , w(w)
   , h(h)
   , velocity_x(velocity_x)
   , velocity_y(velocity_y)
{
}


AABB2D::~AABB2D()
{
}


void AABB2D::set_x(float x)
{
   this->x = x;
}


void AABB2D::set_y(float y)
{
   this->y = y;
}


void AABB2D::set_w(float w)
{
   this->w = w;
}


void AABB2D::set_h(float h)
{
   this->h = h;
}


void AABB2D::set_velocity_x(float velocity_x)
{
   this->velocity_x = velocity_x;
}


void AABB2D::set_velocity_y(float velocity_y)
{
   this->velocity_y = velocity_y;
}


float AABB2D::get_x() const
{
   return x;
}


float AABB2D::get_y() const
{
   return y;
}


float AABB2D::get_w() const
{
   return w;
}


float AABB2D::get_h() const
{
   return h;
}


float AABB2D::get_velocity_x() const
{
   return velocity_x;
}


float AABB2D::get_velocity_y() const
{
   return velocity_y;
}


float AABB2D::get_left_edge()
{
   return x;
}

float AABB2D::get_right_edge()
{
   return x + w;
}

float AABB2D::get_top_edge()
{
   return y;
}

float AABB2D::get_bottom_edge()
{
   return y + h;
}

void AABB2D::set_left_edge(float x)
{
   this->x = x;
   return;
}

void AABB2D::set_right_edge(float x)
{
   this->x = x - w;
   return;
}

void AABB2D::set_top_edge(float y)
{
   this->y = y;
   return;
}

void AABB2D::set_bottom_edge(float y)
{
   this->y = y - h;
   return;
}

bool AABB2D::collides(AllegroFlare::Physics::AABB2D* other, AllegroFlare::Vec2D self_offset, AllegroFlare::Vec2D other_offset)
{
   if (!(other))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::AABB2D::collides]: error: guard \"other\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::AABB2D::collides]: error: guard \"other\" not met");
   }
   // TODO: consider less assignment, add values directly into the conditional

   AllegroFlare::Vec2D a_min = AllegroFlare::Vec2D(x, y) + self_offset;
   AllegroFlare::Vec2D a_max = AllegroFlare::Vec2D(x+w, y+h) + self_offset;
   AllegroFlare::Vec2D b_min = AllegroFlare::Vec2D(other->x, other->y) + other_offset;
   AllegroFlare::Vec2D b_max = AllegroFlare::Vec2D(other->x + other->w, other->y + other->h) + other_offset;

   return (
      a_min.x <= b_max.x &&
      a_max.x >= b_min.x &&
      a_min.y <= b_max.y &&
      a_max.y >= b_min.y
   );
}

bool AABB2D::collides_with_point(AllegroFlare::Vec2D position)
{
   // TODO: Test this

   AllegroFlare::Vec2D a_min = AllegroFlare::Vec2D(x, y);
   AllegroFlare::Vec2D a_max = AllegroFlare::Vec2D(x+w, y+h);

   return (
      a_min.x <= position.x &&
      a_max.x >= position.x &&
      a_min.y <= position.y &&
      a_max.y >= position.y
   );
}


} // namespace Physics
} // namespace AllegroFlare


