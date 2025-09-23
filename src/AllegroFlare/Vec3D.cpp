



#include <AllegroFlare/Vec3D.hpp>

#include <cmath>
#include <sstream>




namespace AllegroFlare
{
   Vec3D::Vec3D(float x, float y, float z)
      : x( x )
      , y( y )
      , z( z )
   {}




   float Vec3D::get_magnitude() const
   {
      return std::sqrt(get_magnitude_squared());
   }




   float Vec3D::get_magnitude_squared() const
   {
      return x * x + y * y + z * z;
   }



   Vec3D Vec3D::cross_product(const Vec3D& other) const
   {
      // Implementation provided by ChatGPT
      float result_x = y * other.z - z * other.y;
      float result_y = z * other.x - x * other.z;
      float result_z = x * other.y - y * other.x;
      return Vec3D(result_x, result_y, result_z);
   }



   Vec3D Vec3D::normalized() const
   {
      float magnitude = get_magnitude();
      // what if magnitude is 0?
      return Vec3D( x / magnitude, y / magnitude, z / magnitude);
   }



   Vec3D Vec3D::negated() const
   {
      return Vec3D(-x, -y, -z);
   }



   Vec3D Vec3D::complemented() const
   {
      return Vec3D(1.0f-x, 1.0f-y, 1.0f-z);
   }



   Vec3D Vec3D::xzy() const
   {
      return Vec3D( x, z, y );
   }




   void Vec3D::operator+=(const Vec3D &other)
   {
      x += other.x;
      y += other.y;
      z += other.z;
   }




   void Vec3D::operator-=(const Vec3D &other)
   {
      x -= other.x;
      y -= other.y;
      z -= other.z;
   }




   void Vec3D::operator*=(float factor)
   {
      x *= factor;
      y *= factor;
      z *= factor;
   }




   void Vec3D::operator/=(float divisor)
   {
      x /= divisor;
      y /= divisor;
      z /= divisor;
   }




   bool Vec3D::operator==(const Vec3D &other) const
   {
      if (x != other.x) return false;
      if (y != other.y) return false;
      if (z != other.z) return false;
      return true;
      //return fabs(x - other.x) < 0.01 && fabs(y - other.y) < 0.01 && fabs(z - other.z) < 0.01;
   }




   bool Vec3D::operator!=(const Vec3D &other) const
   {
      return !(*this == other);
   }




   std::string Vec3D::to_string(int precision) const
   {
      std::ostringstream str;
      str.precision(precision);
      str << "( " << std::fixed << x << ", " << std::fixed << y << ", " << std::fixed << z << " )";
      return str.str();
   }




   std::string Vec3D::get_string() const
   {
      return to_string();
   }




   Vec3D operator+(Vec3D first, Vec3D second)
   {
      return Vec3D(first.x + second.x, first.y + second.y, first.z + second.z);
   }




   Vec3D operator-(Vec3D first, Vec3D second)
   {
      return Vec3D(first.x - second.x, first.y - second.y, first.z - second.z);
   }




   Vec3D operator*(Vec3D vec, float factor)
   {
      return Vec3D(factor * vec.x, factor * vec.y, factor * vec.z);
   }




   Vec3D operator*(float factor, Vec3D vec)
   {
      return Vec3D(factor * vec.x, factor * vec.y, factor * vec.z);
   }




   Vec3D operator/(Vec3D vec, float divisor)
   {
      return Vec3D(vec.x / divisor, vec.y / divisor, vec.z / divisor);
   }




   // dot product
   float operator*(Vec3D first, Vec3D second)
   {
      return first.x * second.x + first.y * second.y + first.z * second.z;
   }




   // change the sign
   Vec3D operator-(Vec3D vec)
   {
      return Vec3D( -vec.x, -vec.y, -vec.z );
   }




   // normalize
   Vec3D operator~(Vec3D vec)
   {
      return vec.normalized();
   }
}




