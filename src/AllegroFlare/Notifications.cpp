

#include <AllegroFlare/Notifications.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Notifications::Notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications)
   : notifications(notifications)
{
}


Notifications::~Notifications()
{
}


void Notifications::set_notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications)
{
   this->notifications = notifications;
}


std::vector<AllegroFlare::Elements::Notifications::Base*> Notifications::get_notifications() const
{
   return notifications;
}


int Notifications::size()
{
   return notifications.size();
}

void Notifications::add(AllegroFlare::Elements::Notifications::Base* notification)
{
   if (!(notification))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Notifications::add]: error: guard \"notification\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Notifications::add]: error: guard \"notification\" not met");
   }
   notifications.push_back(notification);
   return;
}

std::vector<AllegroFlare::Elements::Notifications::Base*> Notifications::select_all_order_by_created_at_desc()
{
   std::vector<AllegroFlare::Elements::Notifications::Base*> result = notifications;
   std::sort(result.begin(), result.end(), sort_by_created_at_desc_func);
   return result;
}

std::vector<AllegroFlare::Elements::Notifications::Base*> Notifications::select_created_at_since_order_by_created_at(float min_created_at)
{
   std::vector<AllegroFlare::Elements::Notifications::Base*> result;
   std::copy_if(
      notifications.begin(),
      notifications.end(),
      std::back_inserter(result),
      [min_created_at](AllegroFlare::Elements::Notifications::Base* notification) {
         return notification && notification->get_created_at() >= min_created_at;
      }
   );
   std::sort(result.begin(), result.end(), sort_by_created_at_desc_func);
   return result;
}

void Notifications::destroy_all()
{
   for (auto &notification : notifications) delete notification;
   notifications.clear();
   return;
}

bool Notifications::sort_by_created_at_desc_func(AllegroFlare::Elements::Notifications::Base* a, AllegroFlare::Elements::Notifications::Base* b)
{
   if (a->get_created_at() == b->get_created_at()) return a; // TODO: return by ID
   return a->get_created_at() > b->get_created_at();
}


} // namespace AllegroFlare


