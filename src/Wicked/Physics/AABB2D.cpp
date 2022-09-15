

#include <Wicked/Physics/AABB2D.hpp>




namespace Wicked
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


} // namespace Physics
} // namespace Wicked


