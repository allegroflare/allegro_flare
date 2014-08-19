#ifndef OL_VEC2D_HPP
#define OL_VEC2D_HPP

#include <cmath>
#include <string>
#include <sstream>


// from OpenLayer //


class vec2d
{
public:
   float x, y;


   // CONSTRUCTORS //

   vec2d( float x = 0.0, float y = 0.0 )
      : x( x ), y( y ) {}


   static inline vec2d PolarCoords( float angle, float magnitude ) {
      return vec2d( magnitude * std::cos( angle ), magnitude * std::sin( angle ));
   }


   // METHODS //

   inline float get_angle() const {
      return std::atan2( y, x );
   }


   inline float get_magnitude() const {
      return std::sqrt( get_magnitude_squared() );
   }


   inline float get_magnitude_squared() const {
      return x * x + y * y;
   }


   inline vec2d Normalized() const {
      float magnitude = get_magnitude();

      return vec2d( x / magnitude, y / magnitude );
   }


   // OPERATORS //


   inline void operator += ( const vec2d &other ) {
      x += other.x; y += other.y;
   }

   inline void operator -= ( const vec2d &other ) {
      x -= other.x; y -= other.y;
   }


   inline void operator *= ( float factor ) {
      x *= factor; y *= factor;
   }


   inline void operator /= ( float divisor ) {
      x /= divisor; y /= divisor;
   }

   inline bool operator == ( const vec2d &other ) const {
    return fabs(x - other.x) < 0.01 && fabs(y - other.y) < 0.01;
   }
   
   inline bool operator != ( const vec2d &other ) const {
    return !(*this == other);
   }
   
   inline std::string get_string() const {
      std::ostringstream str;
      str << "(" << x << ", " << y << ")";
      return str.str();
   }
   
   /*
   inline std::string GetString() const {
      return ToString();
   }
   */
};


// ADDITION AND SUBTRACTION //

inline vec2d operator + ( vec2d first, vec2d second ) {
   return vec2d( first.x + second.x, first.y + second.y );
}


inline vec2d operator - ( vec2d first, vec2d second ) {
   return vec2d( first.x - second.x, first.y - second.y );
}


// MULTIPLICATION AND DIVISION

inline vec2d operator * ( vec2d vec, float factor ) {
   return vec2d( factor * vec.x, factor * vec.y );
}


inline vec2d operator * ( float factor, vec2d vec ) {
   return vec2d( factor * vec.x, factor * vec.y );
}


inline vec2d operator / ( vec2d vec, float divisor ) {
   return vec2d( vec.x / divisor, vec.y / divisor );
}


// DOT PRODUCT //

inline float operator * ( vec2d first, vec2d second ) {
   return first.x * second.x + first.y * second.y;
}


// SIGN //

inline vec2d operator - ( vec2d vec ) {
   return vec2d( -vec.x, -vec.y );
}


// NORMALIZATION

inline vec2d operator ~ ( vec2d vec ) {
   return vec.Normalized();
}


// TESTS


// Checks if the points are in counter clockwise order //

inline bool IsCounterClockwise( const vec2d first, const vec2d second, const vec2d third ) {
  float dx1, dx2, dy1, dy2;

  dx1 = second.x - first.x;
  dy1 = second.y - first.y;
  dx2 = third.x - second.x;
  dy2 = third.y - second.y;

  return dy1*dx2 < dy2*dx1;
}













#endif