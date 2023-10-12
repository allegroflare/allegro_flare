

#include <AllegroFlare/DialogSystem/NodeStates/Base.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace NodeStates
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


void Base::update(float time_now)
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace NodeStates
} // namespace DialogSystem
} // namespace AllegroFlare


