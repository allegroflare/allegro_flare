

#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Base::Base(std::string type)
   : type(type)
   , created_at(0)
{
}


Base::~Base()
{
}


void Base::set_created_at(float created_at)
{
   this->created_at = created_at;
}


std::string Base::get_type() const
{
   return type;
}


float Base::get_created_at() const
{
   return created_at;
}


void Base::update()
{
   return;
}

float Base::infer_age()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Base::infer_age]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::infer_age: error: guard \"al_is_system_installed()\" not met");
   }
   return al_get_time() - get_created_at();
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


