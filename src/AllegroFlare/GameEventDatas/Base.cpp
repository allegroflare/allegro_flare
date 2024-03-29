

#include <AllegroFlare/GameEventDatas/Base.hpp>




namespace AllegroFlare
{
namespace GameEventDatas
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


void Base::set_type(std::string type)
{
   this->type = type;
}


std::string Base::get_type() const
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameEventDatas
} // namespace AllegroFlare


