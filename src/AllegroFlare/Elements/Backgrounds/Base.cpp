

#include <AllegroFlare/Elements/Backgrounds/Base.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
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


void Base::activate()
{
   return;
}

void Base::deactivate()
{
   return;
}

void Base::update()
{
   return;
}

void Base::render()
{
   return;
}

void Base::show()
{
   return;
}

void Base::hide()
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


