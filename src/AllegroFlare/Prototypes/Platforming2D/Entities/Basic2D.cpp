

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


Basic2D::Basic2D(std::string property)
   : AllegroFlare::Prototypes::Platforming2D::Entities::Base(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::TYPE)
   , property(property)
{
}


Basic2D::~Basic2D()
{
}


std::string Basic2D::get_property() const
{
   return property;
}


bool Basic2D::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


