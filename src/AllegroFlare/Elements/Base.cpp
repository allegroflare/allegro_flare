

#include <AllegroFlare/Elements/Base.hpp>
#include <stdexcept>
#include <sstream>


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
      error_message << "Base" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   return;
}
} // namespace Elements
} // namespace AllegroFlare


