



#include <AllegroFlare/Path3D.hpp>

#include <iostream>
#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <allegro5/allegro_primitives.h>




namespace AllegroFlare
{
   Path3D::Path3D()
      : _length(0.0f)
   { }




   Path3D::Path3D(std::string filename)
      : _length(0.0f)
   {
      load(filename);
   }




   Path3D::~Path3D()
   {
      clear();
   }




   Path3D &Path3D::add_point(float x, float y, float z, bool refresh)
   {
      point.push_back(AllegroFlare::Vec3D(x, y, z));
      if (point.size() == 1) _length = 0.0f;
      else
      {
         //throw std::runtime_error("Path3D::add_point this commented code not implemented");
         segment.push_back(new SegmentInfo3D(
            point[point.size()-2],
            point[point.size()-1]
          ));
         _length += segment.back()->length;
      }

      if (refresh) refresh_segment_info();

      return *this;
   }




   Path3D &Path3D::add_arc(float center_x, float center_y, float radius_x, float radius_y, float start_theta, float delta_theta, int num_segments, bool refresh)
      // this is a little dirty, might be able to speed it up somehow
   {
      if (num_segments >= 256)
      {
         std::cout << "[Path3D::add_arc] you can't have more than 256 segments." << std::endl;
         return *this;
      }
      float points[256];

      al_calculate_arc(&(points[0]), sizeof(float)*2, center_x, center_y,
            radius_x, radius_y, start_theta, delta_theta, 0, num_segments);

      for (int i=0; i<num_segments*2; i+=2) add_point(points[i], points[i+1], points[i+2], false);
      if (refresh) refresh_segment_info();

      return *this;
   }




   Path3D &Path3D::make_arc(int first_index, float arc_strength, int num_segments, bool refresh)
   {
      throw std::runtime_error("Path3D::make_arc not implemented");

      //float points[256];
      //num_segments++;

      //AllegroFlare::Vec3D arc_center = (point[first_index+1] + point[first_index]) / 2;
      //float radius = distance(point[first_index+1], point[first_index]) / 2;
      //float start_theta = (point[first_index+1] - arc_center).get_angle();
      //float end_theta = (point[first_index] - arc_center).get_angle();

      //al_calculate_arc(&(points[0]), sizeof(float)*2, arc_center.x, arc_center.y,
            //radius, radius, start_theta, start_theta-end_theta, 0, num_segments);

      //for (int i=2; i<(num_segments-1)*2; i+=2)
         //insert_point(first_index+1, points[i], points[i+1], true);
      //if (refresh) refresh_segment_info();

      return *this;
   }




   Path3D &Path3D::clear()
   {
      //for (int i=0; i<(int)point.size(); i++) delete point[i];
      for (unsigned i=0; i<segment.size(); i++) delete segment[i];
      point.clear();
      segment.clear();
      _length = 0;

      return *this;
   }




   Path3D &Path3D::concat(Path3D &path)
   {
      if (this == &path) { std::cout << "[Path3D::concat] cannot concat to self (line " + AllegroFlare::tostring(__LINE__) + ")"; return *this; } // prevent self-appending

      AllegroFlare::Vec3D displacement = point.back() - path.point.front();
      for (int i=0; i<(int)path.point.size(); i++)
         point.push_back(path.point[i] + displacement);
      _length += path._length;

      refresh_segment_info();

      return *this;
   }




   AllegroFlare::Vec3D Path3D::top_front_left() { return _top_front_left; }




   AllegroFlare::Vec3D Path3D::bottom_back_right() { return _bottom_back_right; }




   float Path3D::width() { return _bottom_back_right.x - _top_front_left.x; }




   float Path3D::height() { return _bottom_back_right.y - _top_front_left.y; }




   float Path3D::depth() { return _bottom_back_right.z - _top_front_left.z; }




   Path3D &Path3D::top_front_left(float x, float y, float z)
   {
      AllegroFlare::Vec3D disp = AllegroFlare::Vec3D(x, y, z) - _top_front_left;
      return move(disp.x, disp.y, disp.z);
   }




   // math might be wrong
   Path3D &Path3D::bottom_back_right(float x, float y, float z)
   {
      AllegroFlare::Vec3D disp = _bottom_back_right - AllegroFlare::Vec3D(x, y, z);
      return move(disp.x, disp.y, disp.z);
   }




