#pragma once


#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>
#include <string>


namespace AllegroFlare
{
   class NotificationsFactory
   {
   private:

   public:
      NotificationsFactory();
      ~NotificationsFactory();

      AllegroFlare::Elements::Notifications::AchievementUnlocked* create_achievement_unlocked_notification(std::string achievement_name="[unset-achievement_name]");
   };
}



