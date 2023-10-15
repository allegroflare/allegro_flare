

#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>




namespace AllegroFlare
{
namespace GameProgressAndStateInfos
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


} // namespace GameProgressAndStateInfos
} // namespace AllegroFlare


