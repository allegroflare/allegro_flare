

#include <AllegroFlare/SceneGraph/Entities/Base.hpp>




namespace AllegroFlare
{
namespace SceneGraph
{
namespace Entities
{


Base::Base(std::string type)
   : AllegroFlare::ElementID()
   , type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Entities
} // namespace SceneGraph
} // namespace AllegroFlare


