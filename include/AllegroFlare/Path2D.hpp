#pragma once


#include <vector>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/SegmentInfo2D.hpp>
#include <allegro5/allegro_primitives.h> // for ALLEGRO_VERTEX



namespace AllegroFlare
{
   class Path2D
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
      bool load(std::string filename); // should be extracted to a Path2DLoader
      bool save(std::string filename); // should be extracted to a Path2DLoader

      // generators
      Path2D *create_copy();
      Path2D *create_extrapolation(float radian, float theta); // extracts a new path with segments whose normals are within the angles
      // Copy constructor
      Path2D(const Path2D &source);

      // manipulations
      Path2D &add_point(float x, float y, bool refresh=true);
      Path2D &add_arc(float center_x, float center_y, float radius_x, float radius_y, float start_theta, float delta_theta, int num_segments, bool refresh=true);
      Path2D &make_arc(int first_index, float arc_strength, int num_segments, bool refresh=true);
      Path2D &concat(Path2D &path);
      Path2D &append(Path2D &path);
      Path2D &insert_point(unsigned at, float x, float y, bool refresh=true);
      Path2D &rotate(float angle);
      Path2D &rotate(float angle, float anchor_x, float anchor_y);
      Path2D &rotate(float angle, AllegroFlare::vec2d pivot);
      Path2D &flip_h();
      Path2D &flip_v();
      Path2D &soften(bool as_loop=false);
      Path2D &move(float x, float y);
      Path2D &scale(float s);
      Path2D &scale(float x, float y);
      Path2D &scale_to(float w, float h); //< has not been tested
      Path2D &resegment(int num_segments, bool refresh=true);
      //Path2D &resegment(int first_index, int last_index, int num_segments);
      Path2D &move_start_to(float x, float y);
      Path2D &to_origin();
      Path2D &move_end_to(float x, float y); // < todo
      const Path2D &copy_to(Path2D *dest) const;
      Path2D &clear();
      Path2D &roughen(float disp_range_x, float disp_range_y);
      Path2D &top_left(float x, float y);
      Path2D &bottom_right(float x, float y);
      Path2D &reverse();

      // for usage when this path represents a normal function
      bool within_range(float x);
      float get_y(float x);

      AllegroFlare::vec2d top_left();
      AllegroFlare::vec2d bottom_right();
      float width();
      float height();

      float calculate_signed_area();

      // presentation
      // should be extracted to a Path2DRenderer
      void draw(bool draw_points=false, bool show_normals=false, bool show_bounding_box=false, bool show_normal_angles=false, ALLEGRO_COLOR col=al_map_rgba_f(0,0,0,1.0), float thickness=2.0);

      // modifiers
      void set_shape_color(ALLEGRO_COLOR col);

      // all of these things should be considered internal
      AllegroFlare::vec2d _top_left;
      AllegroFlare::vec2d _bottom_right;
      std::vector<SegmentInfo2D> segment;
      std::vector<AllegroFlare::vec2d> point;
      float _length;

      void update_vertexs();
      //void draw_shape(ALLEGRO_BITMAP *image=NULL);
      // should be extracted to a Path2DRenderer
      void draw_shape(ALLEGRO_COLOR color);
      void draw_shape(float x, float y, ALLEGRO_COLOR color);
      void draw_outline(const ALLEGRO_COLOR &color, float thickness);
      void draw_outline(float x, float y, const ALLEGRO_COLOR &color, float thickness);

      Path2D();
      Path2D(std::string filename);
      ~Path2D();

      void refresh_segment_info();
   };
} // namespace AllegroFlare



