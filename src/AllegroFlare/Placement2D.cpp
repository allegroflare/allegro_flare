



#include <AllegroFlare/Placement2D.hpp>

#include <sstream>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>



namespace AllegroFlare
{
   Placement2D::Placement2D()
      : position(0, 0)
      , size(0, 0)
      , align(0.5, 0.5)
      , scale(1, 1)
      , anchor(0, 0)
      , flip(false, false)
      , rotation(0)
      //, x(position.x)
      //, y(position.y)
      //, w(size.x)
      //, h(size.y)
   {}




   Placement2D::Placement2D(float x, float y, float w, float h)
      : position(x, y)
      , size(w, h)
      , align(0.5, 0.5)
      , scale(1, 1)
      , anchor(0, 0)
      , flip(false, false)
      , rotation(0)
      //, x(position.x)
      //, y(position.y)
      //, w(size.x)
      //, h(size.y)
   {}




   Placement2D::Placement2D(float x, float y, float w, float h, float rotation, float scale_x, float scale_y, float align_x, float align_y, float anchor_x, float anchor_y)
      : position(x, y)
      , size(w, h)
      , align(align_x, align_y)
      , scale(scale_x, scale_y)
      , anchor(anchor_x, anchor_y)
      , flip(false, false)
      , rotation(rotation)
      //, x(position.x)
      //, y(position.y)
      //, w(size.x)
      //, h(size.y)
   {}




   void Placement2D::start_transform()
   {
      ALLEGRO_TRANSFORM transform;

      if (!al_get_current_transform()) return;
      al_copy_transform(&previous_transform, al_get_current_transform());

      this->build_transform(&transform);

      al_compose_transform(&transform, &previous_transform);
      al_use_transform(&transform);
   }



   void Placement2D::start_reverse_transform()
   {
      ALLEGRO_TRANSFORM transform;

      if (!al_get_current_transform()) return;
      al_copy_transform(&previous_transform, al_get_current_transform());

      this->build_reverse_transform(&transform);

      al_compose_transform(&transform, &previous_transform);
      al_use_transform(&transform);
   }



   void Placement2D::draw_origin()
   {
      float half_size = 12;
      ALLEGRO_COLOR color = al_map_rgba_f(1, 0, 0, 1);
      al_draw_line(position.x, position.y-half_size, position.x, position.y+half_size, color, 1.0);
      al_draw_line(position.x-half_size, position.y, position.x+half_size, position.y, color, 1.0);
   }




   void Placement2D::restore_transform()
   {
      if (!al_get_current_transform()) return;
      al_use_transform(&previous_transform);
   }




   void Placement2D::build_transform(ALLEGRO_TRANSFORM *transform)
   {
      al_identity_transform(transform);

      al_translate_transform(transform, -align.x*size.x, -align.y*size.y);
      al_scale_transform(transform, scale.x * (flip.get_x() ? -1 : 1), scale.y * (flip.get_y() ? -1 : 1));
      al_translate_transform(transform, anchor.x, anchor.y);
      al_rotate_transform(transform, rotation);
      al_translate_transform(transform, position.x, position.y);
   }




   void Placement2D::build_reverse_transform(ALLEGRO_TRANSFORM *transform)
   {
      al_identity_transform(transform);

      al_translate_transform(transform, -position.x, -position.y);
      al_rotate_transform(transform, -rotation);
      al_translate_transform(transform, -anchor.x, -anchor.y);
      al_scale_transform(transform, 1.0/scale.x * (flip.get_x() ? -1 : 1), 1.0/scale.y * (flip.get_y() ? -1 : 1));
      al_translate_transform(transform, align.x*size.x, align.y*size.y);
   }




   void Placement2D::draw_box(ALLEGRO_COLOR color, bool draw_origin)
   {
      if (draw_origin) al_draw_circle(position.x, position.y, 5, color, 3.0);
      start_transform();
      al_draw_rectangle(0, 0, size.x, size.y, color, 3.0);
      restore_transform();
   }




   void Placement2D::draw_box_with_padding(ALLEGRO_COLOR color, bool draw_origin, float pt, float pr, float pb, float pl)
   {
      if (draw_origin) al_draw_circle(position.x, position.y, 5, color, 3.0);
      start_transform();
      al_draw_rectangle(0, 0, size.x, size.y, color, 3.0);
      al_draw_rectangle(-pl, -pt, size.x+pr, size.y+pb, al_map_rgba_f(color.r*0.5, color.g*0.5, color.b*0.5, color.a*0.5), 3.0);
      restore_transform();
   }




   void Placement2D::transform_coordinates(float *xx, float *yy)
   {
      ALLEGRO_TRANSFORM transform;
      this->build_transform(&transform);

      al_invert_transform(&transform);
      al_transform_coordinates(&transform, xx, yy);
   }



   void Placement2D::transform_coordinates(std::vector<AllegroFlare::Vec2D> *coordinates)
   {
      if (!coordinates)
      {
         throw std::runtime_error("Placement2D:transform_coordinates: error: coordinates cannot be null");
      }
      ALLEGRO_TRANSFORM transform;
      this->build_transform(&transform);

      al_invert_transform(&transform);
      for (auto &coordinate : *coordinates)
      {
         al_transform_coordinates(&transform, &coordinate.x, &coordinate.y);
      }
   }



   void Placement2D::place_coordinates(float *x, float *y)
   {
      ALLEGRO_TRANSFORM transform;
      this->build_transform(&transform);

      al_transform_coordinates(&transform, x, y);
   }



   bool Placement2D::in_range(float x, float y, float distance) const
   {
      return (x-position.x) * (x-position.x) + (y-position.y) * (y-position.y) < (distance * distance);
   }



   bool Placement2D::collide(float x, float y)
   {
      transform_coordinates(&x, &y);

      if (x < 0) return false;
      if (x > size.x) return false;
      if (y < 0) return false;
      if (y > size.y) return false;
      return true;
   }




   bool Placement2D::collide(float x, float y, float padding_top, float padding_right, float padding_bottom, float padding_left)
   {
      transform_coordinates(&x, &y);

      if (x < -padding_left) return false;
      if (x > size.x+padding_right) return false;
      if (y < -padding_top) return false;
      if (y > size.y+padding_bottom) return false;
      return true;
   }




   void Placement2D::clear()
   {
      position.x = 0;
      position.y = 0;
      align.x = 0.5;
      align.y = 0.5;
      rotation = 0;
      flip.set_x(false);
      flip.set_y(false);
      scale.x = 1;
      scale.y = 1;
      size.x = 1;
      size.y = 1;
      anchor.x = 0;
      anchor.y = 0;
   }




   std::string Placement2D::get_string()
   {
      std::stringstream ss;
      ss << "x" << position.x << " y" << position.y << " w" << size.x << " h" << size.y;
      return ss.str();
   }




   Placement2D& Placement2D::operator+=(Placement2D& other)
   {
      position += other.position;
      size += other.size;
      align += other.align;
      scale += other.scale;
      anchor += other.anchor;
      rotation += other.rotation;
      // flip.x and flip.y are ignored
      // however, they should flip whatever value is currently present if other.flip.x == true, or otherwise
      return *this;
   }




   Placement2D Placement2D::operator*(float f)
   {
      Placement2D place = *this;
      position *= f;
      size *= f;
      align *= f;
      scale *= f;
      anchor *= f;
      rotation *= f;
      // flip.x and flip.y are ignored
      return place;
   }
}




