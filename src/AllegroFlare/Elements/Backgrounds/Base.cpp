

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


std::string Base::get_type()
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
} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


