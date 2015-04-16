#ifndef __AF_USEFUL_HEADER
#define __AF_USEFUL_HEADER






// defines a list of general purpose, useful utility functions


// parsing this file for documentation is like this
// here is the regular expression for a section header: \n//\n// .+\n(//.*\n)*//\n\n



#include <string>
#include <vector>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include <allegro_flare/vec2d.h>
#include <allegro_flare/vec3d.h>
#include <allegro_flare/color.h>



//
// General purpose functions
//

// macro that replaces previous usage of NULL
#define ALLEGRO_FLAGS_EMPTY 0

// TODO: change to #define
static const float FULL_ROTATION = 6.28318531;

// TODO: change to #define
static const float TAU = 6.28318531;

// convert from degrees to radians
float degrees_to_radians(float deg);

// convert from radians to degrees
float radians_to_degrees(float rad);

// returns true if the value of two floats are equivalent within a given threshold.
// Sometimes using the == operator between two floats might produce unexpected results
// doe to precision and rounding errors.  Using this function will help reduce that
// potential pitfall.
bool basically_equal(float v1, float v2, float threshold=0.00001f);







//
// Limits, bounds, and ranges
//

// returns a number who's value has been limited to be within (non-inclusive) a range
template<class T>
T limit(const T &range1, const T &range2, const T &val)
{
	float min = (range1 < range2) ? range1 : range2;
	float max = (range1 > range2) ? range1 : range2;
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

// finds if a value is within (non-inclusive) the given min and max ranges
template<class T>
bool in_range(const T &min, const T &max, const T &val)
{
	if (val < min) return false;
	if (val > max) return false;
	return true;
}

// returns the midpoint between two values
template<class T>
T mid(const T &val1, const T &val2)
{
	return (max(val1, val2) - min(val1, val2)) / 2.0 + min(val1, val2);
}

// returns the next greatest whole number if the given value is not a whole number itself; e.g. it rounds the number up.
float round(float val);

// returns true if the given string only contains characters that pass std::is_digit()
// TODO: rename this to to_int or something similar
bool is_number(const std::string& s); 

// will do a find using a binary search (your elements must already be ordered)
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

// converts a value to a string representation
template<class T>
std::string tostring(T val)
{
	std::ostringstream s;
	s << val;
	return s.str();
}

// returns a string with each character encoded in XML, e.g. #&x00fe;
std::string get_xml_encoded_ustr(ALLEGRO_USTR *ustr);

// escapes any XML characters in a string.  This is useful
// for passing complex arguments in a CURL command
std::string escape_xml_chars(std::string xml);

// converts an int32_t into the string hexidecimal representation of the number
// TODO should change this function name to to_hex_string() or something similar
std::string as_hex(int32_t num);

// given an array of strings, will return an array of ints
std::vector<int> to_int(const std::vector<std::string> &arr);

// returns the current datetime in "DD-MM-YYYY HH:MM:SS" format
// TODO: test in gcc
std::string get_datetime_str();








//
// Random generator functions
//

// returns a random true or false
bool random_bool();

// returns a random float between min and max (inclusive)
float random_float(float min, float max);

// returns a random double between min and max (inclusive)
double random_double(double min, double max);

// returns a random integer between min and max (inclusive)
int random_int(int min, int max);

// returns either a 1 or -1, selected at random
int random_sign();

// returns a random uppercase char 'A-Z'
// if lower=true, then it will return a random lowercase letter 'a-z'
unsigned char random_letter(bool lower);

// returns a char that is either an uppercase character 'A-Z', a lowercase character 'a-z', or a number character from '0-9'
unsigned char random_letter_or_number();

// generates a string of the size length consisting of randomly selected characters 'A-Za-z0-0'
// This is useful for generating random strings for identifiers or unique instances
// TODO: aaaagggghhh ;[ this is not funny tested
std::string random_string(unsigned int length);

// returns a randomly selected element from the vector
// WARNING: this function does not do any bounds checking.
// If the array is empty, this function will throw an out-of-bounds exception
template<class T>
T random_element(std::vector<T> &elements)
{
	return elements[random_int(0, elements.size())];
}

// returns a random selected element from an array of elements[]
// if the array is empty, it will throw an out-of-bounds exception
template<class T>
T random_element(T elements[], int size)
{
	return elements[random_int(0, size-1)];
}

// returns an ALLEGRO_COLOR with randomly picked RGB values
// TODO: this function is more useful for tests. Since the RGB values are generated
// independently, the colors that are typically generated fall into the middle of the
// color space.  A better, more 'random' color might integrate some color theory. 
ALLEGRO_COLOR random_color();







//
// Vector math functions (2d and 3d variants)
//

// basic vector math
float dot_product(vec3d A, vec3d B);
vec3d cross_product(vec3d A, vec3d B);

// returns a point projected onto an axis
vec2d project(vec2d &point, vec2d &axis);
vec3d project(vec3d point, vec3d point_on_plane, vec3d normal_of_plane);

// rotates a point by an angle
vec2d rotate_point(vec2d point, float angle);

// reflect a point along an axis
vec2d reflect(vec2d &point, const vec2d &axis);
vec3d reflect(vec3d &point, const vec3d &axis);

// calculate the distance between points using the distance formula
float distance(float x1, float y1, float x2, float y2);
float distance(const vec2d &point1, const vec2d &point2);
float distance(const vec2d *point1, const vec2d *point2);

// calculate the manhattan distance between points (google "Manhattan Distance")
// manhattan distance is a slightly faster (but less accurate) way to get the distance
float manhattan_distance(float x1, float y1, float x2, float y2);
float manhattan_distance(const vec2d *point1, const vec2d *point2);

// calculate the distance squared between points
// finding the distance squared is a fast calculation, you might use it to prune out
// *possible* collisions between objects before calculating a more accurate distance
// with the normal distance() formula
float distance_squared(const vec2d &point1, const vec2d &point2);

// draws a crosshair at a given coordinate on the screen
void draw_crosshair(float x, float y, ALLEGRO_COLOR color=al_color_name("white"));
void draw_crosshair(float x, float y, float z, ALLEGRO_COLOR col=color::black, float size=10);
void draw_crosshair(vec2d &point, ALLEGRO_COLOR color=al_color_name("white"));
void draw_crosshair(vec3d point, ALLEGRO_COLOR col=color::black, float size=10);









//
// Allegro utility functions
//

ALLEGRO_VERTEX build_vertex(float x, float y, float z, ALLEGRO_COLOR col, float u, float v);

void draw_textured_rectangle(float x, float y, float w, float h, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color=color::white);

void draw_offset_textured_rectangle(float x, float y, float w, float h, float offset_x, float offset_y, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color=color::white);

void draw_stretched_bitmap(float x, float y, float w, float h, ALLEGRO_BITMAP *bitmap, int flip_flags=ALLEGRO_FLAGS_EMPTY, ALLEGRO_COLOR color=color::white);

// might be obsolete?  look in the unique font drawing routines
void draw_unicode_char(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y);

// using a Motion object, this will modify a color so that it will crossfade between two colors
#include <allegro_flare/motion.h>
void animate_color(Motion *motion, ALLEGRO_COLOR *dest_color, const ALLEGRO_COLOR start, const ALLEGRO_COLOR end, double start_time, double duration, interpolator::interpolator_func_t interpolator_func);

// using the allegro functions, writes a screenshot.
// if the filename is left blank, then "screenshot-[time].png" will be generated
// as the filename
std::string take_screenshot(std::string filename="");

// using allegro, this will check if a key is currently pressed
bool key_pressed(int al_keycode);






//
// Filesystem functions
//

// using the allegro path addon, this will open a native dialogue box
// prompting the user to select a file.
// TODO: add an additional parameter limiting the file extensions
std::string pick_filename();

// get a listing of all the files in the directory
#include <iostream>
std::vector<std::string> get_directory_listing(std::string directory);






//
// javascript-like functions
// TODO: these should probably be moved to a useful_js.h or something similar
//

namespace javascript
{
	void alert(std::string message);
};













#endif

