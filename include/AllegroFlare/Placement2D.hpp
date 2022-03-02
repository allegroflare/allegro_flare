#pragma once



#include <string>
#include <allegro5/allegro.h>
#include <allegro_flare/vec2b.h> // TODO replace this
#include <AllegroFlare/Vec2D.hpp>




namespace AllegroFlare
{
   class Placement2D
   {
   private:
      ALLEGRO_TRANSFORM previous_transform;

   public:
      AllegroFlare::vec2d position, size, align, scale, anchor;
      allegro_flare::vec2b flip; // TODO: replace this
      float rotation;
      float &x, &y, &w, &h;  // for convience

      Placement2D();
      Placement2D(float x, float y, float w, float h);
      Placement2D(float x, float y, float w, float h, float rotation, float scale_x=1.0, float scale_y=1.0, float align_x=0.5, float align_y=0.5, float anchor_x=0.0, float anchor_y=0.0);

      void start_transform();
      void start_reverse_transform();
      void restore_transform();
      void build_transform(ALLEGRO_TRANSFORM *transform) const;
      void build_reverse_transform(ALLEGRO_TRANSFORM *transform) const;
      void draw_box(ALLEGRO_COLOR color, bool draw_origin);
      void draw_box_with_padding(ALLEGRO_COLOR color, bool draw_origin, float pt, float pr, float pb, float pl);
      void draw_origin();
      void clear();
      void transform_coordinates(float *x, float *y) const;
      void place_coordinates(float *x, float *y) const;
      bool collide(float x, float y) const;
      bool collide(float x, float y, float padding_top, float padding_right, float padding_bottom, float padding_left) const;
      std::string get_string();

      Placement2D& operator+=(Placement2D &other);
      Placement2D operator*(float f); // mostly used when Placement2D represents a velocity
   };
}




