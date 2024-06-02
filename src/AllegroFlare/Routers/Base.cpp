

#include <AllegroFlare/Routers/Base.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Routers
{


Base::Base(std::string type, AllegroFlare::ScreenManagers::Dictionary* screen_manager)
   : type(type)
   , screen_manager(screen_manager)
   , on_before_activate_screen_func({})
   , on_before_activate_screen_func_user_data(nullptr)
{
}


Base::~Base()
{
}


void Base::set_screen_manager(AllegroFlare::ScreenManagers::Dictionary* screen_manager)
{
   this->screen_manager = screen_manager;
}


void Base::set_on_before_activate_screen_func(std::function<void(std::string, std::string, AllegroFlare::Routers::Base*, void*)> on_before_activate_screen_func)
{
   this->on_before_activate_screen_func = on_before_activate_screen_func;
}


void Base::set_on_before_activate_screen_func_user_data(void* on_before_activate_screen_func_user_data)
{
   this->on_before_activate_screen_func_user_data = on_before_activate_screen_func_user_data;
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::ScreenManagers::Dictionary* Base::get_screen_manager() const
{
   return screen_manager;
}


std::function<void(std::string, std::string, AllegroFlare::Routers::Base*, void*)> Base::get_on_before_activate_screen_func() const
{
   return on_before_activate_screen_func;
}


void* Base::get_on_before_activate_screen_func_user_data() const
{
   return on_before_activate_screen_func_user_data;
}


void Base::register_screen(std::string screen_identifier, AllegroFlare::Screens::Base* screen)
{
   if (!(screen_manager))
   {
      std::stringstream error_message;
      error_message << "[Base::register_screen]: error: guard \"screen_manager\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::register_screen: error: guard \"screen_manager\" not met");
   }
   if (!(screen))
   {
      std::stringstream error_message;
      error_message << "[Base::register_screen]: error: guard \"screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::register_screen: error: guard \"screen\" not met");
   }
   screen_manager->add(screen_identifier, screen);
   return;
}

void Base::unregister_screen(AllegroFlare::Screens::Base* screen)
{
   if (!(screen_manager))
   {
      std::stringstream error_message;
      error_message << "[Base::unregister_screen]: error: guard \"screen_manager\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::unregister_screen: error: guard \"screen_manager\" not met");
   }
   if (!(screen))
   {
      std::stringstream error_message;
      error_message << "[Base::unregister_screen]: error: guard \"screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::unregister_screen: error: guard \"screen\" not met");
   }
   screen_manager->remove(screen);
   return;
}

void Base::activate_screen(std::string screen_identifier)
{
   if (!(screen_manager))
   {
      std::stringstream error_message;
      error_message << "[Base::activate_screen]: error: guard \"screen_manager\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::activate_screen: error: guard \"screen_manager\" not met");
   }
   if (on_before_activate_screen_func)
   {
      std::string currently_active_screen_identifier = screen_manager->get_currently_active_screen_identifier();
      on_before_activate_screen_func(
            screen_identifier,
            currently_active_screen_identifier,
            this,
            on_before_activate_screen_func_user_data
         );
   }
   screen_manager->activate(screen_identifier);
   return;
}

void Base::on_route_event(uint32_t route_event, AllegroFlare::RouteEventDatas::Base* route_event_data, float time_now)
{
   if (!((route_event != 0)))
   {
      std::stringstream error_message;
      error_message << "[Base::on_route_event]: error: guard \"(route_event != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::on_route_event: error: guard \"(route_event != 0)\" not met");
   }
   // TODO: consider making this function pure virutal instead of throwing an error
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Routers::Base::on_route_event",
      "This function is expected be implemented on the base class."
   );
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Routers
} // namespace AllegroFlare


