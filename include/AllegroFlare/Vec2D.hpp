#pragma once


#include <string>
#include <utility> // for std::pair


namespace AllegroFlare
{
   class Vec2D
   {
   public:
      float x, y;

      Vec2D(float x=0.0, float y=0.0);
      Vec2D(const std::pair<float, float>& p);

      // returns the polar coordinates of an angle (in radians?) and magnitude
      static Vec2D polar_coords(float angle, float magnitude);

      // return the arctangent(2) for the current vector, returns the value in radians (2*pi)
      float get_angle() const;

      // return the magnitude, or length, of the vector
      float get_magnitude() const;

      // return the magnitude squared of the vector
      float get_magnitude_squared() const;

      // returns the normalized value of the vector where the length = 1
      Vec2D normalized() const;

      void operator+=(const Vec2D &other);
      void operator-=(const Vec2D &other);
      void operator*=(float factor);
      void operator/=(float divisor);
      bool operator==(const Vec2D &other) const;
      bool operator!=(const Vec2D &other) const;

      // Compound operators for use with std::pair<float, float>
      Vec2D& operator=(const std::pair<float, float> &float_pair);
      Vec2D& operator+=(const std::pair<float, float>& p);
      Vec2D& operator-=(const std::pair<float, float>& p);
      Vec2D& operator*=(const std::pair<float, float>& p); // Component-wise multiplication
      Vec2D& operator/=(const std::pair<float, float>& p); // Component-wise division

      // returns the vector formatted as a string
      std::string get_string() const;
   };


   // add two vectors
   Vec2D operator+(Vec2D first, Vec2D second);

   // subtract two vectors
   Vec2D operator-(Vec2D first, Vec2D second);

   // multiply a vector by a factor
   Vec2D operator*(Vec2D vec, float factor);
   Vec2D operator*(float factor, Vec2D vec);

   // divide a vector by a factor
   Vec2D operator/(Vec2D vec, float divisor);

   // dot product
   float operator*(Vec2D first, Vec2D second);

   // change the sign
   Vec2D operator-(Vec2D vec);

   // normalize
   Vec2D operator~(Vec2D vec);

   // Check if the points are in counter clockwise order
   bool is_counter_clockwise(const Vec2D first, const Vec2D second, const Vec2D third);

   // allow legacy usage of "AllegroFlare::vec2d" instead of "AllegroFlare::Vec2D"
   // TODO: consider depreciating
   typedef Vec2D vec2d;
}


