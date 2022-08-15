

#include <AllegroFlare/Notifications.hpp>
#include <stdexcept>
#include <sstream>


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


std::vector<AllegroFlare::Elements::Notifications::Base*> Notifications::get_notifications()
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
         error_message << "Notifications" << "::" << "add" << ": error: " << "guard \"notification\" not met";
         throw std::runtime_error(error_message.str());
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

void Notifications::destroy_all()
{
   for (auto &notification : notifications) delete notification;
   notifications.clear();
   return;
}

bool Notifications::sort_by_created_at_desc_func(AllegroFlare::Elements::Notifications::Base* a, AllegroFlare::Elements::Notifications::Base* b)
{
   return a->get_created_at() > b->get_created_at();
}
} // namespace AllegroFlare


