

#include <AllegroFlare/Useful.hpp>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <locale>
#include <sstream>
#include <string>
#include <map>




namespace AllegroFlare
{
   float degrees_to_radians(float deg)
   {
      return ALLEGRO_PI * deg / 180.0f;
   }




   float radians_to_degrees(float rad)
   {
      return 180.0f / ALLEGRO_PI * rad;
   }




   void draw_crosshair(float x, float y, ALLEGRO_COLOR color, float size)
   {
      float half_size = size * 0.5;
      al_draw_line(x, y-half_size, x, y+half_size, color, 1.0);
      al_draw_line(x-half_size, y, x+half_size, y, color, 1.0);
   }




   void draw_crosshair(vec2d &point, ALLEGRO_COLOR color, float size)
   {
      float half_size = size * 0.5;
      al_draw_line(point.x, point.y-half_size, point.x, point.y+half_size, color, 1.0);
      al_draw_line(point.x-half_size, point.y, point.x+half_size, point.y, color, 1.0);
   }




   float distance(float x1, float y1, float x2, float y2)
   {
      return sqrt( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) ) ;
   }




   float distance(const vec2d &point1, const vec2d &point2)
   {
      return sqrt( ((point1.x - point2.x) * (point1.x - point2.x)) + ((point1.y - point2.y) * (point1.y - point2.y)) ) ;
   }




   float distance(const vec2d *point1, const vec2d *point2)
   {
      return sqrt( ((point1->x - point2->x) * (point1->x - point2->x)) + ((point1->y - point2->y) * (point1->y - point2->y)) ) ;
   }




   float manhattan_distance(const vec2d *point1, const vec2d *point2)
   {
      // may consider writing out the abs function
      return std::abs(point2->x - point1->x) + std::abs(point2->y - point1->y);
   }




   float manhattan_distance(float x1, float y1, float x2, float y2)
   {
      // may consider writing out the abs function
      return std::abs(x2 - x1) + std::abs(y2 - y1);
   }




   float distance_squared(const vec2d &point1, const vec2d &point2)
   {
      return ((point1.x - point2.x) * (point1.x - point2.x)) + ((point1.y - point2.y) * (point1.y - point2.y));
   }




   float random_float(float min, float max)
   {
      return ((float) rand()/RAND_MAX)*(max-min) + min;
   }




   double random_double(double min, double max)
   {
      return ((double) rand()/RAND_MAX)*(max-min) + min;
   }




   int random_int(int min, int max)
   {
      return rand()%(max-min+1) + min;
   }




   int random_int(std::vector<int> vals)
   {
      if (vals.empty()) return 0;
      return vals[random_int(0, vals.size()-1)];
   }




   bool random_bool()
   {
      return (rand()%2 == 1);
   }




   int random_sign()
   {
      return random_bool() ? 1 : -1;
   }




   unsigned char random_letter(bool lower)
   {
      if (lower) return (unsigned char)(rand()%26 + 'a');
      return (unsigned char)(rand()%26 + 'A');
   }




   unsigned char random_letter_or_number()
   {
      // TODO aaaaggghhh :[ not fully tested
      int num = random_int(0, 10+26+26); // 10 digits, 26 uppercase, 26 lowercase
      if (num <= 10) return (unsigned char)(rand()%10 + '0');
      else if ((num-10) <= 26) return (unsigned char)(rand()%26 + 'A');
      else if ((num-10-26) <= 26) return (unsigned char)(rand()%26 + 'a');
      return '-';
   }




   std::string random_string(unsigned int length)
   {
      std::string return_str;
      for (unsigned i=0; i<length; i++)
         return_str += random_letter_or_number();
      return return_str;
   }




   ALLEGRO_COLOR random_color()
   {
      return al_map_rgb(random_int(0, 255), random_int(0, 255), random_int(0, 255));
   }




   // returns a point projected onto an axis
   vec2d project(vec2d &point, vec2d &axis)
   {
      float somethun = (point.x * axis.x + point.y * axis.y)
         / (pow(axis.x, 2) + pow(axis.y, 2));
      return vec2d(somethun * axis.x, somethun * axis.y);
   }

   vec2d rotate_point(vec2d point, float angle)
   {
      return vec2d(point.x*cos(angle) - point.y*sin(angle), point.x*sin(angle) + point.y*cos(angle));
   }




   // reflect a point along an axis
   vec2d reflect(vec2d &point, const vec2d &axis)
   {
      float d = point * axis;
      return point - 2 * d * axis;
   }




   vec3d reflect(vec3d &point, const vec3d &axis) 
   {

      return -2 * (point * axis) * axis + point;

      //http://www.3dkingdoms.com/weekly/weekly.php?a=2
      // V is the "velocity" vector (or point, in this case)
      // N is the normal of the plane (axis, in this case)
      //b * ( -2*(V dot N)*N + V )
      // where b is bounce
   }




   float dot_product(vec3d A, vec3d B)
   {
      return A * B;
   }




   vec3d project(vec3d point, vec3d point_on_plane, vec3d normal_of_plane)
   {
      return point - dot_product(point - point_on_plane, normal_of_plane) * normal_of_plane;
   }




   vec3d cross_product(vec3d A, vec3d B)
   {
      //vec3d vector;
      //vector.x = A.y*B.z - B.y*A.z;
      //vector.y = B.x*A.z - A.x*B.z;
      //vector.z = A.x*B.y - A.y*B.x; 
      //return vector;
      return vec3d(A.y*B.z - B.y*A.z, B.x*A.z - A.x*B.z, A.x*B.y - A.y*B.x);
   }




   float round_up(float val)
   {
      return floor(val + 0.5f);
   }




   ALLEGRO_VERTEX build_vertex(float x, float y, float z, ALLEGRO_COLOR col, float u, float v)
   {
      ALLEGRO_VERTEX vertex;
      vertex.x = x, vertex.y = y, vertex.z = z, vertex.color = col, vertex.u = u, vertex.v = v;
      return vertex;
   }




   void draw_crosshair(float x, float y, float z, ALLEGRO_COLOR col, float size)
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




   void draw_crosshair(vec3d point, ALLEGRO_COLOR col, float size)
   {
      draw_crosshair(point.x, point.y, point.z, col, size);
   }




   void draw_textured_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color)
   {
      ALLEGRO_VERTEX v[4];

      v[0] = build_vertex(x1, y1, 0, color, x1-x1, y1-y1);
      v[1] = build_vertex(x2, y1, 0, color, x2-x1, y1-y1);
      v[2] = build_vertex(x2, y2, 0, color, x2-x1, y2-y1);
      v[3] = build_vertex(x1, y2, 0, color, x1-x1, y2-y1);

      al_draw_prim(v, NULL, texture, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
   }




   void draw_offset_textured_rectangle(float x1, float y1, float x2, float y2, float offset_x, float offset_y, ALLEGRO_BITMAP *texture, const ALLEGRO_COLOR &color)
   {
      ALLEGRO_VERTEX v[4];

      v[0] = build_vertex(x1, y1, 0, color, x1-x1+offset_x, y1-y1+offset_y);
      v[1] = build_vertex(x2, y1, 0, color, x2-x1+offset_x, y1-y1+offset_y);
      v[2] = build_vertex(x2, y2, 0, color, x2-x1+offset_x, y2-y1+offset_y);
      v[3] = build_vertex(x1, y2, 0, color, x1-x1+offset_x, y2-y1+offset_y);

      al_draw_prim(v, NULL, texture, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
   }




   void draw_stretched_bitmap(float x, float y, float w, float h, ALLEGRO_BITMAP *bitmap, int flip_flags, ALLEGRO_COLOR color)
   {
      al_draw_tinted_scaled_bitmap(bitmap, color, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
            x, y, w, h, flip_flags);
   }




   void draw_dashed_line(float x, float y, float x2, float y2, ALLEGRO_COLOR &col, float thickness)
   {
      float dash = 6;
      float space = 6;

      int segments = distance(x, y, x2, y2) / (dash+space);
      vec2d dir = vec2d(x2-x, y2-y).normalized();

      float dist_traveled = 0;
      for (int i=0; i<segments; i++)
      {
         al_draw_line(x + dir.x*dist_traveled, y + dir.y*dist_traveled,
               x + dir.x*dist_traveled + dir.x*dash, y + dir.y*dist_traveled + dir.y*dash, col, thickness);
         dist_traveled += (dash+space);
      }
      // draw last partial segment
      al_draw_line(x + dir.x*dist_traveled + dir.x*dash, y + dir.y*dist_traveled + dir.y*dash,
            x2, y2, col, thickness);
   }




   void animate_color(Motion *motion, ALLEGRO_COLOR *dest_color, const ALLEGRO_COLOR start, const ALLEGRO_COLOR end, double start_time, double duration, interpolator::interpolator_func_t interpolator_func)
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




   bool key_pressed(int al_keycode)
   {
      if (!al_is_system_installed()) return false;
      if (!al_is_keyboard_installed()) al_install_keyboard();

      ALLEGRO_KEYBOARD_STATE keyboard_state;
      al_get_keyboard_state(&keyboard_state);
      return al_key_down(&keyboard_state, al_keycode); 
   }




   std::vector<int> to_int(const std::vector<std::string> &arr)
   {
      std::vector<int> result;
      for (int i=0; i<(int)arr.size(); i++)
         result.push_back(atoi(arr[i].c_str()));
      return result;
   }




   bool basically_equal(float v1, float v2, float threshold)
   {
      if (std::abs(v1 - v2) > threshold) return false;
      return true;
   }




   std::vector<std::string> get_directory_listing(std::string directory)
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




   namespace javascript
   {

      void alert(std::string message)
      {
         al_show_native_message_box(al_get_current_display(), "Alert", "", message.c_str(), NULL, ALLEGRO_MESSAGEBOX_WARN);
      }

   };




   void draw_unicode_char(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
   {
      static ALLEGRO_USTR *ustr = NULL;
      if (!ustr) ustr = al_ustr_new("");
      al_ustr_set_chr(ustr, 0, icon);
      al_draw_ustr(font, color, x, y, flags, ustr);
   }




   std::string get_xml_encoded_ustr(ALLEGRO_USTR *ustr)
   {
      std::stringstream output;
      //al_ustr_get(const ALLEGRO_USTR *ub, int pos)
      for (unsigned i=0; i<al_ustr_length(ustr); i++)
      {
         output << "&#x" << al_ustr_get(ustr, i) << ";";
      }
      return output.str();
   }




   std::string escape_xml_chars(std::string xml)
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




   std::string as_hex(int32_t num)
   {
      std::stringstream stream;
      stream << std::hex << num;
      return stream.str();
   }




   bool is_number(const std::string& s) // this is closer to is int
   {
      std::locale loc;
      std::string::const_iterator it = s.begin();
      while (it != s.end() && std::isdigit(*it, loc)) ++it;
      return !s.empty() && it == s.end();
   }




   /// TODO: here are some new additions, they need to be categorized somewhere and the required headers should be placed above them




   std::string pick_filename()
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




   std::string get_datetime_str()
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




   std::string take_screenshot(std::string filename)
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
}


