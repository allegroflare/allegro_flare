

#include <AllegroFlare/NotificationsFactory.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


NotificationsFactory::NotificationsFactory()
{
}


NotificationsFactory::~NotificationsFactory()
{
}


AllegroFlare::Elements::Notifications::AchievementUnlocked* NotificationsFactory::create_achievement_unlocked_notification(std::string achievement_name)
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "NotificationsFactory" << "::" << "create_achievement_unlocked_notification" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Elements::Notifications::AchievementUnlocked *result =
      new AllegroFlare::Elements::Notifications::AchievementUnlocked(achievement_name);
   result->set_created_at(al_get_time());
   return result;
}
} // namespace AllegroFlare


