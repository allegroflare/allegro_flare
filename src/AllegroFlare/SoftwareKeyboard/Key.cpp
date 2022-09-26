

#include <AllegroFlare/SoftwareKeyboard/Key.hpp>




namespace AllegroFlare
{
namespace SoftwareKeyboard
{


Key::Key(char character, float x, float y, float width, float height, float last_pressed_at)
   : character(character)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , last_pressed_at(last_pressed_at)
{
}


Key::~Key()
{
}


void Key::set_character(char character)
{
   this->character = character;
}


void Key::set_x(float x)
{
   this->x = x;
}


void Key::set_y(float y)
{
   this->y = y;
}


void Key::set_width(float width)
{
   this->width = width;
}


void Key::set_height(float height)
{
   this->height = height;
}


void Key::set_last_pressed_at(float last_pressed_at)
{
   this->last_pressed_at = last_pressed_at;
}


char Key::get_character() const
{
   return character;
}


float Key::get_x() const
{
   return x;
}


float Key::get_y() const
{
   return y;
}


float Key::get_width() const
{
   return width;
}


float Key::get_height() const
{
   return height;
}


float Key::get_last_pressed_at() const
{
   return last_pressed_at;
}




} // namespace SoftwareKeyboard
} // namespace AllegroFlare


