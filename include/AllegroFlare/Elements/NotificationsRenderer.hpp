#pragma once


#include <AllegroFlare/Elements/Notifications/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class NotificationsRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<AllegroFlare::Elements::Notifications::Base*> notifications;
         float x;
         float y;
         float notification_box_width;
         float notification_box_height;

      public:
         NotificationsRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::Notifications::Base*> notifications={}, float x=0.0f, float y=0.0f, float notification_box_width=560.0f, float notification_box_height=130.0f);
         ~NotificationsRenderer();

         void set_notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications);
         void set_x(float x);
         void set_y(float y);
         void set_notification_box_width(float notification_box_width);
         void set_notification_box_height(float notification_box_height);
         std::vector<AllegroFlare::Elements::Notifications::Base*> get_notifications();
         float get_x();
         float get_y();
         float get_notification_box_width();
         float get_notification_box_height();
         void render();
      };
   }
}



