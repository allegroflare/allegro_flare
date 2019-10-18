



#include <allegro_flare/path2d.h>

#include <iostream>
//#include <allegro_flare/text_object.h>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/UsefulPHP.hpp>




namespace allegro_flare
{
   SegmentInfo::SegmentInfo(AllegroFlare::vec2d &start, AllegroFlare::vec2d &end)
   {
      this->start = start;
      this->end = end;
      from_start = end - start;
      middle = from_start/2 + start;
      length = distance(start, end);
      radius = length/2;
      perpendicular = AllegroFlare::vec2d(-from_start.y, from_start.x);
      normal = ~-perpendicular;
   }




   path2d::path2d()
      : _length(0.0f)
   { }




   path2d::path2d(std::string filename)
      : _length(0.0f)
   {
      load(filename);
   }




   path2d::~path2d()
   {
      clear();
   }




   path2d &path2d::add_point(float x, float y, bool refresh)
   {
      point.push_back(AllegroFlare::vec2d(x, y));
      if (point.size() == 1) _length = 0.0f;
      else
      {
         segment.push_back(new SegmentInfo(point[point.size()-2], point[point.size()-1]));
         _length += segment.back()->length;
      }

      if (refresh) refresh_segment_info();

      return *this;
   }




   path2d &path2d::add_arc(float center_x, float center_y, float radius_x, float radius_y, float start_theta, float delta_theta, int num_segments, bool refresh)
      // this is a little dirty, might be able to speed it up somehow
   {
      if (num_segments >= 256)
      {
         std::cout << "[path2d::add_arc] you can't have more than 256 segments." << std::endl;
         return *this;
      }
      float points[256];

      al_calculate_arc(&(points[0]), sizeof(float)*2, center_x, center_y,
            radius_x, radius_y, start_theta, delta_theta, 0, num_segments);

      for (int i=0; i<num_segments*2; i+=2) add_point(points[i], points[i+1], false);
      if (refresh) refresh_segment_info();

      return *this;
   }




   path2d &path2d::make_arc(int first_index, float arc_strength, int num_segments, bool refresh)
   {
      float points[256];

      num_segments++;

      AllegroFlare::vec2d arc_center = (point[first_index+1] + point[first_index]) / 2;
      float radius = distance(point[first_index+1], point[first_index]) / 2;
      float start_theta = (point[first_index+1] - arc_center).get_angle();
      float end_theta = (point[first_index] - arc_center).get_angle();

      al_calculate_arc(&(points[0]), sizeof(float)*2, arc_center.x, arc_center.y,
            radius, radius, start_theta, start_theta-end_theta, 0, num_segments);

      for (int i=2; i<(num_segments-1)*2; i+=2)
         insert_point(first_index+1, points[i], points[i+1], true);
      //add_point(points[i], points[i+1], false);
      if (refresh) refresh_segment_info();

      return *this;
   }




   path2d &path2d::clear()
   {
      //for (int i=0; i<(int)point.size(); i++) delete point[i];
      for (unsigned i=0; i<segment.size(); i++) delete segment[i];
      point.clear();
      segment.clear();
      _length = 0;

      return *this;
   }




   path2d &path2d::concat(path2d &path)
   {
      if (this == &path) { std::cout << "[path2d::concat] cannot concat to self (line " + AllegroFlare::tostring(__LINE__) + ")"; return *this; } // prevent self-appending

      AllegroFlare::vec2d displacement = point.back() - path.point.front();
      for (int i=0; i<(int)path.point.size(); i++)
         point.push_back(path.point[i] + displacement);
      _length += path._length;

      refresh_segment_info();

      return *this;
   }




   AllegroFlare::vec2d path2d::top_left() { return _top_left; }




   AllegroFlare::vec2d path2d::bottom_right() { return _bottom_right; }




   float path2d::width() { return _bottom_right.x - _top_left.x; }




   float path2d::height() { return _bottom_right.y - _top_left.y; }




   path2d &path2d::top_left(float x, float y)
   {
      AllegroFlare::vec2d disp = AllegroFlare::vec2d(x, y) - _top_left;
      return move(disp.x, disp.y);
   }




   // math might be wrong
   path2d &path2d::bottom_right(float x, float y)
   {
      AllegroFlare::vec2d disp = _bottom_right - AllegroFlare::vec2d(x, y);
      return move(disp.x, disp.y);
   }




