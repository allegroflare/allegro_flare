#pragma once


#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>
#include <AllegroFlare/Elements/Notifications/JoystickConnected.hpp>
#include <string>


namespace AllegroFlare
{
   class NotificationsFactory
   {
   private:

   protected:


   public:
      NotificationsFactory();
      ~NotificationsFactory();

      AllegroFlare::Elements::Notifications::AchievementUnlocked* create_achievement_unlocked_notification(std::string achievement_name="[unset-achievement_name]");
      AllegroFlare::Elements::Notifications::JoystickConnected* create_joystick_connected_notification(std::string joystick_name="[unset-joystick_name]");
   };
}



