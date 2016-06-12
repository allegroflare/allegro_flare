#ifndef __AF_VEC_3D_HEADER
#define __AF_VEC_3D_HEADER




#include <string>




class vec3d
{
public:
   float x, y, z;

   vec3d(float x=0.0, float y=0.0, float z=0.0);

   // return the magnitude, or length, of the vector
   float get_magnitude() const;

   // return the magnitude squared of the vector
   float get_magnitude_squared() const;

   // returns the normalized value of the vector where the length = 1
   vec3d normalized() const;

   void operator+=(const vec3d &other);
   void operator-=(const vec3d &other);
   void operator*=(float factor);
   void operator/=(float divisor);
   bool operator==(const vec3d &other) const;
   bool operator!=(const vec3d &other) const;

   // returns the vector formatted as a string
   std::string to_string(int precision=5) const;
   std::string get_string() const;
};




// add two vectors
vec3d operator+(vec3d first, vec3d second);

// subtract two vectors
vec3d operator-(vec3d first, vec3d second);

// multiply a vector by a factor
vec3d operator*(vec3d vec, float factor);
vec3d operator*(float factor, vec3d vec);

// divide a vector by a factor
vec3d operator/(vec3d vec, float divisor);

// dot product
float operator*(vec3d first, vec3d second);

// change the sign
vec3d operator-(vec3d vec);

// normalize
vec3d operator~(vec3d vec);




#endif
