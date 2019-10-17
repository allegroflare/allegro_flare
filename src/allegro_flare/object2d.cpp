



#include <allegro_flare/object2d.h>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/UsefulPHP.hpp>




//#include <map>
//#include <string>
//std::map<std::string, object2d *> object;
//extern object2d *current_object;




float &object2d::w() { return *_w; }
float &object2d::h() { return *_h; }
float &object2d::w(float val) { return *_w=val; }
float &object2d::h(float val) { return *_h=val; }
void object2d::top(float val) { *_y = val; }
void object2d::left(float val) { *_x = val; }
float object2d::top() { return *_y; }
float object2d::right() { return *_x+*_w; }
float object2d::bottom() { return *_y+*_h; }
float object2d::left() { return *_x; }
float object2d::center() { return *_x+*_w/2; }
float object2d::middle() { return *_y+*_h/2; }
float object2d::anchor_x() { return (_placement) ? _placement->anchor.x : 0.0; }
float object2d::anchor_y() { return (_placement) ? _placement->anchor.x : 0.0; }
float object2d::scale_x() { return (_placement) ? _placement->scale.x : 1.0; }
float object2d::scale_y() { return (_placement) ? _placement->scale.y : 1.0; }
bool object2d::flip_x() { return (_placement) ? _placement->flip.x : false; }
bool object2d::flip_y() { return (_placement) ? _placement->flip.y : false; }
float object2d::align_x() { return (_placement) ? _placement->align.x : 0.0; }
float object2d::align_y() { return (_placement) ? _placement->align.y : 0.0; }
float object2d::opacity() { return (_appearance) ? _appearance->opacity : 1.0; }
ALLEGRO_COLOR object2d::color() { return (_appearance)?_appearance->color:al_map_rgba_f(1,1,1,1); }




object2d::object2d(float x, float y, float w, float h)
   : _x(new float(x))
   , _y(new float(y))
   , _w(new float(w))
   , _h(new float(h))
   , _placement(NULL)
   , _appearance(NULL)
{
   transform_on();
}




object2d::~object2d()
{
}




object2d &object2d::transform_on()
{
   if (!_placement)
   {
      // todo (is being animated?) //
      _placement = new placement2d();
      _placement->position.x = *_x;
      _placement->position.y = *_y;
      _placement->size.x = *_w;
      _placement->size.y = *_h;
      delete _x;
      delete _y;
      delete _w;
      delete _h;
      _x = &_placement->position.x;
      _y = &_placement->position.y;
      _w = &_placement->size.x;
      _h = &_placement->size.y;
      _placement->align.x = 0.0;
      _placement->align.y = 0.0;
   }
   return *this;
}




object2d &object2d::appearance_on()
{
   if (!_appearance)
   {
      _appearance = new appearance2d;
      _appearance->opacity = 1.0;
      _appearance->color = al_map_rgba_f(1,1,1,1);
   }
   return *this;
}



object2d &object2d::start_transform()
{
   if (!_placement) transform_on();
   _placement->start_transform();
   return *this;
}



object2d &object2d::restore_transform()
{
   if (!_placement) transform_on();
   _placement->restore_transform();
   return *this;
}



object2d &object2d::rotation(float rotation)
{
   if (!_placement) transform_on();
   _placement->rotation = rotation;
   return *this;
}




object2d &object2d::scale(float scale)
{
   if (!_placement) transform_on();
   _placement->scale.x = scale;
   _placement->scale.y = scale;
   return *this;
}



object2d &object2d::flip(bool flip_x, bool flip_y)
{
   if (!_placement) transform_on();
   _placement->flip.x = flip_x;
   _placement->flip.y = flip_y;
   return *this;
}




object2d &object2d::anchor(float x, float y)
{
   if (!_placement) transform_on();
   _placement->anchor.x = x;
   _placement->anchor.y = y;
   return *this;
}




object2d &object2d::scale(float scale_x, float scale_y)
{
   if (!_placement) transform_on();
   _placement->scale.x = scale_x;
   _placement->scale.y = scale_y;
   return *this;
}




object2d &object2d::scale_to_fit(float w, float h)
{
   if (!_placement) transform_on();

   float h_scale = (w) / this->w();
   float v_scale = (h) / this->h();

   this->_placement->scale.x = this->_placement->scale.y = std::min<float>(h_scale, v_scale);

   return *this;
}




object2d &object2d::stretch_to_fit(float w, float h)
{
   if (!_placement) transform_on();
   _placement->scale.x = w/(*this->_w);
   _placement->scale.y = h/(*this->_h);
   return *this;
}




