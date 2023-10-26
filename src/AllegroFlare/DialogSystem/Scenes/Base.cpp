

#include <AllegroFlare/DialogSystem/Scenes/Base.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace Scenes
{


Base::Base(std::string type)
   : type(type)
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


} // namespace Scenes
} // namespace DialogSystem
} // namespace AllegroFlare


