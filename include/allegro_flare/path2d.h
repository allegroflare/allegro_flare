#ifndef __AF_PATH_2D_HEADER
#define __AF_PATH_2D_HEADER




#include <vector>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Vec2D.hpp>



namespace allegro_flare
{
   class SegmentInfo
   {
   public:
      AllegroFlare::vec2d start;
      AllegroFlare::vec2d end;
      AllegroFlare::vec2d from_start;
      AllegroFlare::vec2d perpendicular;
      AllegroFlare::vec2d normal;
      AllegroFlare::vec2d middle;
      float radius;
      float length;

      SegmentInfo() {}
      SegmentInfo(AllegroFlare::vec2d &start, AllegroFlare::vec2d &end);
   };




   class path2d
   {
   public:
      // with this current method, "point" carries duplicate data also in "segment"

      std::vector<ALLEGRO_VERTEX> vertex;

      float length();
      float length_along(int first_index, int last_index);
      float length_to(int index);
      AllegroFlare::vec2d at(int index);
      AllegroFlare::vec2d &get_point(int index);
      AllegroFlare::vec2d coordinate_at(float dist); // returns the point along the line, after traveling a distance of dist

      // filesys
      bool load(std::string filename);
      bool save(std::string filename);

      // generators
      path2d *create_copy();
      path2d *create_extrapolation(float radian, float theta); // extracts a new path with segments whose normals are within the angles
      // Copy constructor
      path2d(const path2d &source);

      // manipulations
      path2d &add_point(float x, float y, bool refresh=true);
      path2d &add_arc(float center_x, float center_y, float radius_x, float radius_y, float start_theta, float delta_theta, int num_segments, bool refresh=true);
      path2d &make_arc(int first_index, float arc_strength, int num_segments, bool refresh=true);
      path2d &concat(path2d &path);
      path2d &append(path2d &path);
      path2d &insert_point(unsigned at, float x, float y, bool refresh=true);
      path2d &rotate(float angle);
      path2d &rotate(float angle, float anchor_x, float anchor_y);
      path2d &rotate(float angle, AllegroFlare::vec2d pivot);
      path2d &flip_h();
      path2d &flip_v();
      path2d &soften();
      path2d &move(float x, float y);
      path2d &scale(float s);
      path2d &scale(float x, float y);
      path2d &scale_to(float w, float h); //< has not been tested
      path2d &resegment(int num_segments, bool refresh=true);
      //path2d &resegment(int first_index, int last_index, int num_segments);
      path2d &move_start_to(float x, float y);
      path2d &to_origin();
      path2d &move_end_to(float x, float y); // < todo
      const path2d &copy_to(path2d *dest) const;
      path2d &clear();
      path2d &roughen(float disp_range_x, float disp_range_y);
      path2d &top_left(float x, float y);
      path2d &bottom_right(float x, float y);
      path2d &reverse();

      // for usage when this path represents a normal function
      bool within_range(float x);
      float get_y(float x);

      AllegroFlare::vec2d top_left();
      AllegroFlare::vec2d bottom_right();
      float width();
      float height();

      // presentation
      void draw(bool draw_points=false, bool show_normals=false, bool show_bounding_box=false, bool show_normal_angles=false, ALLEGRO_COLOR col=al_map_rgba_f(0,0,0,1.0), float thickness=2.0);

      // modifiers
      void set_shape_color(ALLEGRO_COLOR col);

      // all of these things should be considered internal
      AllegroFlare::vec2d _top_left;
      AllegroFlare::vec2d _bottom_right;
      std::vector<SegmentInfo *> segment;
      std::vector<AllegroFlare::vec2d> point;
      float _length;

      void update_vertexs();
      //void draw_shape(ALLEGRO_BITMAP *image=NULL);
      void draw_shape(ALLEGRO_COLOR color);
      void draw_shape(float x, float y, ALLEGRO_COLOR color);
      void draw_outline(const ALLEGRO_COLOR &color, float thickness);
      void draw_outline(float x, float y, const ALLEGRO_COLOR &color, float thickness);

      path2d();
      path2d(std::string filename);
      ~path2d();

      void refresh_segment_info();
   };
}



#endif
