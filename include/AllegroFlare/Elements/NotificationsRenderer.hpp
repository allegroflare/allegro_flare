#pragma once


#include <AllegroFlare/BitmapBin.hpp>
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
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::vector<AllegroFlare::Elements::Notifications::Base*> notifications;
         int surface_width;
         int surface_height;
         float notification_box_width;
         float notification_box_height;
         float notification_vertical_gutter;

      protected:


      public:
         NotificationsRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::Notifications::Base*> notifications={}, int surface_width=1920, int surface_height=1080, float notification_box_width=560.0f, float notification_box_height=130.0f, float notification_vertical_gutter=16.0f);
         ~NotificationsRenderer();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications);
         void set_surface_width(int surface_width);
         void set_surface_height(int surface_height);
         void set_notification_box_width(float notification_box_width);
         void set_notification_box_height(float notification_box_height);
         void set_notification_vertical_gutter(float notification_vertical_gutter);
         std::vector<AllegroFlare::Elements::Notifications::Base*> get_notifications() const;
         int get_surface_width() const;
         int get_surface_height() const;
         float get_notification_box_width() const;
         float get_notification_box_height() const;
         float get_notification_vertical_gutter() const;
         void render();
      };
   }
}



