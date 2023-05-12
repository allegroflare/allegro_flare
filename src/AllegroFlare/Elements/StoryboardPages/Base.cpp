

#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


Base::Base(std::string type)
   : type(type)
   , started_at(0.0f)
   , finished(true)
{
}


Base::~Base()
{
}


void Base::set_started_at(float started_at)
{
   this->started_at = started_at;
}


void Base::set_finished(bool finished)
{
   this->finished = finished;
}


std::string Base::get_type() const
{
   return type;
}


float Base::get_started_at() const
{
   return started_at;
}


bool Base::get_finished() const
{
   return finished;
}


void Base::managed_start(float time_now)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Base::managed_start]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::managed_start: error: guard \"al_is_system_installed()\" not met");
   }
   started_at = time_now;
   start();
   return;
}

void Base::start()
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

void Base::advance()
{
   return;
}

float Base::infer_age(float time_now)
{
   return time_now - started_at;
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


