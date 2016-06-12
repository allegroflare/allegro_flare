#ifndef __AF_VEC_2D_HEADER
#define __AF_VEC_2D_HEADER




#include <string>




class vec2d
{
public:
   float x, y;

   vec2d(float x=0.0, float y=0.0);

   // returns the polar coordinates of an angle (in radians?) and magnitude
   static vec2d polar_coords(float angle, float magnitude);

   // return the arctangent(2) for the current vector
   float get_angle() const;

   // return the magnitude, or length, of the vector
   float get_magnitude() const;

   // return the magnitude squared of the vector
   float get_magnitude_squared() const;

   // returns the normalized value of the vector where the length = 1
   vec2d normalized() const;

   void operator+=(const vec2d &other);
   void operator-=(const vec2d &other);
   void operator*=(float factor);
   void operator/=(float divisor);
   bool operator==(const vec2d &other) const;
   bool operator!=(const vec2d &other) const;

   // returns the vector formatted as a string
   std::string get_string() const;
};




// add two vectors
vec2d operator+(vec2d first, vec2d second);

// subtract two vectors
vec2d operator-(vec2d first, vec2d second);

// multiply a vector by a factor
vec2d operator*(vec2d vec, float factor);
vec2d operator*(float factor, vec2d vec);

// divide a vector by a factor
vec2d operator/(vec2d vec, float divisor);

// dot product
float operator*(vec2d first, vec2d second);

// change the sign
vec2d operator-(vec2d vec);

// normalize
vec2d operator~(vec2d vec);

// Check if the points are in counter clockwise order
bool is_counter_clockwise(const vec2d first, const vec2d second, const vec2d third);




#endif
