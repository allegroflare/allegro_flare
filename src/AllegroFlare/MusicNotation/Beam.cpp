

#include <AllegroFlare/MusicNotation/Beam.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


Beam::Beam(float staff_line_distance, float start_x, float start_staff_pos, Beam::Alignment start_alignment, float end_x, float end_staff_pos, Beam::Alignment end_alignment)
   : staff_line_distance(staff_line_distance)
   , start_x(start_x)
   , start_staff_pos(start_staff_pos)
   , start_alignment(start_alignment)
   , end_x(end_x)
   , end_staff_pos(end_staff_pos)
   , end_alignment(end_alignment)
{
}


Beam::~Beam()
{
}


void Beam::set_staff_line_distance(float staff_line_distance)
{
   this->staff_line_distance = staff_line_distance;
}


void Beam::set_start_x(float start_x)
{
   this->start_x = start_x;
}


void Beam::set_start_staff_pos(float start_staff_pos)
{
   this->start_staff_pos = start_staff_pos;
}


void Beam::set_start_alignment(Beam::Alignment start_alignment)
{
   this->start_alignment = start_alignment;
}


void Beam::set_end_x(float end_x)
{
   this->end_x = end_x;
}


void Beam::set_end_staff_pos(float end_staff_pos)
{
   this->end_staff_pos = end_staff_pos;
}


void Beam::set_end_alignment(Beam::Alignment end_alignment)
{
   this->end_alignment = end_alignment;
}


float Beam::get_staff_line_distance() const
{
   return staff_line_distance;
}


float Beam::get_start_x() const
{
   return start_x;
}


float Beam::get_start_staff_pos() const
{
   return start_staff_pos;
}


Beam::Alignment Beam::get_start_alignment() const
{
   return start_alignment;
}


float Beam::get_end_x() const
{
   return end_x;
}


float Beam::get_end_staff_pos() const
{
   return end_staff_pos;
}


Beam::Alignment Beam::get_end_alignment() const
{
   return end_alignment;
}


void Beam::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(staff_line_distance > 0))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"staff_line_distance > 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"staff_line_distance > 0\" not met");
   }
   if (!(start_alignment != Beam::Alignment::UNDEFINED))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"start_alignment != Beam::Alignment::UNDEFINED\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"start_alignment != Beam::Alignment::UNDEFINED\" not met");
   }
   if (!(end_alignment != Beam::Alignment::UNDEFINED))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"end_alignment != Beam::Alignment::UNDEFINED\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"end_alignment != Beam::Alignment::UNDEFINED\" not met");
   }
   //ALLEGRO_VERTEX[4] = {
      //ALLEGRO_VERTEX{start_x, 
   //};
   //al_draw_line(start_x
   return;
}


} // namespace MusicNotation
} // namespace AllegroFlare


