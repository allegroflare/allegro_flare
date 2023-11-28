



#include <AllegroFlare/Placement2D.hpp>

#include <sstream>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>



#include <iostream>
#include <AllegroFlare/Color.hpp>



// from Andre LeMothe's "Tricks of the Windows Game Programming Gurus"

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}




static float cross2d(float ax, float ay, float bx, float by)
{
    return ax * by - ay * bx;
}



static bool line_line_collision2d(
      float l1x1, float l1y1, float l1x2, float l1y2, float l2x1, float l2y1, float l2x2, float l2y2
   )
{
    float ax = l1x2 - l1x1;
    float ay = l1y2 - l1y1;
    float bx = l2x2 - l2x1;
    float by = l2y2 - l2y1;
    float cx = l2x1 - l1x1;
    float cy = l2y1 - l1y1;
    float ab = cross2d(ax, ay, bx, by);
    float ca = cross2d(cx, cy, ax, ay);
    float cb = cross2d(cx, cy, bx, by);
    if (ab == 0) {
        return 0;
    }
    if (ab < 0) {
        if (ca > 0 || cb > 0) {
            return 0;
        }
        if (ca < ab || cb < ab) {
            return 0;
        }
    }
    else {
        if (ca < 0 || cb < 0) {
            return 0;
        }
        if (ca > ab || cb > ab) {
            return 0;
        }
    }
    return 1;
}



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
{}




Placement2D::Placement2D(float x, float y, float w, float h)
   : position(x, y)
   , size(w, h)
   , align(0.5, 0.5)
   , scale(1, 1)
   , anchor(0, 0)
   , flip(false, false)
   , rotation(0)
{}




Placement2D::Placement2D(float x, float y, float w, float h, float rotation, float scale_x, float scale_y, float align_x, float align_y, float anchor_x, float anchor_y)
   : position(x, y)
   , size(w, h)
   , align(align_x, align_y)
   , scale(scale_x, scale_y)
   , anchor(anchor_x, anchor_y)
   , flip(false, false)
   , rotation(rotation)
{}



void Placement2D::scale_to_fit_width(float target_width)
{
   // TODO: Test this function
   // TODO: Have divide by zero to set scale to 0.0f or other if alternative scale is better
   // TODO: Consider negative width/height
   if (size.x == 0.0f) scale.x = scale.y = 1.0f;

   float new_scale_x = target_width / size.x;
   scale.x = new_scale_x;
   scale.y = new_scale_x;
}



void Placement2D::scale_to_fit_height(float target_height)
{
   // TODO: Test this function
   // TODO: Have divide by zero to set scale to 0.0f or other if alternative scale is better
   // TODO: Consider negative width/height
   if (size.y == 0.0f) scale.x = scale.y = 1.0f;

   float new_scale_y = target_height / size.y;
   scale.x = new_scale_y;
   scale.y = new_scale_y;
}



void Placement2D::scale_to_fit_width_or_height(float target_width, float target_height)
{
   // TODO: Test this function
   // TODO: Have divide by zero to set scale to 0.0f or other if alternative scale is better
   // TODO: Consider negative width/height
   if (size.x == 0.0f || size.y == 0.0f) scale.x = scale.y = 1.0f;

   float new_scale_x = target_width / size.x;
   float new_scale_y = target_height / size.y;

   if (new_scale_x < new_scale_y) new_scale_y = new_scale_x;
   else new_scale_x = new_scale_y;

   scale.x = new_scale_x;
   scale.y = new_scale_y;
}



void Placement2D::scale_to_fill_width_or_height(float target_width, float target_height)
{
   // TODO: Test this function
   // TODO: Have divide by zero to set scale to 0.0f or other if alternative scale is better
   // TODO: Consider negative width/height
   if (size.x == 0.0f || size.y == 0.0f) scale.x = scale.y = 1.0f;

   float new_scale_x = target_width / size.x;
   float new_scale_y = target_height / size.y;

   if (new_scale_x > new_scale_y) new_scale_y = new_scale_x;
   else new_scale_x = new_scale_y; 

   scale.x = new_scale_x;
   scale.y = new_scale_y;
}



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


