

#include <AllegroFlare/Backgrounds/Parallax.hpp>
#include <AllegroFlare/Useful.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Backgrounds
{


Parallax::Parallax(std::vector<AllegroFlare::Backgrounds::ParallaxLayer> layers, float offset_x, float offset_y)
   : AllegroFlare::Backgrounds::Base("Parallax")
   , layers(layers)
   , offset_x(offset_x)
   , offset_y(offset_y)
{
}


Parallax::~Parallax()
{
}


void Parallax::set_layers(std::vector<AllegroFlare::Backgrounds::ParallaxLayer> layers)
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


std::vector<AllegroFlare::Backgrounds::ParallaxLayer> Parallax::get_layers()
{
   return layers;
}


float Parallax::get_offset_x()
{
   return offset_x;
}


float Parallax::get_offset_y()
{
   return offset_y;
}


void Parallax::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Parallax" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
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
} // namespace AllegroFlare


