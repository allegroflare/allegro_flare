

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Tiled/TMJImageLayer.hpp>
#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>

//void PrintTo(const ALLEGRO_COLOR& color, ::std::ostream* os)
//{
  //*os << "ALLEGRO_COLOR{" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "}";
//}


namespace AllegroFlare::Tiled
{


bool operator==(const TMJImageLayer& object, const TMJImageLayer& other_object)
{
   return object.id == other_object.id &&
          object.name == other_object.name &&
          object.image_filename == other_object.image_filename &&
          object.offset_x == other_object.offset_x &&
          object.offset_y == other_object.offset_y &&
          object.parallax_x == other_object.parallax_x &&
          object.parallax_y == other_object.parallax_y &&
          object.repeat_x == other_object.repeat_x &&
          object.repeat_y == other_object.repeat_y &&
          object.opacity == other_object.opacity &&
          object.tint_color_is_set == other_object.tint_color_is_set;
          //object.tint_color == other_object.tint_color; // TODO: Have testing compare color
}


bool operator!=(const TMJImageLayer& object, const TMJImageLayer& other_object)
{
   return !(object == other_object);
}


void PrintTo(const TMJImageLayer& object, ::std::ostream* os)
{
   ALLEGRO_COLOR c = object.tint_color;
   *os << "TMJImageLayer{ id: " << object.id
       << ", name: \"" << object.name << "\""
       << ", image_filename: \"" << object.image_filename << "\""
       << ", offset_x: " << object.offset_x
       << ", offset_y: " << object.offset_y
       << ", parallax_x: " << object.parallax_x
       << ", parallax_y: " << object.parallax_y
       << ", repeat_x: " << object.repeat_x
       << ", repeat_y: " << object.repeat_y
       << ", opacity: " << object.opacity
       << ", tint_color_is_set: " << object.tint_color_is_set
       << ", tint_color: " << "ALLEGRO_COLOR{" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << "}"
       << " }";
}


}


