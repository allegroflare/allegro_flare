

#include <AllegroFlare/Runners/Base.hpp>




namespace AllegroFlare
{
namespace Runners
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


} // namespace Runners
} // namespace AllegroFlare


