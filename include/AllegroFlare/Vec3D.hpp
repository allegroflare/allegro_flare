#pragma once


#include <string>


namespace AllegroFlare
{
   class Vec3D
   {
   public:
      float x, y, z;

      Vec3D(float x=0.0, float y=0.0, float z=0.0);

      // return the magnitude, or length, of the vector
      float get_magnitude() const;

      // return the magnitude squared of the vector
      float get_magnitude_squared() const;

      // returns the cross product
      Vec3D cross_product(const Vec3D& other) const;

      // returns the normalized value of the vector where the length = 1
      Vec3D normalized() const;

      // returns swizzled coordinate values
      Vec3D xzy() const;

      void operator+=(const Vec3D &other);
      void operator-=(const Vec3D &other);
      void operator*=(float factor);
      void operator/=(float divisor);
      bool operator==(const Vec3D &other) const;
      bool operator!=(const Vec3D &other) const;

      // returns the vector formatted as a string
      std::string to_string(int precision=5) const;
      std::string get_string() const;
   };




   // add two vectors
   Vec3D operator+(Vec3D first, Vec3D second);

   // subtract two vectors
   Vec3D operator-(Vec3D first, Vec3D second);

   // multiply a vector by a factor
   Vec3D operator*(Vec3D vec, float factor);
   Vec3D operator*(float factor, Vec3D vec);

   // divide a vector by a factor
   Vec3D operator/(Vec3D vec, float divisor);

   // dot product
   float operator*(Vec3D first, Vec3D second);

   // change the sign
   Vec3D operator-(Vec3D vec);

   // normalize
   Vec3D operator~(Vec3D vec);




   // allow legacy usage of "AllegroFlare::vec3d" instead of "AllegroFlare::Vec3D"
   // TODO: consider depreciating
   typedef Vec3D vec3d;
}





