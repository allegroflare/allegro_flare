

#include <AllegroFlare/Elements/Rectangle.hpp>

#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Rectangle::Rectangle()
   : x1(0.0f)
   , y1(0.0f)
   , x2(1.0f)
   , y2(1.0f)
{
}


Rectangle::~Rectangle()
{
}


float Rectangle::w()
{
   return x2-x1;
}

float Rectangle::h()
{
   return y2-y1;
}

void Rectangle::scale(float scale_x, float scale_y)
{
   x1 *= scale_x;
   y1 *= scale_y;
   x2 *= scale_x;
   y2 *= scale_y;
   return;
}

void Rectangle::draw(ALLEGRO_COLOR color, float line_thickness)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Rectangle::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Rectangle::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   al_draw_rectangle(x1, y1, x2, y2, color, line_thickness);
   return;
}

AllegroFlare::Elements::Rectangle Rectangle::build_xywh(float x, float y, float w, float h)
{
   AllegroFlare::Elements::Rectangle result;
   result.x1 = x;
   result.y1 = y;
   result.x2 = x + w;
   result.y2 = y + h;
   return result;
}

bool Rectangle::collides(AllegroFlare::Vec2D point)
{
   if (point.x > x2) return false;
   if (point.x < x1) return false;
   if (point.y > y2) return false;
   if (point.y < y1) return false;
   return true;
}


} // namespace Elements
} // namespace AllegroFlare