   // this has not been tested
   Path3D &Path3D::insert_point(unsigned at, float x, float y, float z, bool refresh)
   {
      if (point.size() <= at)
      {
         std::cout << "[Path3D::insert] could not insert point at index "
                   << at << " - point.size() is " << point.size(); return *this;
      }

      point.insert(point.begin()+at, AllegroFlare::Vec3D(x, y, z));
      if (refresh) refresh_segment_info();

      return *this;
   }




   void Path3D::set_shape_color(ALLEGRO_COLOR col)
   {
      for (int i=0; i<(int)vertex.size(); i++)
      {
         vertex[i].color = col;
      }
   }




   Path3D &Path3D::append(Path3D &path)
   {
      if (this == &path) { std::cout << "[Path3D::append] cannot append to self (line " + AllegroFlare::tostring(__LINE__) + ")"; return *this; } // prevent self-appending

      for (int i=0; i<(int)path.point.size(); i++)
         point.push_back(path.point[i]);
      _length += path._length;

      refresh_segment_info();

      return *this;
   }




   AllegroFlare::Vec3D Path3D::coordinate_at(float dist)
   {
      // this can be optimized
      float len = 0.0f;

      if (point.empty()) return AllegroFlare::Vec3D(0, 0);
      if (dist < 0) return point.front();
      if (dist >= _length) return point.back();

      for (int i=1; i<(int)point.size(); i++)
      {
         len += segment[i-1]->length;
         if (dist < len)
         {
            float percentage = (segment[i-1]->length - (len - dist)) / segment[i-1]->length;
            return segment[i-1]->from_start * percentage + point[i-1];
         }
      }

      return AllegroFlare::Vec3D(0, 0);
   }




   Path3D &Path3D::rotate(float angle, float anchor_x, float anchor_y)
   {
      ALLEGRO_TRANSFORM t;
      al_build_transform(&t, anchor_x, anchor_y, 1.0, 1.0, angle);

      for (int i=0; i<(int)point.size(); i++)
         al_transform_coordinates(&t, &point[i].x, &point[i].y);

      refresh_segment_info();

      return *this;
   }




   Path3D &Path3D::rotate(float angle, AllegroFlare::Vec3D pivot)
   {
      return rotate(angle, pivot.x, pivot.y);
   }




   Path3D &Path3D::rotate(float angle)
   {
      throw std::runtime_error("Path3D::rotate not implemented");
      return rotate(angle, 0, 0);
   }




   Path3D &Path3D::flip_v()
   {
      // this can be optimized
      // one possibility is to add an "off switch" for update_segment_info, so it can be done at the end, instead of at each step
      AllegroFlare::Vec3D pos = this->_top_front_left;

      this->to_origin();

      for (unsigned i=0; i<point.size(); i++)
         this->point[i].y *= -1;

      refresh_segment_info(); // <-- needed to recalc the bounding box

      this->top_front_left(pos.x, pos.y, pos.z);

      return *this;
   }




   Path3D &Path3D::flip_h()
   {
      // this can be optimized
      // one possibility is to add an "off switch" for update_segment_info, so it can be done at the end, instead of at each step
      AllegroFlare::Vec3D pos = this->_top_front_left;

      this->to_origin();

      for (unsigned i=0; i<point.size(); i++)
         this->point[i].x *= -1;

      refresh_segment_info(); // <-- needed to recalc the bounding box

      this->top_front_left(pos.x, pos.y, pos.z);

      return *this;
   }




   Path3D &Path3D::reverse()
   {
      if (point.size() <= 1) return *this;

      std::vector<AllegroFlare::Vec3D> *newpoints = new std::vector<AllegroFlare::Vec3D>;

      for (int i=point.size()-1; i>=0; i--)
      {
         newpoints->push_back(point[i]);
      }

      clear();
      point = *newpoints;

      refresh_segment_info();

      return *this;
   }




   void Path3D::refresh_segment_info()
   {
      //if (_length<=1) return; // <-- I'm not sure why this was here
      if (point.size() <= 1) return; // <-- replaced it with this

      _length = 0;

      for (int i=0; i<(int)segment.size(); i++) delete segment[i];
      segment.clear();

      _top_front_left = point.front();
      _bottom_back_right = point.front();

      for (int i=1; i<(int)point.size(); i++)
      {
         segment.push_back(new SegmentInfo3D(point[i-1], point[i]));
         _length += segment.back()->length;

         if (point[i].x < _top_front_left.x) _top_front_left.x = point[i].x;
         if (point[i].x > _bottom_back_right.x) _bottom_back_right.x = point[i].x;
         if (point[i].y < _top_front_left.y) _top_front_left.y = point[i].y;
         if (point[i].y > _bottom_back_right.y) _bottom_back_right.y = point[i].y;
         if (point[i].z < _top_front_left.z) _top_front_left.z = point[i].z;
         if (point[i].z > _bottom_back_right.z) _bottom_back_right.z = point[i].z;
      }
   }




