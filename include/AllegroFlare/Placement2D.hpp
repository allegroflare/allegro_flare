#pragma once



#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <AllegroFlare/Vec2B.hpp>
#include <AllegroFlare/Vec2D.hpp>




namespace AllegroFlare
{
   class Placement2D
   {
   private:
      ALLEGRO_TRANSFORM previous_transform;

   public:
      AllegroFlare::Vec2D position, size, align, scale, anchor;
      AllegroFlare::Vec2B flip;
      float rotation;

      Placement2D();
      Placement2D(float x, float y, float w, float h);
      Placement2D(float x, float y, float w, float h, float rotation, float scale_x=1.0, float scale_y=1.0, float align_x=0.5, float align_y=0.5, float anchor_x=0.0, float anchor_y=0.0);

      void scale_to_fit_width(float target_width);
      void scale_to_fit_height(float target_height);
      void scale_to_fit_width_or_height(float target_width, float target_height);
      void scale_to_fill_width_or_height(float target_width, float target_height);

      void start_transform();
      void start_reverse_transform();
      void restore_transform();
      void build_transform(ALLEGRO_TRANSFORM *transform);
      void build_reverse_transform(ALLEGRO_TRANSFORM *transform);
      void draw_box(ALLEGRO_COLOR color, bool draw_origin=false);
      void draw_box_with_padding(ALLEGRO_COLOR color, bool draw_origin, float pt, float pr, float pb, float pl);
      void draw_origin();
      void clear();
      void transform_coordinates(float *x, float *y);
      void transform_coordinates(std::vector<AllegroFlare::Vec2D> *coordinates);
      void place_coordinates(float *x, float *y);
      void place_coordinates(std::vector<AllegroFlare::Vec2D> *coordinates);

      bool in_range(float x, float y, float distance) const;
      bool collide(float x, float y);
      bool collide_as_if(ALLEGRO_BITMAP *bitmap, float x, float y);
      bool collide(float x, float y, float padding_top, float padding_right, float padding_bottom, float padding_left);
      bool collide(AllegroFlare::Placement2D &other); // should revise to a const &other

      float get_leftmost_coordinate();
      float get_rightmost_coordinate();
      float get_topmost_coordinate();
      float get_bottommost_coordinate();

      std::string get_string();

      Placement2D& operator+=(Placement2D &other);
      Placement2D operator-(Placement2D &other);
      Placement2D operator+(Placement2D &other);
      Placement2D operator*(float f); // mostly used when Placement2D represents a velocity
   };
}




