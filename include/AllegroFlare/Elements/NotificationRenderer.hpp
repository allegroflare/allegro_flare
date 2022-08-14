#pragma once


#include <AllegroFlare/Elements/Notifications/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class NotificationRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Elements::Notifications::Base* notification;

      public:
         NotificationRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Elements::Notifications::Base* notification=nullptr);
         ~NotificationRenderer();

         void set_notification(AllegroFlare::Elements::Notifications::Base* notification);
         void render();
         void draw_box();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



