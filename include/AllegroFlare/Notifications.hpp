#pragma once


#include <AllegroFlare/Elements/Notifications/Base.hpp>
#include <vector>


namespace AllegroFlare
{
   class Notifications
   {
   private:
      std::vector<AllegroFlare::Elements::Notifications::Base*> notifications;

   public:
      Notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications={});
      ~Notifications();

      void set_notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications);
      std::vector<AllegroFlare::Elements::Notifications::Base*> get_notifications();
   };
}