   float Path3D::length()
   {
      return _length;
   }




   Path3D &Path3D::soften()
   {
      throw std::runtime_error("Path3D::soften not implemented");

      ////////
      //// NOTE: This commented code is from the Path2D implementation (for reference)
      ////////

      //if (point.size() <= 1) return *this;

      //std::vector<AllegroFlare::Vec3D> *newpoints = new std::vector<AllegroFlare::Vec3D>;

      //// break each segment into 4 seperate segments
      //for (int i=1; i<(int)point.size(); i++)
      //{
         //newpoints->push_back(AllegroFlare::Vec3D((point[i]-point[i-1])*0.0 + point[i-1]));
         //newpoints->push_back(AllegroFlare::Vec3D((point[i]-point[i-1])*0.25 + point[i-1]));
         //newpoints->push_back(AllegroFlare::Vec3D((point[i]-point[i-1])*0.5 + point[i-1]));
         //newpoints->push_back(AllegroFlare::Vec3D((point[i]-point[i-1])*0.75 + point[i-1]));
      //}
      //newpoints->push_back(point[point.size()-1]);


      //// skip the first 2
      //// erase every other point
      //bool keep = true;
      //for (int i=1; i<(int)newpoints->size(); i++)
      //{
         //if (!keep)
         //{
            ////delete newpoints->at(i);
            //newpoints->erase(newpoints->begin()+i);
            //i--;
         //}
         //keep = !keep;
      //}
      //newpoints->push_back(AllegroFlare::Vec3D(point[point.size()-1]));

      ////delete newpoints->at(1);
      //newpoints->erase(newpoints->begin()+1);

      ////delete newpoints->at((int)newpoints->size()-2);
      //newpoints->erase(newpoints->end()-2);


      //// clear the current points
      //// and fill with the new points
      //clear();
      //point = *newpoints;

      //refresh_segment_info();

      return *this;
   }




   Path3D &Path3D::move(float x, float y, float z)
   {
      for (int i=0; i<(int)point.size(); i++)
      {
         point[i].x += x;
         point[i].y += y;
         point[i].z += z;
      }
      for (int i=0; i<(int)segment.size(); i++)
      {
         segment[i]->start.x += x;
         segment[i]->start.y += y;
         segment[i]->start.z += z;
         segment[i]->end.x += x;
         segment[i]->end.y += y;
         segment[i]->end.z += z;
         segment[i]->middle.x += x;
         segment[i]->middle.y += y;
         segment[i]->middle.z += z;
      }

      refresh_segment_info();

      return *this;
   }




   Path3D &Path3D::to_origin()
   {
      return this->move_start_to(0,0,0);
   }




   Path3D &Path3D::move_start_to(float x, float y, float z)
   {
      if (point.empty()) return *this;
      move(-point[0].x + x, -point[0].y + y, -point[0].z + z);

      return *this;
   }




   Path3D &Path3D::move_end_to(float x, float y, float z)
   {
      if (point.empty()) return *this;
      move(-point.back().x + x, -point.back().y + y, -point.back().z + z);

      return *this;
   }




   Path3D &Path3D::scale(float s)
   {
      return this->scale(s, s, s);
   }




   Path3D &Path3D::scale_to(float w, float h, float d)
   {
      return scale(w/width(), h/height(), d/depth());
   }




   Path3D &Path3D::scale(float x, float y, float z)
   {
      for (int i=0; i<(int)point.size(); i++)
      {
         point[i].x *= x;
         point[i].y *= y;
         point[i].z *= z;
      }
      refresh_segment_info();

      return *this;
   }




   // this function will take the whole path and split it into
   // num_segments of equal length, traveling along the path.
   Path3D &Path3D::resegment(int num_segments, bool refresh)
   {
      if (num_segments <= 1) return *this;

      std::vector<AllegroFlare::Vec3D> *newpoints = new std::vector<AllegroFlare::Vec3D>;

      //Vec3D p;
      for (int seg = 0; seg <= num_segments; seg++)
      {
         //std::cout << std::endl << _length * ((float)seg / num_segments);

         newpoints->push_back(AllegroFlare::Vec3D(
                  coordinate_at(_length * ((float)seg / num_segments))
                  ));
      }

      //std::cout << std::endl << point.size();
      clear();

      //std::cout << std::endl << this->length();
      point = *newpoints;

      if (refresh) refresh_segment_info();
      //std::cout << std::endl << this->length();

      return *this;
   }




