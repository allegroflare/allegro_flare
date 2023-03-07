

#include <AllegroFlare/VirtualControllers/Base.hpp>




namespace AllegroFlare
{
namespace VirtualControllers
{


Base::Base(std::string type, std::string name)
   : type(type)
   , name(name)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


std::string Base::get_name() const
{
   return name;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace VirtualControllers
} // namespace AllegroFlare


