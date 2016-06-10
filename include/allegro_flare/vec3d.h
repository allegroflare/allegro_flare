#ifndef __AF_VEC_3D_HEADER
#define __AF_VEC_3D_HEADER




#include <cmath>
#include <sstream>
#include <string>




// from OpenLayer //




class vec3d
{
public:
   float x, y, z;


   // CONSTRUCTORS //

   vec3d( float x = 0.0, float y = 0.0, float z = 0.0 )
      : x( x ), y( y ), z( z ) {}



   // METHODS //


   inline float get_magnitude() const {
      return std::sqrt( get_magnitude_squared() );
   }


   inline float get_magnitude_squared() const {
      return x * x + y * y + z * z;
   }


   inline vec3d normalized() const {
      float magnitude = get_magnitude();
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

   inline std::string to_string(int precision=5) const {
      std::ostringstream str;
      str.precision(precision);
      str << "( " << std::fixed << x << ", " << std::fixed << y << ", " << std::fixed << z << " )";
      return str.str();
   }

   inline std::string get_string() const {
      return to_string();
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
   return vec.normalized();
}




#endif
