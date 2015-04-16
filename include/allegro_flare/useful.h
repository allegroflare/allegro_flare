#ifndef __USEFUL_HEADER
#define __USEFUL_HEADER




#include <sstream>
#include <string>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include <allegro_flare/vec2d.h>
#include <allegro_flare/vec3d.h>
#include <allegro_flare/color.h>

#include <math.h>


#ifdef _MSC_VER
#define A_INLINE __inline
#else
#define A_INLINE static inline
#endif





#ifndef __FUNCTION__
#define __FUNCTION__ __func__
#endif





#define ALLEGRO_FLAGS_EMPTY 0




// this are keycodes for the Logitech Powerpoint Remote
// (note: the remote toggles between two different keys when the screen_play key is pressed) 
#define LOGITECH_REMOTE_BACK 80
#define LOGITECH_REMOTE_FORWARD 81
#define LOGITECH_REMOTE_SCREEN_PLAY_1 51
#define LOGITECH_REMOTE_SCREEN_PLAY_2 59
#define LOGITECH_REMOTE_SCREEN_BLACK 73
inline bool logitec_is_screen_play(int allegro_key)
{
	return ((allegro_key == LOGITECH_REMOTE_SCREEN_PLAY_2) || (allegro_key == LOGITECH_REMOTE_SCREEN_PLAY_1));
}



static const float FULL_ROTATION = 6.28318531;
static const float TAU = 6.28318531;







#define VALIDATE_AL_INIT() if (!al_is_system_installed()) { std::cout << "error [" << __FUNCTION__ << "]: allegro not initialized." << std::endl; }



A_INLINE float degrees_to_radians(float deg) { return ALLEGRO_PI * deg / 180.0f; }
A_INLINE float radians_to_degrees(float rad) { return 180.0f / ALLEGRO_PI * rad; }

A_INLINE void draw_crosshair(float x, float y, ALLEGRO_COLOR color=al_color_name("white"))
{
	float half_size = 12;
	al_draw_line(x, y-half_size, x, y+half_size, color, 1.0);
	al_draw_line(x-half_size, y, x+half_size, y, color, 1.0);
}

A_INLINE void draw_crosshair(vec2d &point, ALLEGRO_COLOR color=al_color_name("white"))
{
	float half_size = 5;
	al_draw_line(point.x, point.y-half_size, point.x, point.y+half_size, color, 1.0);
	al_draw_line(point.x-half_size, point.y, point.x+half_size, point.y, color, 1.0);
}







// this one is lower down:
//A_INLINE void draw_crosshair(vec3d point, ALLEGRO_COLOR col=color::black, float size=10)

A_INLINE float distance(float x1, float y1, float x2, float y2)
{
      return sqrt( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) ) ;
}

A_INLINE float distance(const vec2d &point1, const vec2d &point2)
{
      return sqrt( ((point1.x - point2.x) * (point1.x - point2.x)) + ((point1.y - point2.y) * (point1.y - point2.y)) ) ;
}

A_INLINE float distance(const vec2d *point1, const vec2d *point2)
{
      return sqrt( ((point1->x - point2->x) * (point1->x - point2->x)) + ((point1->y - point2->y) * (point1->y - point2->y)) ) ;
}

A_INLINE float manhattan_distance(const vec2d *point1, const vec2d *point2)
{
	// may consider writing out the abs function
	return abs(point2->x - point1->x) + abs(point2->y - point1->y);
}

A_INLINE float manhattan_distance(float x1, float y1, float x2, float y2)
{
	// may consider writing out the abs function
	return abs(x2 - x1) + abs(y2 - y1);
}

A_INLINE float distance_squared(const vec2d &point1, const vec2d &point2)
{
	return ((point1.x - point2.x) * (point1.x - point2.x)) + ((point1.y - point2.y) * (point1.y - point2.y));
}

A_INLINE float random_float(float min, float max)
{
    return ((float) rand()/RAND_MAX)*(max-min) + min;
}







A_INLINE double random_double(double min, double max)
{
    return ((double) rand()/RAND_MAX)*(max-min) + min;
}

A_INLINE int random_int(int min, int max)
{
    return rand()%(max-min+1) + min;
}

A_INLINE bool random_bool()
{
    return (rand()%2 == 1);
}

A_INLINE int random_sign()
{
    return random_bool() ? 1 : -1;
}


