

#include <AllegroFlare/GameplayMechanics/Triggers/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GameplayMechanics
{
namespace Triggers
{


Base::Base(std::string type)
   : type(type)
   , triggered(false)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


bool Base::get_triggered() const
{
   return triggered;
}


void Base::trigger()
{
   if (!((!get_triggered())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameplayMechanics::Triggers::Base::trigger]: error: guard \"(!get_triggered())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameplayMechanics::Triggers::Base::trigger]: error: guard \"(!get_triggered())\" not met");
   }
   on_trigger();
   triggered = true;
}

void Base::reset()
{
   on_reset();
   triggered = false;
}

void Base::on_trigger()
{
   if (!((!get_triggered())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameplayMechanics::Triggers::Base::on_trigger]: error: guard \"(!get_triggered())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameplayMechanics::Triggers::Base::on_trigger]: error: guard \"(!get_triggered())\" not met");
   }
   // to be implemented by the derived class
   return;
}

void Base::on_reset()
{
   if (!((get_triggered())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameplayMechanics::Triggers::Base::on_reset]: error: guard \"(get_triggered())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameplayMechanics::Triggers::Base::on_reset]: error: guard \"(get_triggered())\" not met");
   }
   // to be implemented by the derived class
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Triggers
} // namespace GameplayMechanics
} // namespace AllegroFlare


