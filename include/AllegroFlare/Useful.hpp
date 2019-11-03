#pragma once


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Motion.hpp>


namespace AllegroFlare
{
   //
   // General purpose functions
   //

   // macro that replaces previous usage of NULL.
#define ALLEGRO_FLAGS_EMPTY 0

   // TODO: change to #define.
   static const float FULL_ROTATION = 6.28318531;

   // TODO: change to #define.
   static const float TAU = 6.28318531;

   // Converts a value from degrees to radians.
   float degrees_to_radians(float deg);

   // Converts a value from radians to degrees.
   float radians_to_degrees(float rad);

   // Returns true if the value of two floats are equivalent within a given threshold.
   // Sometimes using the == operator between two floats might produce unexpected results
   // doe to precision and rounding errors.  Using this function will help reduce that
   // potential pitfall.
   bool basically_equal(float v1, float v2, float threshold=0.00001f);




   //
   // Limits, bounds, and ranges
   //

   // Returns a number whose value has been limited to be within (non-inclusive) a range.
   template<class T>
   T clamp(const T &range1, const T &range2, const T &val)
   {
      float min = (range1 < range2) ? range1 : range2;
      float max = (range1 > range2) ? range1 : range2;
      if (val < min) return min;
      if (val > max) return max;
      return val;
   }

   // Finds if a value is within (non-inclusive) the given min and max ranges.
   template<class T>
   bool in_range(const T &min, const T &max, const T &val)
   {
      if (val < min) return false;
      if (val > max) return false;
      return true;
   }

   // Returns the midpoint between two values.
   template<class T>
   T mid(const T &val1, const T &val2)
   {
      return (max(val1, val2) - min(val1, val2)) / 2.0 + min(val1, val2);
   }

   // Returns the next greatest whole number if the given value is not a whole number itself; e.g. it rounds the number up.
   float round_up(float val);

   // Returns true if the given string only contains characters that pass `std::is_digit()`.
   // TODO: rename this to to_int or something similar
   bool is_number(const std::string& s); 

   // Finds an element matching `val` using a binary search (your elements must already be ordered).
   // TODO: this function is unfinished
   template<class Iter, class T>
   inline Iter binary_find(Iter begin, Iter end, T val)
   {
      // Finds the lower bound in at most log(last - first) + 1 comparisons
      Iter i = std::lower_bound(begin, end, val);

      if (i != end && *i == val)
         return i; // found
      else
         return end; // not found
   }




   //
   // String utility functions
   // encoding / escaping / converting / formatting, etc
   //

   // Converts a value to a string representation.
   template<class T>
   std::string tostring(T val)
   {
      std::ostringstream s;
      s << val;
      return s.str();
   }

   // Returns a string with each character encoded in XML, e.g. #&x00fe;.
   std::string get_xml_encoded_ustr(ALLEGRO_USTR *ustr);

   // Escapes any XML characters in a string.  
   // This is useful for passing complex arguments in a CURL command.
   std::string escape_xml_chars(std::string xml);

   // Converts an int32_t into the string hexidecimal representation of the number.
   // TODO should change this function name to to_hex_string() or something similar.
   std::string as_hex(int32_t num);

   // Returns an array of ints given an array of strings..
   std::vector<int> to_int(const std::vector<std::string> &arr);

   // Returns the current datetime in "DD-MM-YYYY HH:MM:SS" format.
   // TODO: test in gcc
   std::string get_datetime_str();




   //
   // Random generator functions
   //

   // Returns a random boolean `true` or `false`.
   bool random_bool();

   // Returns a random float between `min` and `max` (inclusive).
   float random_float(float min, float max);

   // Returns a random double between min and max (inclusive).
   double random_double(double min, double max);

   // Returns a random integer between min and max (inclusive).
   int random_int(int min, int max);
   int random_int(std::vector<int> vals);

   // Returns either a 1 or -1, selected at random.
   int random_sign();

   // Returns a random uppercase char 'A-Z'.
   // If `lower=true`, then a random lowercase letter 'a-z' will be returned.
   unsigned char random_letter(bool lower);

   // Returns a char that is either an uppercase character 'A-Z', a lowercase character 'a-z', or a number character from '0-9'.
   unsigned char random_letter_or_number();

   // Generates a string of the size length consisting of randomly selected characters [A-Za-z0-0].
   // This is useful for generating random strings for identifiers or unique instances.
   // TODO: add functions for returning specific types of "random strings", e.g. random_identifier
   std::string random_string(unsigned int length);

   // Returns a randomly selected element from the vector.
   // If the vector is empty, unexpected things can happen and your program will most likely crash.
   // You should ensure that your vector is not empty before calling this function.
   template<class T>
   T random_element(std::vector<T> &elements)
   {
      return elements[random_int(0, elements.size()-1)];
   }

   // Returns a random selected element from an array of elements.
   // If the array is empty, unexpected things can happen and your program will most likely crash.
   // You should ensure that your array is not empty before calling this function.
   template<class T>
   T random_element(T elements[], int size)
   {
      return elements[random_int(0, size-1)];
   }

