

#include <AllegroFlare/Elements/Backgrounds/Parallax.hpp>

#include <AllegroFlare/Useful.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


Parallax::Parallax(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers, float offset_x, float offset_y)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::Parallax::TYPE)
   , layers(layers)
   , offset_x(offset_x)
   , offset_y(offset_y)
{
}


Parallax::~Parallax()
{
}


void Parallax::set_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers)
{
   this->layers = layers;
}


void Parallax::set_offset_x(float offset_x)
{
   this->offset_x = offset_x;
}


void Parallax::set_offset_y(float offset_y)
{
   this->offset_y = offset_y;
}


std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> Parallax::get_layers() const
{
   return layers;
}


float Parallax::get_offset_x() const
{
   return offset_x;
}


float Parallax::get_offset_y() const
{
   return offset_y;
}


void Parallax::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Parallax::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Parallax::render]: error: guard \"al_is_system_installed()\" not met");
   }
   for (auto &layer : layers)
   {
      if (layer.get_bitmap())
      {
         draw_offset_textured_rectangle(
               0,
               0,
               1920,
               1080,
               get_offset_x() * layer.get_offset_rate() + layer.get_anchor_x(),
               get_offset_y() * layer.get_offset_rate() + layer.get_anchor_y(),
               layer.get_bitmap()
            );
      }
   }
   return;
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