   float Path3D::length_along(int first_index, int last_index)
   {
      float len = 0;

      if (first_index<0) return 0;
      if (first_index>=(int)point.size()) return 0;
      if (last_index<0) return 0;
      if ((first_index+last_index)>=(int)point.size()) return 0;
      if (last_index <= (first_index+1)) return 0;

      for (int i=first_index+1; i<=last_index; i++)
      {
         len += distance(point[i-1], point[i]);
      }

      return len;
   }




   float Path3D::length_to(int index)
   {
      if (index <= 0) return 0;
      if ((int)point.size() <= index) return 0;

      float len = 0;
      for (int i=1; i<=index; i++)
      {
         len += distance(point[i-1], point[i]);
      }

      return len;
   }




   void Path3D::draw(bool show_points, bool show_normals, bool show_bounding_box, bool show_normal_angles, ALLEGRO_COLOR col, float thickness)
   {
      if (point.size() <= 1) return;

      if (show_bounding_box)
      {
         al_draw_rectangle(
            _top_front_left.x,
            _top_front_left.y,
            _bottom_back_right.x,
            _bottom_back_right.y,
            al_color_name("yellow"),
            1.0
         );
      }

      for (int i=1; i<(int)point.size(); i++)
      {
         al_draw_line(point[i-1].x, point[i-1].y, point[i].x, point[i].y, col, thickness);
         if (show_points) al_draw_filled_circle(point[i-1].x, point[i-1].y, 2, al_color_name("dodgerblue"));
      }

      if (show_points) al_draw_filled_circle(point.front().x, point.front().y, 2, al_color_name("forestgreen"));
      if (show_points) al_draw_circle(point.back().x, point.back().y, 3, al_color_name("brown"), 1.0f);

      //float normal_length = 5;

      /*
      Text t;
      t.font(get_font("04B_03B_.TTF", -8)).align(0.5, 1.0);
      for (int i=0; i<(int)segment.size(); i++)
      {
         if (show_normals)
         al_draw_line(segment[i]->middle.x, segment[i]->middle.y,
         segment[i]->middle.x + segment[i]->normal.x * normal_length,
         segment[i]->middle.y + segment[i]->normal.y * normal_length,
         al_map_rgba_f(0.5, 0.5, 0, 1), 1.0);

         if (show_normal_angles)
         t.text(tostring((segment[i]->normal.GetAngle()))).position(segment[i]->middle.x, segment[i]->middle.y).print();
      }
      */
   }




   AllegroFlare::Vec3D Path3D::at(int index)
   {
      if (index < 0 || index >= (int)point.size()) return AllegroFlare::Vec3D(0,0);
      return point.at(index);
   }




   const Path3D &Path3D::copy_to(Path3D *dest) const
   {
      if (!dest) return *this;
      if (dest==this) return *this;

      dest->clear();

      for (int i=0; i<(int)point.size(); i++)
         dest->point.push_back(point[i]);

      dest->refresh_segment_info();

      dest->_length = _length;

      return *this;
   }




   Path3D *Path3D::create_copy()
   {
      Path3D *dest = new Path3D;

      dest->clear();

      for (int i=0; i<(int)point.size(); i++)
         dest->point.push_back(point[i]);

      dest->refresh_segment_info();

      dest->_length = _length;

      return dest;
   }




   bool Path3D::load(std::string filename)
   {
      clear();
      if (!AllegroFlare::php::file_exists(filename))
      {
         std::cout << "[Path3D::load] file not found."; return false;
      }
      std::vector<std::string> parts = AllegroFlare::php::explode("\n", AllegroFlare::php::file_get_contents(filename));
      for (int i=0; i<(int)parts.size(); i++)
      {
         //std::cout << parts[i] << std::endl;
         std::vector<std::string> coord_string = AllegroFlare::php::explode(" ", parts[i]);
         add_point(atof(coord_string[0].c_str()), atof(coord_string[1].c_str()), atof(coord_string[2].c_str()), false);
      }

      refresh_segment_info();
      return true;
   }




   bool Path3D::save(std::string filename)
   {
      std::string output = "";
      for (int i=0; i<(int)point.size(); i++)
      {
         output += AllegroFlare::tostring(point[i].x) + " " + AllegroFlare::tostring(point[i].y);
         if (i!=((int)point.size()-1)) output += "\n";
      }
      AllegroFlare::php::file_put_contents(filename, output);

      return true;
   }




