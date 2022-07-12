

#include <AllegroFlare/Elements/Backgrounds/Base.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


Base::Base(std::string type)
   : type(type)
   , reveal_counter(0)
   , reveal_speed(1.0f/60.0f)
   , active(false)
{
}


Base::~Base()
{
}


std::string Base::get_type()
{
   return type;
}


float Base::get_reveal_counter()
{
   return reveal_counter;
}


void Base::activate()
{
   reveal_counter = 1.0;
   active = true;
   return;
}

void Base::deactivate()
{
   reveal_counter = 0.0;
   active = false;
   return;
}

void Base::managed_update()
{
   reveal_counter += reveal_speed;
   if (reveal_counter >= 1.0) reveal_counter = 1.0f;
   if (reveal_counter < 0.0) reveal_counter = 0.0f;
   update();
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


