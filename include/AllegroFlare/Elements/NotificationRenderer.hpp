#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Notifications/Base.hpp>
#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      class NotificationRenderer
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Elements::Notifications::Base* notification;
         float x;
         float y;
         float width;
         float height;

      protected:


      public:
         NotificationRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Elements::Notifications::Base* notification=nullptr, float x=0.0f, float y=0.0f, float width=560.0f, float height=130.0f);
         ~NotificationRenderer();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_notification(AllegroFlare::Elements::Notifications::Base* notification);
         void set_x(float x);
         void set_y(float y);
         void set_width(float width);
         void set_height(float height);
         float get_x() const;
         float get_y() const;
         float get_width() const;
         float get_height() const;
         void render();
         void draw_box();
      };
   }
}



