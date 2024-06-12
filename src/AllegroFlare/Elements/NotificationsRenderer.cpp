

#include <AllegroFlare/Elements/NotificationsRenderer.hpp>

#include <AllegroFlare/Elements/NotificationRenderer.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


NotificationsRenderer::NotificationsRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::vector<AllegroFlare::Elements::Notifications::Base*> notifications, int surface_width, int surface_height, float notification_box_width, float notification_box_height, float notification_vertical_gutter)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , notifications(notifications)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , notification_box_width(notification_box_width)
   , notification_box_height(notification_box_height)
   , notification_vertical_gutter(notification_vertical_gutter)
{
}


NotificationsRenderer::~NotificationsRenderer()
{
}


void NotificationsRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void NotificationsRenderer::set_notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications)
{
   this->notifications = notifications;
}


void NotificationsRenderer::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void NotificationsRenderer::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


void NotificationsRenderer::set_notification_box_width(float notification_box_width)
{
   this->notification_box_width = notification_box_width;
}


void NotificationsRenderer::set_notification_box_height(float notification_box_height)
{
   this->notification_box_height = notification_box_height;
}


void NotificationsRenderer::set_notification_vertical_gutter(float notification_vertical_gutter)
{
   this->notification_vertical_gutter = notification_vertical_gutter;
}


std::vector<AllegroFlare::Elements::Notifications::Base*> NotificationsRenderer::get_notifications() const
{
   return notifications;
}


int NotificationsRenderer::get_surface_width() const
{
   return surface_width;
}


int NotificationsRenderer::get_surface_height() const
{
   return surface_height;
}


float NotificationsRenderer::get_notification_box_width() const
{
   return notification_box_width;
}


float NotificationsRenderer::get_notification_box_height() const
{
   return notification_box_height;
}


float NotificationsRenderer::get_notification_vertical_gutter() const
{
   return notification_vertical_gutter;
}


void NotificationsRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationsRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationsRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationsRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationsRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   float surface_padding_x = 20;
   float surface_padding_y = 60;
   AllegroFlare::Placement2D place(
      surface_width-surface_padding_x*2,
      surface_padding_y*2,
      notification_box_width,
      100
   );
   place.align.x = 1.0;
   place.align.y = 0.0f;

   float cursor_y = 0;

   place.start_transform();
   for (int i=0; i<notifications.size(); i++)
   {
      AllegroFlare::Elements::NotificationRenderer renderer(
         bitmap_bin,
         font_bin,
         notifications[i],
         0,
         cursor_y,
         notification_box_width,
         notification_box_height
      );
      renderer.render();

      cursor_y += notification_box_height + notification_vertical_gutter;
   }
   place.restore_transform();
   return;
}


} // namespace Elements
} // namespace AllegroFlare


