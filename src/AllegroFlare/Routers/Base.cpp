

#include <AllegroFlare/Routers/Base.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Routers
{


Base::Base(std::string type, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Frameworks::Full* framework)
   : type(type)
   , event_emitter(event_emitter)
   , framework(framework)
{
}


Base::~Base()
{
}


void Base::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Base::set_framework(AllegroFlare::Frameworks::Full* framework)
{
   this->framework = framework;
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::EventEmitter* Base::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::Frameworks::Full* Base::get_framework() const
{
   return framework;
}


void Base::register_screen(std::string screen_identifier, AllegroFlare::Screens::Base* screen)
{
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[Base::register_screen]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::register_screen: error: guard \"framework\" not met");
   }
   if (!(screen))
   {
      std::stringstream error_message;
      error_message << "[Base::register_screen]: error: guard \"screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::register_screen: error: guard \"screen\" not met");
   }
   framework->register_screen(screen_identifier, screen);
   return;
}

void Base::activate_screen(std::string screen_identifier)
{
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[Base::activate_screen]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::activate_screen: error: guard \"framework\" not met");
   }
   framework->activate_screen(screen_identifier);
   return;
}

void Base::emit_route_event(uint32_t route_event)
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Base::emit_route_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::emit_route_event: error: guard \"event_emitter\" not met");
   }
   event_emitter->emit_router_event(route_event);
   return;
}

void Base::on_route_event(uint32_t route_event)
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


