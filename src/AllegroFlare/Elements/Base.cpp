

#include <AllegroFlare/Elements/Base.hpp>




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
   return;
}


} // namespace Elements
} // namespace AllegroFlare