   // Returns an ALLEGRO_COLOR with randomly picked RGB values.
   // TODO: This function is more useful for tests. Since the RGB values are generated
   // independently, the colors that are typically generated fall into the middle of the
   // color space.  A better, more 'random' color might integrate some color theory. 
   ALLEGRO_COLOR random_color();




   //
   // Vector math functions (2d and 3d variants)
   //

   // Calculate the dot product between two vectors.
   float dot_product(vec3d A, vec3d B);

   // Calculate the cross product between two vectors.
   vec3d cross_product(vec3d A, vec3d B);

   // Returns a point projected onto an axis.
   vec2d project(vec2d &point, vec2d &axis);
   vec3d project(vec3d point, vec3d point_on_plane, vec3d normal_of_plane);

   // Rotates a point by an angle.
   vec2d rotate_point(vec2d point, float angle);

   // Reflects a point along an axis.
   vec2d reflect(vec2d &point, const vec2d &axis);
   vec3d reflect(vec3d &point, const vec3d &axis);

   // Calculates the distance between points.
   float distance(float x1, float y1, float x2, float y2);
   float distance(const vec2d &point1, const vec2d &point2);
   float distance(const vec2d *point1, const vec2d *point2);

   // Calculates the manhattan distance between points (google "Manhattan Distance").
   // Manhattan distance is a slightly faster (but less accurate) alternative to the distance formula.
   float manhattan_distance(float x1, float y1, float x2, float y2);
   float manhattan_distance(const vec2d *point1, const vec2d *point2);

   // Calculates the distance squared between points.
   // Finding the distance squared is a fast calculation, so you might use it to prune out
   // possible collisions between objects before calculating a more accurate distance
   // with the usual `distance()` function.
   float distance_squared(const vec2d &point1, const vec2d &point2);




   //
   // Allegro utility functions
   //

   // Draws a crosshair at a given coordinate on the screen.
   void draw_crosshair(float x, float y, ALLEGRO_COLOR color=al_color_name("white"), float size=10);
   void draw_crosshair(float x, float y, float z, ALLEGRO_COLOR col=color::black, float size=10);
   void draw_crosshair(vec2d &point, ALLEGRO_COLOR color=al_color_name("white"), float size=10);
   void draw_crosshair(vec3d point, ALLEGRO_COLOR col=color::black, float size=10);

   // Creates an ALLEGRO_VERTEX with the following parameters.
   ALLEGRO_VERTEX build_vertex(float x, float y, float z, ALLEGRO_COLOR col, float u, float v);

   // Draws a rectangle with the given texture.
   // The texture will tile if the rectangle extends beyond the width or height of the image.
   // The top left corner of the texture is aligned at `x` and `y` of the rectangle.  To define
   // an offset, use `draw_offset_textured_rectangle`.
   void draw_textured_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color=color::white);

   // Same as `draw_textured_rectangle`, but allows you to define an x and y offset for the texture.
   void draw_offset_textured_rectangle(float x1, float y1, float x2, float y2, float offset_x, float offset_y, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color=color::white);

   // Draws an image stretched to fit the given width and height.
   void draw_stretched_bitmap(float x, float y, float w, float h, ALLEGRO_BITMAP *bitmap, int flip_flags=ALLEGRO_FLAGS_EMPTY, ALLEGRO_COLOR color=color::white);

   // Draws a dashed line.
   void draw_dashed_line(float x, float y, float x2, float y2, ALLEGRO_COLOR &col, float thickness);

   // Draws a unicode character on the screen.
   // TODO: might be obsolete?  look in the unique font drawing routines.
   void draw_unicode_char(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y);

   // Initializes an animation on an `ALLEGRO_COLOR` so that it will crossfade between two colors.
//#include <AllegroFlare/Motion.hpp>
   void animate_color(Motion *motion, ALLEGRO_COLOR *dest_color, const ALLEGRO_COLOR start, const ALLEGRO_COLOR end, double start_time, double duration, interpolator::interpolator_func_t interpolator_func);

   // Captures a screenshot of the current display (e.g. the contents of the current program window) and writes the image to a file.
   // If the filename is left blank, then "screenshot-[time].png" will be generated
   // as the filename, where [time] is in the `YYYY-MM-DD HH-MM-SS` format.
   // This function uses the allegro library.
   std::string take_screenshot(std::string filename="");

   // Checks to see if a key is currently pressed.
   bool key_pressed(int al_keycode);




   //
   // Filesystem functions
   //

   // Opens a native dialogue box prompting the user to select a file.
   // This is a _blocking_ function and will halt any activity that is running in the
   // calling thread.  This function uses the allegro path addon.
   // TODO: add an additional parameter limiting the file extensions.
   std::string pick_filename();

   // Get a listing of all the files in the directory.
//#include <iostream>
   std::vector<std::string> get_directory_listing(std::string directory);




   //
   // javascript-like functions
   // TODO: these should probably be moved to a useful_js.h or something similar
   //

   namespace javascript
   {
      void alert(std::string message);
   };
}


