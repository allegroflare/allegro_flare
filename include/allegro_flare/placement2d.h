#ifndef __AF_PLACEMENT_2D_HEADER
#define __AF_PLACEMENT_2D_HEADER




#include <string>
#include <allegro5/allegro.h>
#include <allegro_flare/vec2b.h>
#include <AllegroFlare/Vec2D.hpp>




namespace allegro_flare
{
   class placement2d
   {
   private:
      ALLEGRO_TRANSFORM previous_transform;

   public:
      AllegroFlare::vec2d position, size, align, scale, anchor;
      vec2b flip;
      float rotation;
      float &x, &y, &w, &h;  // for convience

      placement2d();
      placement2d(float x, float y, float w, float h);
      placement2d(float x, float y, float w, float h, float rotation, float scale_x=1.0, float scale_y=1.0, float align_x=0.5, float align_y=0.5, float anchor_x=0.0, float anchor_y=0.0);

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

      placement2d& operator+=(placement2d &other);
      placement2d operator*(float f); // mostly used when placement2d represents a velocity
   };
}



#endif