object2d &object2d::scale_to(float w, float h) { return scale(w/(*this->_w), h/(*this->_h)); }




object2d &object2d::scale_to_width(float w) { return scale(w/(*this->_w)); }




object2d &object2d::scale_to_height(float h) { return scale(h/(*this->_h)); }




object2d &object2d::align(float align_x, float align_y)
{
   if (!_placement) transform_on();
   _placement->align.x = align_x;
   _placement->align.y = align_y;
   return *this;
}




float &object2d::get_attr(std::string attr)
{
   if (attr=="scale_x") { transform_on(); return _placement->scale.x; }
   else if (attr=="scale_y") { transform_on(); return _placement->scale.y; }
   else if (attr=="align_x") { transform_on(); return _placement->align.x; }
   else if (attr=="align_y") { transform_on(); return _placement->align.y; }
   else if (attr=="anchor_x") { transform_on(); return _placement->anchor.x; }
   else if (attr=="anchor_y") { transform_on(); return _placement->anchor.y; }
   else if (attr=="rotation") { transform_on(); return _placement->rotation; }
   else if (attr=="x") { return *_x; }
   else if (attr=="y") { return *_y; }
   else if (attr=="w") { return *_w; }
   else if (attr=="h") { return *_h; }
   else if (attr=="opacity") { appearance_on(); return _appearance->opacity; }
   else if (attr=="r") { appearance_on(); return _appearance->color.r; }
   else if (attr=="g") { appearance_on(); return _appearance->color.g; }
   else if (attr=="b") { appearance_on(); return _appearance->color.b; }
   else if (attr=="a") { appearance_on(); return _appearance->color.a; }
   return _dummy;
}




object2d &object2d::markup(std::string str)
{
   // function parses a markup string in the form of
   // x=4.2 y=40 opacity=0.2 rotation=0.1
   std::vector<std::string> parts = php::explode(" ", str);

   for (std::vector<std::string>::iterator it=parts.begin(); it!=parts.end(); it++)
   {
      std::vector<std::string> lval_rval_pair = php::explode("=", (*it));
      if (lval_rval_pair.size() != 2)
      {
         std::cout << "[" << __FUNCTION__ << "] lval=rval format not found in token." << std::endl;
         continue;
      }
      std::string &lval = lval_rval_pair[0];
      std::string &rval = lval_rval_pair[1];
      float &found_val = get_attr(lval);
      if ((&found_val)==(&_dummy))
      {
         std::cout << "[" << __FUNCTION__ << "] the attribute \"" << lval << "\" does not exist, cannot set." << std::endl;
         continue;
      }
      else
      {
         try
         {
            found_val = atof(rval.c_str());
         }
         catch(...)
         {
            std::cout << "[" << __FUNCTION__ << "] the rval \"" << rval << "\" is not valid for the atof()." << std::endl;
            continue;
         }
      }
   }
   return *this;
}




object2d &object2d::opacity(float v)
{
   appearance_on();
   _appearance->opacity = v;
   return *this;
}




object2d &object2d::color(ALLEGRO_COLOR color)
{
   appearance_on();
   _appearance->color = color;
   return *this;
}




object2d &object2d::color(const char *color, float opacity)
{
   appearance_on();
   //_appearance->color = ::color(color, opacity);
   return *this;
}




object2d &object2d::position(float x, float y)
{
   *_x = x;
   *_y = y;
   return *this;
}




object2d &object2d::move(float x, float y)
{
   *_x += x;
   *_y += y;
   return *this;
}




object2d &object2d::draw()
{
   _placement->start_transform();
   al_draw_filled_rectangle(0, 0, 0+*_w, 0+*_h, _appearance->color);
   al_draw_rectangle(0, 0, 0+*_w, 0+*_h, al_color_name("dodgerblue"), 1.0);
   _placement->restore_transform();
   return *this;
}




object2d &object2d::draw_raw()
{
   al_draw_filled_rectangle(0, 0, 0+*_w, 0+*_h, _appearance->color);
   al_draw_rectangle(0, 0, 0+*_w, 0+*_h, al_color_name("dodgerblue"), 1.0);
   return *this;
}




void object2d::draw_origin(ALLEGRO_COLOR col)
{
   draw_crosshair(*_x, *_y, col);
}




bool object2d::collide(float x, float y)
{
   if (_placement) return _placement->collide(x, y);
   if (x < *_x) return false;
   if (x > *_x+*_w) return false;
   if (y < *_y) return false;
   if (y > *_y+*_h) return false;
   return true;
}