A_INLINE unsigned char random_letter(bool lower)
{
	if (lower) return (unsigned char)(rand()%26 + 'a');
	return (unsigned char)(rand()%26 + 'A');
}


A_INLINE unsigned char random_letter_or_number()
{
	// TODO aaaaggghhh :[ not fully tested
	int num = random_int(0, 10+26+26); // 10 digits, 26 uppercase, 26 lowercase
	if (num <= 10) return (unsigned char)(rand()%10 + '0');
	else if ((num-10) <= 26) return (unsigned char)(rand()%26 + 'A');
	else if ((num-10-26) <= 26) return (unsigned char)(rand()%26 + 'a');
	return '-';
}


A_INLINE std::string random_string(unsigned int length)
{
	std::string return_str;
	for (unsigned i=0; i<length; i++)
		return_str += random_letter_or_number();
	return return_str;
}



template<class T>
A_INLINE T random_element(std::vector<T> &elements)
{
	// TODO yikes does not bounds check
	return elements[random_int(0, elements.size())];
}


template<class T>
A_INLINE T random_element(T elements[], int size)
{
	return elements[random_int(0, size-1)];
}



A_INLINE ALLEGRO_COLOR random_color()
{
	return al_map_rgb(random_int(0, 255), random_int(0, 255), random_int(0, 255));
}





// returns a point projected onto an axis
A_INLINE vec2d project(vec2d &point, vec2d &axis)
{
	float somethun = (point.x * axis.x + point.y * axis.y)
	               / (pow(axis.x, 2) + pow(axis.y, 2));
	return vec2d(somethun * axis.x, somethun * axis.y);
}

A_INLINE vec2d rotate_point(vec2d point, float angle)
{
	return vec2d(point.x*cos(angle) - point.y*sin(angle), point.x*sin(angle) + point.y*cos(angle));
}





// reflect a point along an axis
A_INLINE vec2d reflect(vec2d &point, const vec2d &axis)
{
    float d = point * axis;
	return point - 2 * d * axis;
}

A_INLINE vec3d reflect(vec3d &point, const vec3d &axis) 
{

	return -2 * (point * axis) * axis + point;

	//http://www.3dkingdoms.com/weekly/weekly.php?a=2
	// V is the "velocity" vector (or point, in this case)
	// N is the normal of the plane (axis, in this case)
	//b * ( -2*(V dot N)*N + V )
	// where b is bounce
}





A_INLINE float dot_product(vec3d A, vec3d B)
{
	return A * B;
}

A_INLINE vec3d project(vec3d point, vec3d point_on_plane, vec3d normal_of_plane)
{
	return point - dot_product(point - point_on_plane, normal_of_plane) * normal_of_plane;
}

A_INLINE vec3d cross_product(vec3d A, vec3d B)
{
	//vec3d vector;
	//vector.x = A.y*B.z - B.y*A.z;
	//vector.y = B.x*A.z - A.x*B.z;
	//vector.z = A.x*B.y - A.y*B.x; 
	//return vector;
	return vec3d(A.y*B.z - B.y*A.z, B.x*A.z - A.x*B.z, A.x*B.y - A.y*B.x);
}