   // this has not been tested
   path2d &path2d::insert_point(unsigned at, float x, float y, bool refresh)
   {
      if (point.size() <= at) { std::cout << "[path2d::insert] could not insert point at index " << at << " - point.size() is " << point.size(); return *this; }

      point.insert(point.begin()+at, AllegroFlare::vec2d(x, y));
      if (refresh) refresh_segment_info();

      return *this;
   }




   void path2d::set_shape_color(ALLEGRO_COLOR col)
   {
      for (int i=0; i<(int)vertex.size(); i++)
      {
         vertex[i].color = col;
      }
   }




   path2d &path2d::append(path2d &path)
   {
      if (this == &path) { std::cout << "[path2d::append] cannot append to self (line " + AllegroFlare::tostring(__LINE__) + ")"; return *this; } // prevent self-appending

      for (int i=0; i<(int)path.point.size(); i++)
         point.push_back(path.point[i]);
      _length += path._length;

      refresh_segment_info();

      return *this;
   }




   AllegroFlare::vec2d path2d::coordinate_at(float dist)
   {
      // this can be optimized
      float len = 0.0f;

      if (point.empty()) return AllegroFlare::vec2d(0, 0);
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

      return AllegroFlare::vec2d(0, 0);
   }




   path2d &path2d::rotate(float angle, float anchor_x, float anchor_y)
   {
      ALLEGRO_TRANSFORM t;
      al_build_transform(&t, anchor_x, anchor_y, 1.0, 1.0, angle);

      for (int i=0; i<(int)point.size(); i++)
         al_transform_coordinates(&t, &point[i].x, &point[i].y);

      refresh_segment_info();

      return *this;
   }




   path2d &path2d::rotate(float angle, AllegroFlare::vec2d pivot)
   {
      return rotate(angle, pivot.x, pivot.y);
   }




   path2d &path2d::rotate(float angle)
   {
      return rotate(angle, 0, 0);
   }




   path2d &path2d::flip_v()
   {
      // this can be optimized
      // one possibility is to add an "off switch" for update_segment_info, so it can be done at the end, instead of at each step
      AllegroFlare::vec2d pos = this->_top_left;

      this->to_origin();

      for (unsigned i=0; i<point.size(); i++)
         this->point[i].y *= -1;

      refresh_segment_info(); // <-- needed to recalc the bounding box

      this->top_left(pos.x, pos.y);

      return *this;
   }




   path2d &path2d::flip_h()
   {
      // this can be optimized
      // one possibility is to add an "off switch" for update_segment_info, so it can be done at the end, instead of at each step
      AllegroFlare::vec2d pos = this->_top_left;

      this->to_origin();

      for (unsigned i=0; i<point.size(); i++)
         this->point[i].x *= -1;

      refresh_segment_info(); // <-- needed to recalc the bounding box

      this->top_left(pos.x, pos.y);

      return *this;
   }




   path2d &path2d::reverse()
   {
      if (point.size() <= 1) return *this;

      std::vector<AllegroFlare::vec2d> *newpoints = new std::vector<AllegroFlare::vec2d>;

      for (int i=point.size()-1; i>=0; i--)
      {
         newpoints->push_back(point[i]);
      }

      clear();
      point = *newpoints;

      refresh_segment_info();

      return *this;
   }




   void path2d::refresh_segment_info()
   {
      //if (_length<=1) return; // <-- I'm not sure why this was here
      if (point.size() <= 1) return; // <-- replaced it with this

      _length = 0;

      for (int i=0; i<(int)segment.size(); i++) delete segment[i];
      segment.clear();

      _top_left = point.front();
      _bottom_right = point.front();

      for (int i=1; i<(int)point.size(); i++)
      {
         segment.push_back(new SegmentInfo(point[i-1], point[i]));
         _length += segment.back()->length;

         if (point[i].x < _top_left.x) _top_left.x = point[i].x;
         if (point[i].x > _bottom_right.x) _bottom_right.x = point[i].x;
         if (point[i].y < _top_left.y) _top_left.y = point[i].y;
         if (point[i].y > _bottom_right.y) _bottom_right.y = point[i].y;
      }
   }




   float path2d::length()
   {
      return _length;
   }