   void Path3D::update_vertexs()
   {
      //vertex.resize(point.size());
      vertex.clear();

      ALLEGRO_COLOR col = al_color_name("white");

      ALLEGRO_VERTEX v;
      for (int i=0; i<(int)point.size(); i++)
      {
         vertex.push_back(v);
         vertex.back().x = point[i].x;
         vertex.back().y = point[i].y;
         vertex.back().z = 0;
         vertex.back().color = col;
         vertex.back().u = point[i].x;
         vertex.back().v = point[i].y;
      }
   }




   /*
   void Path3D::draw_shape(ALLEGRO_BITMAP *image)
   {
      static bool warned = false;
      if (vertex.empty()) { if (!warned) { warned = true; std::cout << std::endl << "[Path3D::draw_shape] attempting to draw empty() vertexes, did you remember to update_vertexs()?" << std::endl; } return; }
      al_draw_prim(&vertex[0], NULL, image, 0, vertex.size(), ALLEGRO_PRIM_TRIANGLE_FAN);
   }
   */




   void Path3D::draw_shape(ALLEGRO_COLOR color)
   {
      throw std::runtime_error("Path3D::draw_shape not implemented");
      al_draw_filled_polygon(&point[0].x, point.size(), color);
   }




   void Path3D::draw_shape(float x, float y, float z, ALLEGRO_COLOR color)
   {
      this->move(x, y, z);
      draw_shape(color);
      this->move(-x, -y, -z);
   }




   void Path3D::draw_outline(const ALLEGRO_COLOR &color, float thickness)
   {
      if (point.empty()) return;
      std::vector<AllegroFlare::Vec3D>::iterator previous_it = point.begin();
      for (std::vector<AllegroFlare::Vec3D>::iterator it=point.begin()+1; it!=point.end(); it++)
      {
         al_draw_line(it->x, it->y, previous_it->x, previous_it->y, color, thickness);
         previous_it = it;
      }
   }




   void Path3D::draw_outline(float x, float y, float z, const ALLEGRO_COLOR &color, float thickness)
   {
      this->move(x, y, z);
      draw_outline(color, thickness);
      this->move(-x, -y, -z);
   }




   Path3D *Path3D::create_extrapolation(float radian, float theta)
   {
      throw std::runtime_error("Path3D::create_extrapolation not implemented");

      ////////
      //// NOTE: This commented code is from the Path2D implementation (for reference)
      ////////

      //float angle = 0;
      //Path3D *result = new Path3D();

      //for (int i=0; i<(int)point.size()-1; i++)
      //{
         //angle = segment[i]->normal.get_angle();
         //std::cout << std::endl << i << " " << angle;
         //if (angle > radian && angle < radian+theta)
         //{
            //result->add_point(point[i].x, point[i].y, false);
            ////result->add_point(point[i]->x, point[i]->y, false);
         //}
      //}

      //std::cout << std::endl << result->point.size();

      ////result->refresh_segment_info();

      //return result;

      return nullptr;
   }




   Path3D::Path3D(const Path3D &source)
   {
      source.copy_to(this);
   }




   Path3D &Path3D::roughen(float disp_range_x, float disp_range_y)
   {
      AllegroFlare::Random random_number_generator;
      disp_range_x *= 0.5;
      disp_range_y *= 0.5;
      for (int i=0; i<(int)point.size(); i++)
      {
         point[i].x += random_number_generator.get_random_float(-disp_range_x, disp_range_x);
         point[i].y += random_number_generator.get_random_float(-disp_range_y, disp_range_y);
      }

      refresh_segment_info();
      return *this;
   }




   bool Path3D::within_range(float x)
   {
      if (point.empty()) return false;
      if (point.size() == 1) return false;
      if (x < point[0].x) return false;
      if (x > point[point.size()-1].x) return false;
      return true;
   }




   // assumes within_range() is true
   // this is too slow for practical real-time usage
   float Path3D::get_y(float x)
   {
      int lpoint_index = 0;
      AllegroFlare::Vec3D lpoint = point[lpoint_index];
      AllegroFlare::Vec3D rpoint;

      for (unsigned i=0; i<point.size(); i++)
      {
         if (point[i].x > x) break;
         lpoint_index = i;
      }

      lpoint = point[lpoint_index];
      if (lpoint_index >= ((int)point.size()-1)) rpoint = lpoint;
      else rpoint = point[lpoint_index+1];

      float percentage_between = (x - lpoint.x) / (rpoint.x - lpoint.x);
      AllegroFlare::Vec3D point = (rpoint - lpoint) * percentage_between + lpoint;
      return point.y;
   }
}