template<class T>
A_INLINE T limit(const T &range1, const T &range2, const T &val)
{
	float min = (range1 < range2) ? range1 : range2;
	float max = (range1 > range2) ? range1 : range2;
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

template<class T>
A_INLINE bool in_range(const T &min, const T &max, const T &val)
{
	if (val < min) return false;
	if (val > max) return false;
	return true;
}


template<class T>
A_INLINE T mid(const T &val1, const T &val2)
{
	return (max(val1, val2) - min(val1, val2)) / 2.0 + min(val1, val2);
}

A_INLINE float round(float val)
{
	return floor(val + 0.5f);
}









A_INLINE ALLEGRO_VERTEX build_vertex(float x, float y, float z, ALLEGRO_COLOR col, float u, float v)
{
	ALLEGRO_VERTEX vertex;
	vertex.x = x, vertex.y = y, vertex.z = z, vertex.color = col, vertex.u = u, vertex.v = v;
	return vertex;
}

A_INLINE void draw_crosshair(float x, float y, float z, ALLEGRO_COLOR col=color::black, float size=10)
{
	ALLEGRO_VERTEX v[6];
	float hsize = size/2;

	for (unsigned i=0; i<6; i++)
		v[i] = build_vertex(x, y, z, col, 0, 0);

	v[0].x -= hsize;
	v[1].x += hsize;

	v[2].y -= hsize;
	v[3].y += hsize;

	v[4].z -= hsize;
	v[5].z += hsize;

	al_draw_prim(&v, NULL, NULL, 0, 6, ALLEGRO_PRIM_LINE_LIST);
}

A_INLINE void draw_crosshair(vec3d point, ALLEGRO_COLOR col=color::black, float size=10)
{
	draw_crosshair(point.x, point.y, point.z, col, size);
}

A_INLINE void draw_textured_rectangle(float x, float y, float w, float h, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color=color::white)
{
	ALLEGRO_VERTEX v[4];
	v[0] = build_vertex(x, y, 0, color, 0, 0);
	v[1] = build_vertex(w, y, 0, color, w, 0);
	v[2] = build_vertex(w, h, 0, color, w, h);
	v[3] = build_vertex(x, h, 0, color, 0, h);

	//al_draw_filled_rounded_rectangle(0, 0, placement.w, placement.h, 3, 3, background_color);

	al_draw_prim(v, NULL, texture, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}

A_INLINE void draw_offset_textured_rectangle(float x, float y, float w, float h, float offset_x, float offset_y, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color=color::white)
{
	ALLEGRO_VERTEX v[4];
	v[0] = build_vertex(x, y, 0, color, 0+offset_x, 0+offset_y);
	v[1] = build_vertex(w, y, 0, color, w+offset_x, 0+offset_y);
	v[2] = build_vertex(w, h, 0, color, w+offset_x, h+offset_y);
	v[3] = build_vertex(x, h, 0, color, 0+offset_x, h+offset_y);

	//al_draw_filled_rounded_rectangle(0, 0, placement.w, placement.h, 3, 3, background_color);

	al_draw_prim(v, NULL, texture, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}


A_INLINE void draw_stretched_bitmap(float x, float y, float w, float h, ALLEGRO_BITMAP *bitmap, int flip_flags=ALLEGRO_FLAGS_EMPTY, ALLEGRO_COLOR color=color::white)
{
	al_draw_tinted_scaled_bitmap(bitmap, color, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
		x, y, w, h, flip_flags);
}



#include <allegro_flare/motion.h>

A_INLINE void animate_color(Motion *motion, ALLEGRO_COLOR *dest_color, const ALLEGRO_COLOR start, const ALLEGRO_COLOR end, double start_time, double duration, interpolator::interpolator_func_t interpolator_func)
{
	motion->clear_animations_on(&dest_color->r);
	motion->clear_animations_on(&dest_color->g);
	motion->clear_animations_on(&dest_color->b);
	motion->clear_animations_on(&dest_color->a);

	motion->animate(&dest_color->r, start.r, end.r, start_time, start_time+duration, interpolator_func, NULL, NULL);
	motion->animate(&dest_color->g, start.g, end.g, start_time, start_time+duration, interpolator_func, NULL, NULL);
	motion->animate(&dest_color->b, start.b, end.b, start_time, start_time+duration, interpolator_func, NULL, NULL);
	motion->animate(&dest_color->a, start.a, end.a, start_time, start_time+duration, interpolator_func, NULL, NULL);
}







//#include <allegro5/allegro.h>

A_INLINE bool key_pressed(int al_keycode)
{
	if (!al_is_system_installed()) return false;
	if (!al_is_keyboard_installed()) al_install_keyboard();

	ALLEGRO_KEYBOARD_STATE keyboard_state;
	al_get_keyboard_state(&keyboard_state);
	return al_key_down(&keyboard_state, al_keycode); 
}


template<class T>
A_INLINE std::string tostring(T val)
{
	std::ostringstream s;
	s << val;
	return s.str();
}







#include <allegro_flare/sha2.h>
#include <iostream>
#include <fstream>

A_INLINE std::string sha256_file(std::string filename)
{
	std::string data;
	std::ifstream input_file( filename.c_str(), std::ios::binary | std::ios::in );
	if( !input_file)
	{
		std::cout << "! Failed to open file \"filename\"" << std::endl;
		return "[error1]";
		// exit/return
	}

	std::ostringstream ss;
	ss << input_file.rdbuf();
	data = ss.str();

    std::string output = get_sha256_hash(data);

	input_file .close();

	return output;
}


#include <allegro_flare/md5.h>

A_INLINE std::string md5_file(std::string filename)
{
	std::string data;
	std::ifstream input_file( filename.c_str(), std::ios::binary | std::ios::in );
	if( !input_file)
	{
		std::cout << "! Failed to open file \"filename\"" << std::endl;
		return "[error1]";
		// exit/return
	}

	std::ostringstream ss;
	ss << input_file.rdbuf();
	data = ss.str();


	MD5 md5 = MD5(data);
 

	input_file .close();

	return md5.hexdigest();
}








#include <vector>
A_INLINE std::vector<int> to_int(const std::vector<std::string> &arr)
{
	std::vector<int> result;
	for (int i=0; i<(int)arr.size(); i++)
		result.push_back(atoi(arr[i].c_str()));
	return result;
}






template<class Iter, class T>
A_INLINE Iter binary_find(Iter begin, Iter end, T val)
{
    // Finds the lower bound in at most log(last - first) + 1 comparisons
    Iter i = std::lower_bound(begin, end, val);

    if (i != end && *i == val)
        return i; // found
    else
        return end; // not found
}







/// THE PHP CODE WAS ONCE HERE
/// THE PHP CODE WAS ONCE HERE
/// THE PHP CODE WAS ONCE HERE
/// THE PHP CODE WAS ONCE HERE
/// THE PHP CODE WAS ONCE HERE









/*
// my own functions
#include <tuple>

A_INLINE std::vector<std::tuple<int, std::string>> get_delimited_text(std::string text, std::string start_delim, std::string end_delim)
{
// tuple<position_of_the_string_content_that_was_found, content>
// example usaeg
//	std::string text = "In a world [where one man must fight to survive] all stuff is ok.";
//	std::vector<std::tuple<int, std::string>> results = get_delimited_text(text, "[", "]");
//	std::cout << results.size() << " matches found" << std::endl;
//	for (unsigned i=0; i<results.size(); i++)
//		std::cout << i << ": (" << std::get<0>(results[i]) << ") \"" << std::get<1>(results[i]) << "\"" << std::endl;

	std::vector<std::tuple<int, std::string>> results;
	size_t offset = 0;



	while(offset < text.size())
	{
		size_t start_pos = php::strpos(text, start_delim, offset);

		if (start_pos == std::string::npos) return results;

		size_t end_pos = php::strpos(text, end_delim, start_pos+start_delim.size());

		if (end_pos == std::string::npos) return results;

		if (start_pos == std::string::npos || end_pos == std::string::npos) return results;
	
		results.push_back(std::make_tuple(start_pos+start_delim.size(), text.substr(start_pos+start_delim.size(), end_pos - start_pos - start_delim.size())));

		offset = end_pos + end_delim.size();
	}

	return results;
}

*/






A_INLINE bool basically_equal(float v1, float v2, float threshold=0.00001f)
{
	if (abs(v1 - v2) > threshold) return false;
	return true;
}




#include <iostream>
A_INLINE std::vector<std::string> get_directory_listing(std::string directory)
{
	if (!al_is_system_installed()) al_init();

	std::vector<std::string> results;
    ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(directory.c_str());

    if(al_open_directory(dir))
    {
        ALLEGRO_FS_ENTRY* file;
        while((file=al_read_directory(dir)))
        {
			results.push_back(al_get_fs_entry_name(file));
            al_destroy_fs_entry(file);
        }
    }
	else
	{
		std::cout << "could not open directory \"" << directory << "\"" << std::endl;
	}

    al_destroy_fs_entry(dir);

	return results;
}







// javascript-like functions


namespace javascript
{

A_INLINE void alert(std::string message)
{
	al_show_native_message_box(al_get_current_display(), "Alert", "", message.c_str(), NULL, ALLEGRO_MESSAGEBOX_WARN);
}

};







// font symbol drawing functions

#include <allegro5/allegro_font.h>

A_INLINE void draw_unicode_char(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
{
	static ALLEGRO_USTR *ustr = NULL;
	if (!ustr) ustr = al_ustr_new("");
	al_ustr_set_chr(ustr, 0, icon);
	al_draw_ustr(font, color, x, y, flags, ustr);
}







// encoding / escaping / converting strings to



#include <string>
#include <sstream>
A_INLINE std::string get_xml_encoded_ustr(ALLEGRO_USTR *ustr)
{
	std::stringstream output;
	//al_ustr_get(const ALLEGRO_USTR *ub, int pos)
	for (unsigned i=0; i<al_ustr_length(ustr); i++)
	{
		output << "&#x" << al_ustr_get(ustr, i) << ";";
	}
	return output.str();
}






#include <string>
#include <map>
#include <iostream>
A_INLINE std::string escape_xml_chars(std::string xml)
{
    std::map<char, std::string> transformations;
    transformations['&']  = std::string("&amp;");
    transformations['\''] = std::string("&apos;");
    transformations['"']  = std::string("&quot;");
    transformations['>']  = std::string("&gt;");
    transformations['<']  = std::string("&lt;");

    // Build list of characters to be searched for.
    //
    std::string reserved_chars;
    for (std::map<char, std::string>::iterator ti = transformations.begin(); ti != transformations.end(); ti++)
    {
        reserved_chars += ti->first;
    }

    size_t pos = 0;
    while (std::string::npos != (pos = xml.find_first_of(reserved_chars, pos)))
    {
        xml.replace(pos, 1, transformations[xml[pos]]);
        pos++;
    }

	return xml;
}






#include <string>
#include <sstream>
A_INLINE std::string as_hex(int32_t num)
{
	std::stringstream stream;
	stream << std::hex << num;
	return stream.str();
}







#include <locale>
A_INLINE bool is_number(const std::string& s) // this is closer to is int
{
	std::locale loc;
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it, loc)) ++it;
    return !s.empty() && it == s.end();
}







/// TODO: here are some new additions, they need to be categorized somewhere and the required headers should be placed above them


A_INLINE std::string pick_filename()
{
	std::string picked_file = "";
	ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

	ALLEGRO_FILECHOOSER *filechooser =
		al_create_native_file_dialog(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP),
		"Pick a file",
		"*.bfs",
		ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);

	if (al_show_native_file_dialog(al_get_current_display(), filechooser))
	{
		picked_file = al_get_native_file_dialog_path(filechooser, 0);
	}

	// cleanup
	al_destroy_path(resource_path);
	al_destroy_native_file_dialog(filechooser);
	return picked_file;
}



#include <ctime>
#include <sstream>

A_INLINE std::string get_datetime_str()
	// returns the current datetime in "DD-MM-YYYY HH:MM:SS" format
{
  time_t rawtime;
  char buffer[80];
  std::string format = "%d-%m-%Y %I:%M:%S";

  time (&rawtime);

#if _MSC_VER && !__INTEL_COMPILER
  // msvc:
  struct tm timeinfo_ms;
  localtime_s(&timeinfo_ms, &rawtime);
  strftime(buffer,80,format.c_str(),&timeinfo_ms);
#else
  // TODO: validate this works in gcc
  // gcc:
  struct tm * timeinfo;
  timeinfo = localtime(&rawtime);
  strftime(buffer,80,format.c_str(),timeinfo);
#endif

  return std::string(buffer);
}

/*
A_INLINE std::string get_datetime_str()
{
    std::time_t result = std::time(nullptr);
//	std::stringstream ss;
//    ss << std::asctime(std::localtime(&result)); // << result << " seconds since the Epoch\n";
	
	//timeinfo = localtime(&rawtime);
    std::string temp = my_asctime(std::localtime(&result));
    return temp.substr(0,temp.size()-1); // yea, asctime adds a new-line '\n' char at the end... why?... wtf knows.
}
*/

#include <algorithm>

A_INLINE std::string take_screenshot(std::string filename="")
{
	ALLEGRO_STATE previous_state;
	al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

	ALLEGRO_DISPLAY *display = al_get_current_display();
	ALLEGRO_BITMAP *target = al_create_bitmap(al_get_display_width(display), al_get_display_height(display));
	al_set_target_bitmap(target);

	al_draw_bitmap(al_get_backbuffer(display), 0, 0, 0);

	al_restore_state(&previous_state);
	std::string temp_datetime_str = get_datetime_str();
	std::replace(temp_datetime_str.begin(), temp_datetime_str.end(), ':', ' ');

	if (filename.empty()) filename = tostring("screenshot-") + temp_datetime_str + ".png";

	al_save_bitmap(filename.c_str(), target);
	al_destroy_bitmap(target);

	return filename;
}







#endif
