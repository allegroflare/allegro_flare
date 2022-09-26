

#include <AllegroFlare/SoftwareKeyboard/KeyboardKey.hpp>




namespace AllegroFlare
{
namespace SoftwareKeyboard
{


KeyboardKey::KeyboardKey(std::string character, float x, float y, float width, float height)
   : character(character)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , last_pressed_at(0)
{
}


KeyboardKey::~KeyboardKey()
{
}


void KeyboardKey::set_character(std::string character)
{
   this->character = character;
}


void KeyboardKey::set_x(float x)
{
   this->x = x;
}


void KeyboardKey::set_y(float y)
{
   this->y = y;
}


void KeyboardKey::set_width(float width)
{
   this->width = width;
}


void KeyboardKey::set_height(float height)
{
   this->height = height;
}


void KeyboardKey::set_last_pressed_at(float last_pressed_at)
{
   this->last_pressed_at = last_pressed_at;
}


std::string KeyboardKey::get_character() const
{
   return character;
}


float KeyboardKey::get_x() const
{
   return x;
}


float KeyboardKey::get_y() const
{
   return y;
}


float KeyboardKey::get_width() const
{
   return width;
}


float KeyboardKey::get_height() const
{
   return height;
}


float KeyboardKey::get_last_pressed_at() const
{
   return last_pressed_at;
}


float KeyboardKey::get_x2()
{
   return x+width;
}

float KeyboardKey::get_y2()
{
   return y+height;
}


} // namespace SoftwareKeyboard
} // namespace AllegroFlare


