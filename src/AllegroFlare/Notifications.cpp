

#include <AllegroFlare/Notifications.hpp>



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


} // namespace AllegroFlare


