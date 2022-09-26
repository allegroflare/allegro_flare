

#include <AllegroFlare/SoftwareKeyboard/KeyboardKey.hpp>




namespace AllegroFlare
{
namespace SoftwareKeyboard
{


KeyboardKey::KeyboardKey(char character, float x, float y, float width, float height, float last_pressed_at)
   : character(character)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , last_pressed_at(last_pressed_at)
{
}


KeyboardKey::~KeyboardKey()
{
}


void KeyboardKey::set_character(char character)
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


char KeyboardKey::get_character() const
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




} // namespace SoftwareKeyboard
} // namespace AllegroFlare


