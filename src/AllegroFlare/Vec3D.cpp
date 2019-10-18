



#include <AllegroFlare/Vec3D.hpp>

#include <cmath>
#include <sstream>




namespace AllegroFlare
{
   vec3d::vec3d(float x, float y, float z)
      : x( x )
      , y( y )
      , z( z )
   {}




   float vec3d::get_magnitude() const
   {
      return std::sqrt(get_magnitude_squared());
   }




   float vec3d::get_magnitude_squared() const
   {
      return x * x + y * y + z * z;
   }




   vec3d vec3d::normalized() const
   {
      float magnitude = get_magnitude();
      // what if magnitude is 0?
      return vec3d( x / magnitude, y / magnitude, z / magnitude);
   }




   void vec3d::operator+=(const vec3d &other)
   {
      x += other.x;
      y += other.y;
      z += other.z;
   }




   void vec3d::operator-=(const vec3d &other)
   {
      x -= other.x;
      y -= other.y;
      z -= other.z;
   }




   void vec3d::operator*=(float factor)
   {
      x *= factor;
      y *= factor;
      z *= factor;
   }




   void vec3d::operator/=(float divisor)
   {
      x /= divisor;
      y /= divisor;
      z /= divisor;
   }




   bool vec3d::operator==(const vec3d &other) const
   {
      return fabs(x - other.x) < 0.01 && fabs(y - other.y) < 0.01 && fabs(z - other.z) < 0.01;
   }




   bool vec3d::operator!=(const vec3d &other) const
   {
      return !(*this == other);
   }




   std::string vec3d::to_string(int precision) const
   {
      std::ostringstream str;
      str.precision(precision);
      str << "( " << std::fixed << x << ", " << std::fixed << y << ", " << std::fixed << z << " )";
      return str.str();
   }




   std::string vec3d::get_string() const
   {
      return to_string();
   }




   vec3d operator+(vec3d first, vec3d second)
   {
      return vec3d(first.x + second.x, first.y + second.y, first.z + second.z);
   }




   vec3d operator-(vec3d first, vec3d second)
   {
      return vec3d(first.x - second.x, first.y - second.y, first.z - second.z);
   }




   vec3d operator*(vec3d vec, float factor)
   {
      return vec3d(factor * vec.x, factor * vec.y, factor * vec.z);
   }




   vec3d operator*(float factor, vec3d vec)
   {
      return vec3d(factor * vec.x, factor * vec.y, factor * vec.z);
   }




   vec3d operator/(vec3d vec, float divisor)
   {
      return vec3d(vec.x / divisor, vec.y / divisor, vec.z / divisor);
   }




   // dot product
   float operator*(vec3d first, vec3d second)
   {
      return first.x * second.x + first.y * second.y + first.z * second.z;
   }




   // change the sign
   vec3d operator-(vec3d vec)
   {
      return vec3d( -vec.x, -vec.y, -vec.z );
   }




   // normalize
   vec3d operator~(vec3d vec)
   {
      return vec.normalized();
   }
}