void Placement2D::place_coordinates(std::vector<AllegroFlare::Vec2D> *coordinates)
{
   if (!coordinates)
   {
      throw std::runtime_error("Placement2D:place_coordinates: error: coordinates cannot be null");
   }
   ALLEGRO_TRANSFORM transform;
   this->build_transform(&transform);

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



bool Placement2D::collide_as_if(ALLEGRO_BITMAP *bitmap, float x, float y)
{
   // TODO: this function that will check pixel-perfect collision as if the subject under placement is a bitmap
   if (bitmap == nullptr) return false;
   transform_coordinates(&x, &y);

   // to normal collide as a pre-check
   if (x < 0) return false;
   if (x > al_get_bitmap_width(bitmap)) return false;
   if (y < 0) return false;
   if (y > al_get_bitmap_height(bitmap)) return false;
   
   ALLEGRO_COLOR sample_color = al_get_pixel(bitmap, x, y);

   if (sample_color.a <= 0.001) return false;

   // TODO: consider more ellaborate anchor, scale, transforms on the bitmap

   // TODO: consider that size of the placement may not be considered in this context,
   // and still include checking bitmap

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



float Placement2D::get_leftmost_coordinate()
{
   std::vector<AllegroFlare::Vec2D> self_coordinates = {
      { 0,      0      }, // top left corner
      { size.x, 0      }, // top right corner
      { size.x, size.y }, // bottom right corner
      { 0,      size.y }, // bottom left corner
   };
   
   place_coordinates(&self_coordinates);

   float min_x = std::min({self_coordinates[0].x, self_coordinates[1].x, self_coordinates[2].x, self_coordinates[3].x});

   return min_x;
}



bool Placement2D::collide(AllegroFlare::Placement2D &other)
{
   std::vector<AllegroFlare::Vec2D> self_coordinates = {
      { 0,      0      }, // top left corner
      { size.x, 0      }, // top right corner
      { size.x, size.y }, // bottom right corner
      { 0,      size.y }, // bottom left corner
   };

   std::vector<AllegroFlare::Vec2D> other_coordinates = {
      { 0,            0            }, // top left corner
      { other.size.x, 0            }, // top right corner
      { other.size.x, other.size.y }, // bottom right corner
      { 0,            other.size.y }, // bottom left corner
   };

   place_coordinates(&self_coordinates);
   other.place_coordinates(&other_coordinates);

   for (auto &coordinate : self_coordinates)
   {
      al_draw_rectangle(coordinate.x-3, coordinate.y-3, coordinate.x+3, coordinate.y+3, AllegroFlare::Color::MintCream, 2.0);
   }
   for (auto &coordinate : other_coordinates)
   {
      al_draw_rectangle(coordinate.x-3, coordinate.y-3, coordinate.x+3, coordinate.y+3, AllegroFlare::Color::MintCream, 2.0);
   }

   float dummy_float = 1.0;
   bool collides_by_top_line
      = line_line_collision2d(
         self_coordinates[0].x, self_coordinates[0].y, self_coordinates[1].x, self_coordinates[1].y,
         other_coordinates[0].x, other_coordinates[0].y, other_coordinates[1].x, other_coordinates[1].y)
      || line_line_collision2d(
         self_coordinates[0].x, self_coordinates[0].y, self_coordinates[1].x, self_coordinates[1].y,
         other_coordinates[1].x, other_coordinates[1].y, other_coordinates[2].x, other_coordinates[2].y)
      || line_line_collision2d(
         self_coordinates[0].x, self_coordinates[0].y, self_coordinates[1].x, self_coordinates[1].y,
         other_coordinates[2].x, other_coordinates[2].y, other_coordinates[3].x, other_coordinates[3].y)
      || line_line_collision2d(
         self_coordinates[0].x, self_coordinates[0].y, self_coordinates[1].x, self_coordinates[1].y,
         other_coordinates[3].x, other_coordinates[3].y, other_coordinates[0].x, other_coordinates[0].y)
      ;

   if (collides_by_top_line) return true;

   bool collides_by_right_line
      = line_line_collision2d(
         self_coordinates[1].x, self_coordinates[1].y, self_coordinates[2].x, self_coordinates[2].y,
         other_coordinates[0].x, other_coordinates[0].y, other_coordinates[1].x, other_coordinates[1].y)
      || line_line_collision2d(
         self_coordinates[1].x, self_coordinates[1].y, self_coordinates[2].x, self_coordinates[2].y,
         other_coordinates[1].x, other_coordinates[1].y, other_coordinates[2].x, other_coordinates[2].y)
      || line_line_collision2d(
         self_coordinates[1].x, self_coordinates[1].y, self_coordinates[2].x, self_coordinates[2].y,
         other_coordinates[2].x, other_coordinates[2].y, other_coordinates[3].x, other_coordinates[3].y)
      || line_line_collision2d(
         self_coordinates[1].x, self_coordinates[1].y, self_coordinates[2].x, self_coordinates[2].y,
         other_coordinates[3].x, other_coordinates[3].y, other_coordinates[0].x, other_coordinates[0].y)
      ;

   if (collides_by_right_line) return true;

   bool collides_by_bottom_line
      = line_line_collision2d(
         self_coordinates[2].x, self_coordinates[2].y, self_coordinates[3].x, self_coordinates[3].y,
         other_coordinates[0].x, other_coordinates[0].y, other_coordinates[1].x, other_coordinates[1].y)
      || line_line_collision2d(
         self_coordinates[2].x, self_coordinates[2].y, self_coordinates[3].x, self_coordinates[3].y,
         other_coordinates[1].x, other_coordinates[1].y, other_coordinates[2].x, other_coordinates[2].y)
      || line_line_collision2d(
         self_coordinates[2].x, self_coordinates[2].y, self_coordinates[3].x, self_coordinates[3].y,
         other_coordinates[2].x, other_coordinates[2].y, other_coordinates[3].x, other_coordinates[3].y)
      || line_line_collision2d(
         self_coordinates[2].x, self_coordinates[2].y, self_coordinates[3].x, self_coordinates[3].y,
         other_coordinates[3].x, other_coordinates[3].y, other_coordinates[0].x, other_coordinates[0].y)
      ;

   if (collides_by_bottom_line) return true;

   bool collides_by_left_line
      = line_line_collision2d(
         self_coordinates[3].x, self_coordinates[3].y, self_coordinates[0].x, self_coordinates[0].y,
         other_coordinates[0].x, other_coordinates[0].y, other_coordinates[1].x, other_coordinates[1].y)
      || line_line_collision2d(
         self_coordinates[3].x, self_coordinates[3].y, self_coordinates[0].x, self_coordinates[0].y,
         other_coordinates[1].x, other_coordinates[1].y, other_coordinates[2].x, other_coordinates[2].y)
      || line_line_collision2d(
         self_coordinates[3].x, self_coordinates[3].y, self_coordinates[0].x, self_coordinates[0].y,
         other_coordinates[2].x, other_coordinates[2].y, other_coordinates[3].x, other_coordinates[3].y)
      || line_line_collision2d(
         self_coordinates[3].x, self_coordinates[3].y, self_coordinates[0].x, self_coordinates[0].y,
         other_coordinates[3].x, other_coordinates[3].y, other_coordinates[0].x, other_coordinates[0].y)
      ;

   if (collides_by_left_line) return true;

   bool other_vertex_is_inside = collide(other_coordinates[0].x, other_coordinates[0].y);
   if (other_vertex_is_inside) return true;

   bool self_vertex_is_inside_other = other.collide(self_coordinates[0].x, self_coordinates[0].y);
   if (self_vertex_is_inside_other) return true;

   return false;
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



Placement2D Placement2D::operator-(Placement2D& other)
{
   // TODO: Test this
   AllegroFlare::Placement2D result = *this;
   position -= other.position;
   size -= other.size;
   align -= other.align;
   scale -= other.scale;
   anchor -= other.anchor;
   rotation -= other.rotation;
   // flip.x and flip.y are ignored
   // however, they should flip whatever value is currently present if other.flip.x == true, or otherwise
   return *this;
}



Placement2D Placement2D::operator+(Placement2D& other)
{
   // TODO: Test this
   AllegroFlare::Placement2D result = *this;
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



} // namespace AllegroFlare



