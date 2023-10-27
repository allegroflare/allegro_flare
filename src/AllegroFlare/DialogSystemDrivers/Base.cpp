

#include <AllegroFlare/DialogSystemDrivers/Base.hpp>




namespace AllegroFlare
{
namespace DialogSystemDrivers
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


void Base::on_deactivate()
{
   return;
}

void Base::on_render()
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


