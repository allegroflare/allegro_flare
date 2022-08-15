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
      int size();
      void add(AllegroFlare::Elements::Notifications::Base* notification=nullptr);
      std::vector<AllegroFlare::Elements::Notifications::Base*> select_all_order_by_created_at_desc();
      std::vector<AllegroFlare::Elements::Notifications::Base*> select_most_recent(float age=10.0f);
      void destroy_all();
      static bool notification_not_older_than(AllegroFlare::Elements::Notifications::Base* notification=nullptr);
      static bool sort_by_created_at_desc_func(AllegroFlare::Elements::Notifications::Base* a=nullptr, AllegroFlare::Elements::Notifications::Base* b=nullptr);
   };
}



