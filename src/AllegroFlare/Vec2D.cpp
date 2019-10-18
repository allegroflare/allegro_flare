

#include <AllegroFlare/Vec2D.hpp>

#include <cmath>
#include <sstream>




namespace AllegroFlare
{
   vec2d::vec2d(float x, float y)
      : x(x)
      , y(y)
   {}




   vec2d vec2d::polar_coords(float angle, float magnitude)
   {
      return vec2d(magnitude * std::cos(angle), magnitude * std::sin(angle));
   }




   float vec2d::get_angle() const
   {
      return std::atan2(y, x);
   }




   float vec2d::get_magnitude() const
   {
      return std::sqrt(get_magnitude_squared());
   }




   float vec2d::get_magnitude_squared() const
   {
      return x*x + y*y;
   }




   vec2d vec2d::normalized() const
   {
      float magnitude = get_magnitude();
      return vec2d(x/magnitude, y/magnitude);
   }




   void vec2d::operator+=(const vec2d &other)
   {
      x += other.x;
      y += other.y;
   }




   void vec2d::operator-=(const vec2d &other)
   {
      x -= other.x;
      y -= other.y;
   }




   void vec2d::operator*=(float factor)
   {
      x *= factor;
      y *= factor;
   }




   void vec2d::operator/=(float divisor)
   {
      x /= divisor;
      y /= divisor;
   }




   bool vec2d::operator==(const vec2d &other) const
   {
      return fabs(x - other.x) < 0.01 && fabs(y - other.y) < 0.01;
   }




   bool vec2d::operator!=(const vec2d &other) const
   {
      return !(*this == other);
   }




   std::string vec2d::get_string() const
   {
      std::ostringstream str;
      str << "(" << x << ", " << y << ")";
      return str.str();
   }




   vec2d operator+(vec2d first, vec2d second)
   {
      return vec2d(first.x + second.x, first.y + second.y);
   }




   vec2d operator-(vec2d first, vec2d second)
   {
      return vec2d(first.x - second.x, first.y - second.y);
   }




   vec2d operator*(vec2d vec, float factor)
   {
      return vec2d(factor * vec.x, factor * vec.y);
   }




   vec2d operator*(float factor, vec2d vec)
   {
      return vec2d(factor * vec.x, factor * vec.y);
   }




   vec2d operator/(vec2d vec, float divisor)
   {
      return vec2d(vec.x / divisor, vec.y / divisor);
   }




   // dot product
   float operator*(vec2d first, vec2d second)
   {
      return first.x * second.x + first.y * second.y;
   }




   // change the sign
   vec2d operator-(vec2d vec)
   {
      return vec2d(-vec.x, -vec.y);
   }




   // normalize
   vec2d operator~(vec2d vec)
   {
      return vec.normalized();
   }




   // Check if the points are in counter clockwise order
   bool is_counter_clockwise(const vec2d first, const vec2d second, const vec2d third)
   {
      float dx1, dx2, dy1, dy2;

      dx1 = second.x - first.x;
      dy1 = second.y - first.y;
      dx2 = third.x - second.x;
      dy2 = third.y - second.y;

      return dy1*dx2 < dy2*dx1;
   }
}


