

#include <AllegroFlare/Testing/Rulers.hpp>

#include <AllegroFlare/Rulers.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Testing
{


Rulers::Rulers()
{
}


Rulers::~Rulers()
{
}


void Rulers::draw_dimensional_grid(float x, float y, float z, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_dimensional_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_dimensional_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_dimensional_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_dimensional_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: Test this method
   AllegroFlare::Rulers::draw_dimensional_grid(x, y, z, spacing);
   return;
}

void Rulers::draw_2d_grid(float x, float y, float size, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_2d_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_2d_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_2d_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_2d_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: Test this method
   AllegroFlare::Rulers::draw_2d_grid(x, y, size, spacing);
   return;
}


} // namespace Testing
} // namespace AllegroFlare


