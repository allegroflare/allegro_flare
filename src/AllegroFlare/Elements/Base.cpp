

#include <AllegroFlare/Elements/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Base::Base()
   : AllegroFlare::ElementID()
   , placement({})
{
}


Base::~Base()
{
}


void Base::set_placement(AllegroFlare::Placement2D placement)
{
   this->placement = placement;
}


AllegroFlare::Placement2D Base::get_placement() const
{
   return placement;
}


AllegroFlare::Placement2D &Base::get_placement_ref()
{
   return placement;
}


void Base::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Base::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Base::render]: error: guard \"al_is_system_installed()\" not met");
   }
   return;
}


} // namespace Elements
} // namespace AllegroFlare


