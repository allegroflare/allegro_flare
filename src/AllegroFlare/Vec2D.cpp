

#include <AllegroFlare/Vec2D.hpp>

#include <cmath>
#include <sstream>




namespace AllegroFlare
{
   Vec2D::Vec2D(float x, float y)
      : x(x)
      , y(y)
   {}




   Vec2D Vec2D::polar_coords(float angle, float magnitude)
   {
      return Vec2D(magnitude * std::cos(angle), magnitude * std::sin(angle));
   }




   float Vec2D::get_angle() const
   {
      return std::atan2(y, x);
   }




   float Vec2D::get_magnitude() const
   {
      return std::sqrt(get_magnitude_squared());
   }




   float Vec2D::get_magnitude_squared() const
   {
      return x*x + y*y;
   }




   Vec2D Vec2D::normalized() const
   {
      float magnitude = get_magnitude();
      return Vec2D(x/magnitude, y/magnitude);
   }




   void Vec2D::operator+=(const Vec2D &other)
   {
      x += other.x;
      y += other.y;
   }




   void Vec2D::operator-=(const Vec2D &other)
   {
      x -= other.x;
      y -= other.y;
   }




   void Vec2D::operator*=(float factor)
   {
      x *= factor;
      y *= factor;
   }




   void Vec2D::operator/=(float divisor)
   {
      x /= divisor;
      y /= divisor;
   }




   bool Vec2D::operator==(const Vec2D &other) const
   {
      return fabs(x - other.x) < 0.01 && fabs(y - other.y) < 0.01;
   }




   bool Vec2D::operator!=(const Vec2D &other) const
   {
      return !(*this == other);
   }




   std::string Vec2D::get_string() const
   {
      std::ostringstream str;
      str << "(" << x << ", " << y << ")";
      return str.str();
   }




   Vec2D operator+(Vec2D first, Vec2D second)
   {
      return Vec2D(first.x + second.x, first.y + second.y);
   }




   Vec2D operator-(Vec2D first, Vec2D second)
   {
      return Vec2D(first.x - second.x, first.y - second.y);
   }




   Vec2D operator*(Vec2D vec, float factor)
   {
      return Vec2D(factor * vec.x, factor * vec.y);
   }




   Vec2D operator*(float factor, Vec2D vec)
   {
      return Vec2D(factor * vec.x, factor * vec.y);
   }




   Vec2D operator/(Vec2D vec, float divisor)
   {
      return Vec2D(vec.x / divisor, vec.y / divisor);
   }




   // dot product
   float operator*(Vec2D first, Vec2D second)
   {
      return first.x * second.x + first.y * second.y;
   }




   // change the sign
   Vec2D operator-(Vec2D vec)
   {
      return Vec2D(-vec.x, -vec.y);
   }




   // normalize
   Vec2D operator~(Vec2D vec)
   {
      return vec.normalized();
   }




   // Check if the points are in counter clockwise order
   bool is_counter_clockwise(const Vec2D first, const Vec2D second, const Vec2D third)
   {
      float dx1, dx2, dy1, dy2;

      dx1 = second.x - first.x;
      dy1 = second.y - first.y;
      dx2 = third.x - second.x;
      dy2 = third.y - second.y;

      return dy1*dx2 < dy2*dx1;
   }
}


