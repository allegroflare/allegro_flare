

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>




namespace AllegroFlare
{
namespace RenderSurfaces
{


Bitmap::Bitmap(std::string property)
   : AllegroFlare::RenderSurfaces::Base(AllegroFlare::RenderSurfaces::Bitmap::TYPE)
   , property(property)
{
}


Bitmap::~Bitmap()
{
}


std::string Bitmap::get_property() const
{
   return property;
}


bool Bitmap::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace RenderSurfaces
} // namespace AllegroFlare