   path2d &path2d::soften()
   {
      if (point.size() <= 1) return *this;

      std::vector<AllegroFlare::vec2d> *newpoints = new std::vector<AllegroFlare::vec2d>;

      // break each segment into 4 seperate segments
      for (int i=1; i<(int)point.size(); i++)
      {
         newpoints->push_back(AllegroFlare::vec2d((point[i]-point[i-1])*0.0 + point[i-1]));
         newpoints->push_back(AllegroFlare::vec2d((point[i]-point[i-1])*0.25 + point[i-1]));
         newpoints->push_back(AllegroFlare::vec2d((point[i]-point[i-1])*0.5 + point[i-1]));
         newpoints->push_back(AllegroFlare::vec2d((point[i]-point[i-1])*0.75 + point[i-1]));
      }
      newpoints->push_back(point[point.size()-1]);


      // skip the first 2
      // erase every other point
      bool keep = true;
      for (int i=1; i<(int)newpoints->size(); i++)
      {
         if (!keep)
         {
            //delete newpoints->at(i);
            newpoints->erase(newpoints->begin()+i);
            i--;
         }
         keep = !keep;
      }
      newpoints->push_back(AllegroFlare::vec2d(point[point.size()-1]));

      //delete newpoints->at(1);
      newpoints->erase(newpoints->begin()+1);

      //delete newpoints->at((int)newpoints->size()-2);
      newpoints->erase(newpoints->end()-2);


      // clear the current points
      // and fill with the new points
      clear();
      point = *newpoints;

      refresh_segment_info();

      return *this;
   }




   path2d &path2d::move(float x, float y)
   {
      for (int i=0; i<(int)point.size(); i++)
      {
         point[i].x += x;
         point[i].y += y;
      }
      for (int i=0; i<(int)segment.size(); i++)
      {
         segment[i]->start.x += x;
         segment[i]->start.y += y;
         segment[i]->end.x += x;
         segment[i]->end.y += y;
         segment[i]->middle.x += x;
         segment[i]->middle.y += y;
      }

      refresh_segment_info();

      return *this;
   }




   path2d &path2d::to_origin()
   {
      return this->move_start_to(0,0);
   }




   path2d &path2d::move_start_to(float x, float y)
   {
      if (point.empty()) return *this;
      move(-point[0].x + x, -point[0].y + y);

      return *this;
   }




   path2d &path2d::move_end_to(float x, float y)
   {
      if (point.empty()) return *this;
      move(-point.back().x + x, -point.back().y + y);

      return *this;
   }




   path2d &path2d::scale(float s)
   {
      return this->scale(s, s);
   }




   path2d &path2d::scale_to(float w, float h)
   {
      return scale(w/width(), h/height());
   }




   path2d &path2d::scale(float x, float y)
   {
      for (int i=0; i<(int)point.size(); i++)
      {
         point[i].x *= x;
         point[i].y *= y;
      }
      refresh_segment_info();

      return *this;
   }




