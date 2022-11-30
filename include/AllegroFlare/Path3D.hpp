#pragma once


#include <vector>
#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/SegmentInfo3D.hpp>
#include <allegro5/allegro_primitives.h> // for ALLEGRO_VERTEX



namespace AllegroFlare
{
   class Path3D
   {
   public:
      // with this current method, "point" carries duplicate data also in "segment"

      std::vector<ALLEGRO_VERTEX> vertex;

      float length();
      float length_along(int first_index, int last_index);
      float length_to(int index);
      AllegroFlare::Vec3D at(int index);
      AllegroFlare::Vec3D &get_point(int index);
      AllegroFlare::Vec3D coordinate_at(float dist); // returns the point along the line, after traveling a distance of dist

      // filesys
      bool load(std::string filename); // should be extracted to a Path3DLoader
      bool save(std::string filename); // should be extracted to a Path3DLoader

      // generators
      Path3D *create_copy();
      Path3D *create_extrapolation(float radian, float theta); // extracts a new path with segments whose normals are within the angles
      // Copy constructor
      Path3D(const Path3D &source);

      // manipulations
      Path3D &add_point(float x, float y, bool refresh=true);
      Path3D &add_arc(float center_x, float center_y, float radius_x, float radius_y, float start_theta, float delta_theta, int num_segments, bool refresh=true);
      Path3D &make_arc(int first_index, float arc_strength, int num_segments, bool refresh=true);
      Path3D &concat(Path3D &path);
      Path3D &append(Path3D &path);
      Path3D &insert_point(unsigned at, float x, float y, bool refresh=true);
      Path3D &rotate(float angle);
      Path3D &rotate(float angle, float anchor_x, float anchor_y);
      Path3D &rotate(float angle, AllegroFlare::Vec3D pivot);
      Path3D &flip_h();
      Path3D &flip_v();
      Path3D &soften();
      Path3D &move(float x, float y);
      Path3D &scale(float s);
      Path3D &scale(float x, float y);
      Path3D &scale_to(float w, float h); //< has not been tested
      Path3D &resegment(int num_segments, bool refresh=true);
      //Path3D &resegment(int first_index, int last_index, int num_segments);
      Path3D &move_start_to(float x, float y);
      Path3D &to_origin();
      Path3D &move_end_to(float x, float y); // < todo
      const Path3D &copy_to(Path3D *dest) const;
      Path3D &clear();
      Path3D &roughen(float disp_range_x, float disp_range_y);
      Path3D &top_left(float x, float y);
      Path3D &bottom_right(float x, float y);
      Path3D &reverse();

      // for usage when this path represents a normal function
      bool within_range(float x);
      float get_y(float x);

      AllegroFlare::Vec3D top_left();
      AllegroFlare::Vec3D bottom_right();
      float width();
      float height();

      // presentation
      // should be extracted to a Path3DRenderer
      void draw(bool draw_points=false, bool show_normals=false, bool show_bounding_box=false, bool show_normal_angles=false, ALLEGRO_COLOR col=al_map_rgba_f(0,0,0,1.0), float thickness=2.0);

      // modifiers
      void set_shape_color(ALLEGRO_COLOR col);

      // all of these things should be considered internal
      AllegroFlare::Vec3D _top_left;
      AllegroFlare::Vec3D _bottom_right;
      std::vector<SegmentInfo3D *> segment;
      std::vector<AllegroFlare::Vec3D> point;
      float _length;

      void update_vertexs();
      //void draw_shape(ALLEGRO_BITMAP *image=NULL);
      // should be extracted to a Path3DRenderer
      void draw_shape(ALLEGRO_COLOR color);
      void draw_shape(float x, float y, ALLEGRO_COLOR color);
      void draw_outline(const ALLEGRO_COLOR &color, float thickness);
      void draw_outline(float x, float y, const ALLEGRO_COLOR &color, float thickness);

      Path3D();
      Path3D(std::string filename);
      ~Path3D();

      void refresh_segment_info();
   };
} // namespace AllegroFlare


