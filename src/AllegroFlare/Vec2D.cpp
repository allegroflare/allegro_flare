

#include <AllegroFlare/Vec2D.hpp>

#include <cmath>
#include <sstream>




namespace AllegroFlare
{
   Vec2D::Vec2D(float x, float y)
      : x(x)
      , y(y)
   {}



    Vec2D::Vec2D(const std::pair<float, float>& p)
        : x(p.first)
        , y(p.second)
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
      if (other.x != x) return false;
      if (other.y != y) return false;
      return true;
      //return fabs(x - other.x) < 0.01 && fabs(y - other.y) < 0.01;
   }




   bool Vec2D::operator!=(const Vec2D &other) const
   {
      return !(*this == other);
   }




   Vec2D& Vec2D::operator=(const std::pair<float, float> &float_pair)
   {
       x = float_pair.first;
       y = float_pair.second;
       return *this; // Return a reference to the modified object
   }



   // New compound assignment operators for std::pair
   Vec2D& Vec2D::operator+=(const std::pair<float, float>& p)
   {
       x += p.first;
       y += p.second;
       return *this;
   }



   Vec2D& Vec2D::operator-=(const std::pair<float, float>& p)
   {
       x -= p.first;
       y -= p.second;
       return *this;
   }



   // Component-wise multiplication
   Vec2D& Vec2D::operator*=(const std::pair<float, float>& p)
   {
       x *= p.first;
       y *= p.second;
       return *this;
   }



   // Component-wise division
   Vec2D& Vec2D::operator/=(const std::pair<float, float>& p)
   {
       if (p.first == 0.0f || p.second == 0.0f)
       {
           // Or throw an exception, or handle as per your library's error strategy
           // For example:
           // throw std::domain_error("Division by zero in Vec2D::operator/=(std::pair)");
           // For now, this will result in INF or NaN as per float division rules.
           // Depending on requirements, you might want specific behavior.
       }
       x /= p.first;
       y /= p.second;
       return *this;
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


