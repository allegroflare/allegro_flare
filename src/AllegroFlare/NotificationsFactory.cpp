

#include <AllegroFlare/NotificationsFactory.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[AllegroFlare::NotificationsFactory::create_achievement_unlocked_notification]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::NotificationsFactory::create_achievement_unlocked_notification]: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::Notifications::AchievementUnlocked *result =
      new AllegroFlare::Elements::Notifications::AchievementUnlocked(achievement_name);
   result->set_created_at(al_get_time());
   return result;
}


} // namespace AllegroFlare