   // this function will take the whole path and split it into
   // num_segments of equal length, traveling along the path.
   path2d &path2d::resegment(int num_segments, bool refresh)
   {
      if (num_segments <= 1) return *this;

      std::vector<AllegroFlare::vec2d> *newpoints = new std::vector<AllegroFlare::vec2d>;

      //vec2d p;
      for (int seg = 0; seg <= num_segments; seg++)
      {
         //std::cout << std::endl << _length * ((float)seg / num_segments);

         newpoints->push_back(AllegroFlare::vec2d(
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




   float path2d::length_along(int first_index, int last_index)
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




   float path2d::length_to(int index)
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




   void path2d::draw(bool show_points, bool show_normals, bool show_bounding_box, bool show_normal_angles, ALLEGRO_COLOR col, float thickness)
   {
      if (point.size() <= 1) return;

      if (show_bounding_box) al_draw_rectangle(_top_left.x, _top_left.y, _bottom_right.x, _bottom_right.y, al_color_name("yellow"), 1.0);

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




   AllegroFlare::vec2d path2d::at(int index)
   {
      if (index < 0 || index >= (int)point.size()) return AllegroFlare::vec2d(0,0);
      return point.at(index);
   }




   const path2d &path2d::copy_to(path2d *dest) const
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




   path2d *path2d::create_copy()
   {
      path2d *dest = new path2d;

      dest->clear();

      for (int i=0; i<(int)point.size(); i++)
         dest->point.push_back(point[i]);

      dest->refresh_segment_info();

      dest->_length = _length;

      return dest;
   }




   bool path2d::load(std::string filename)
   {
      clear();
      if (!AllegroFlare::php::file_exists(filename))
      {
         std::cout << "[path2d::load] file not found."; return false;
      }
      std::vector<std::string> parts = AllegroFlare::php::explode("\n", AllegroFlare::php::file_get_contents(filename));
      for (int i=0; i<(int)parts.size(); i++)
      {
         //std::cout << parts[i] << std::endl;
         std::vector<std::string> coord_string = AllegroFlare::php::explode(" ", parts[i]);
         add_point(atof(coord_string[0].c_str()), atof(coord_string[1].c_str()), false);
      }

      refresh_segment_info();
      return true;
   }




   bool path2d::save(std::string filename)
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




   void path2d::update_vertexs()
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
   void path2d::draw_shape(ALLEGRO_BITMAP *image)
   {
      static bool warned = false;
      if (vertex.empty()) { if (!warned) { warned = true; std::cout << std::endl << "[path2d::draw_shape] attempting to draw empty() vertexes, did you remember to update_vertexs()?" << std::endl; } return; }
      al_draw_prim(&vertex[0], NULL, image, 0, vertex.size(), ALLEGRO_PRIM_TRIANGLE_FAN);
   }
   */




   void path2d::draw_shape(ALLEGRO_COLOR color)
   {
      al_draw_filled_polygon(&point[0].x, point.size(), color);
   }




   void path2d::draw_shape(float x, float y, ALLEGRO_COLOR color)
   {
      this->move(x, y);
      draw_shape(color);
      this->move(-x, -y);
   }




   void path2d::draw_outline(const ALLEGRO_COLOR &color, float thickness)
   {
      if (point.empty()) return;
      std::vector<AllegroFlare::vec2d>::iterator previous_it = point.begin();
      for (std::vector<AllegroFlare::vec2d>::iterator it=point.begin()+1; it!=point.end(); it++)
      {
         al_draw_line(it->x, it->y, previous_it->x, previous_it->y, color, thickness);
         previous_it = it;
      }
   }




   void path2d::draw_outline(float x, float y, const ALLEGRO_COLOR &color, float thickness)
   {
      this->move(x, y);
      draw_outline(color, thickness);
      this->move(-x, -y);
   }




   path2d *path2d::create_extrapolation(float radian, float theta)
   {
      float angle = 0;
      path2d *result = new path2d();

      for (int i=0; i<(int)point.size()-1; i++)
      {
         angle = segment[i]->normal.get_angle();
         std::cout << std::endl << i << " " << angle;
         if (angle > radian && angle < radian+theta)
         {
            result->add_point(point[i].x, point[i].y, false);
            //result->add_point(point[i]->x, point[i]->y, false);
         }
      }

      std::cout << std::endl << result->point.size();

      //result->refresh_segment_info();
      return result;
   }




   path2d::path2d(const path2d &source)
   {
      source.copy_to(this);
   }




   path2d &path2d::roughen(float disp_range_x, float disp_range_y)
   {
      disp_range_x *= 0.5;
      disp_range_y *= 0.5;
      for (int i=0; i<(int)point.size(); i++)
      {
         point[i].x += AllegroFlare::random_float(-disp_range_x, disp_range_x);
         point[i].y += AllegroFlare::random_float(-disp_range_y, disp_range_y);
      }

      refresh_segment_info();
      return *this;
   }




   bool path2d::within_range(float x)
   {
      if (point.empty()) return false;
      if (point.size() == 1) return false;
      if (x < point[0].x) return false;
      if (x > point[point.size()-1].x) return false;
      return true;
   }




   // assumes within_range() is true
   // this is too slow for practical real-time usage
   float path2d::get_y(float x)
   {
      int lpoint_index = 0;
      AllegroFlare::vec2d lpoint = point[lpoint_index];
      AllegroFlare::vec2d rpoint;

      for (unsigned i=0; i<point.size(); i++)
      {
         if (point[i].x > x) break;
         lpoint_index = i;
      }

      lpoint = point[lpoint_index];
      if (lpoint_index >= ((int)point.size()-1)) rpoint = lpoint;
      else rpoint = point[lpoint_index+1];

      float percentage_between = (x - lpoint.x) / (rpoint.x - lpoint.x);
      AllegroFlare::vec2d point = (rpoint - lpoint) * percentage_between + lpoint;
      return point.y;
   }
}



