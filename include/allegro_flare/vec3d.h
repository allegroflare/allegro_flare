#ifndef __AF_VEC3D_HPP
#define __AF_VEC3D_HPP

#include <cmath>
#include <string>
#include <sstream>


// from OpenLayer //


class vec3d
{
public:
   float x, y, z;


   // CONSTRUCTORS //

   vec3d( float x = 0.0, float y = 0.0, float z = 0.0 )
      : x( x ), y( y ), z( z ) {}


   
//   static inline vec2d PolarCoords( float angle, float magnitude ) {
//      return vec2d( magnitude * std::cos( angle ), magnitude * std::sin( angle ));
//   }


   // METHODS //

//   inline float GetAngle() const {
//     return std::atan2( y, x );
//   }


   inline float GetMagnitude() const {
      return std::sqrt( GetMagnitudeSquared() );
   }


   inline float GetMagnitudeSquared() const {
      return x * x + y * y + z * z;
   }


   inline vec3d Normalized() const {
      float magnitude = GetMagnitude();
	  // what if magnitude is 0?
      return vec3d( x / magnitude, y / magnitude, z / magnitude);
   }


   // OPERATORS //


   inline void operator += ( const vec3d &other ) {
      x += other.x;
	  y += other.y;
	  z += other.z;
   }

   inline void operator -= ( const vec3d &other ) {
      x -= other.x;
	  y -= other.y;
	  z -= other.z;
   }


   inline void operator *= ( float factor )
   {
      x *= factor;
	  y *= factor;
	  z *= factor;
   }


   inline void operator /= ( float divisor )
   {
      x /= divisor; 
	  y /= divisor;
	  z /= divisor;
   }

   inline bool operator == ( const vec3d &other ) const
   {
    return fabs(x - other.x) < 0.01 && fabs(y - other.y) < 0.01 && fabs(z - other.z) < 0.01;
   }
   
   inline bool operator != ( const vec3d &other ) const {
    return !(*this == other);
   }
   
   inline std::string ToString() const {
      std::ostringstream str;
      str << "( " << x << ", " << y << ", " << z << " )";
      return str.str();
   }
   
   inline std::string GetString() const {
      return ToString();
   }
};


// ADDITION AND SUBTRACTION //

inline vec3d operator + ( vec3d first, vec3d second ) {
   return vec3d( first.x + second.x, first.y + second.y, first.z + second.z );
}


inline vec3d operator - ( vec3d first, vec3d second ) {
   return vec3d( first.x - second.x, first.y - second.y, first.z - second.z  );
}


// MULTIPLICATION AND DIVISION

inline vec3d operator * ( vec3d vec, float factor ) {
   return vec3d( factor * vec.x, factor * vec.y, factor * vec.z );
}


inline vec3d operator * ( float factor, vec3d vec ) {
   return vec3d( factor * vec.x, factor * vec.y, factor * vec.z );
}


inline vec3d operator / ( vec3d vec, float divisor ) {
   return vec3d( vec.x / divisor, vec.y / divisor, vec.z / divisor );
}


// DOT PRODUCT //

inline float operator * ( vec3d first, vec3d second ) {
   return first.x * second.x + first.y * second.y + first.z * second.z;
}


// SIGN //

inline vec3d operator - ( vec3d vec ) {
   return vec3d( -vec.x, -vec.y, -vec.z );
}


// NORMALIZATION

inline vec3d operator ~ ( vec3d vec ) {
   return vec.Normalized();
}


// TESTS


// Checks if the points are in counter clockwise order //

/*
inline bool IsCounterClockwise( const vec2d first, const vec2d second, const vec2d third ) {
  float dx1, dx2, dy1, dy2;

  dx1 = second.x - first.x;
  dy1 = second.y - first.y;
  dx2 = third.x - second.x;
  dy2 = third.y - second.y;

  return dy1*dx2 < dy2*dx1;
}
*/












#endif