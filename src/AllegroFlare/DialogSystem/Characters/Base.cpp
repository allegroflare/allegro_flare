

#include <AllegroFlare/DialogSystem/Characters/Base.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace Characters
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


} // namespace Characters
} // namespace DialogSystem
} // namespace AllegroFlare

