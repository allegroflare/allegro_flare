

#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Room::Room()
   : min_x(0.0f)
   , min_y(0.0f)
   , max_x(1920.0f)
   , max_y(1080.0f)
   , suspended(false)
   , suspended_at(0.0f)
{
}


Room::~Room()
{
}


void Room::set_min_x(float min_x)
{
   this->min_x = min_x;
}


void Room::set_min_y(float min_y)
{
   this->min_y = min_y;
}


void Room::set_max_x(float max_x)
{
   this->max_x = max_x;
}


void Room::set_max_y(float max_y)
{
   this->max_y = max_y;
}


float Room::get_min_x() const
{
   return min_x;
}


float Room::get_min_y() const
{
   return min_y;
}


float Room::get_max_x() const
{
   return max_x;
}


float Room::get_max_y() const
{
   return max_y;
}


bool Room::get_suspended() const
{
   return suspended;
}


void Room::suspend()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Room::suspend]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Room::suspend]: error: guard \"al_is_system_installed()\" not met");
   }
   if (suspended) return;
   suspended = true;
   suspended_at = al_get_time(); // TODO: Pass in a current_time
   return;
}

void Room::resume()
{
   if (!suspended) return;
   suspended = false;
   suspended_at = 0.0f;
   return;
}

void Room::show()
{
   return;
}

void Room::hide()
{
   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


