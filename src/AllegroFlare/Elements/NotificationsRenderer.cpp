

#include <AllegroFlare/Elements/NotificationsRenderer.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Elements/NotificationRenderer.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


NotificationsRenderer::NotificationsRenderer(AllegroFlare::FontBin* font_bin, std::vector<AllegroFlare::Elements::Notifications::Base*> notifications, float x, float y, float notification_box_width, float notification_box_height)
   : font_bin(font_bin)
   , notifications(notifications)
   , x(x)
   , y(y)
   , notification_box_width(notification_box_width)
   , notification_box_height(notification_box_height)
{
}


NotificationsRenderer::~NotificationsRenderer()
{
}


void NotificationsRenderer::set_notifications(std::vector<AllegroFlare::Elements::Notifications::Base*> notifications)
{
   this->notifications = notifications;
}


void NotificationsRenderer::set_x(float x)
{
   this->x = x;
}


void NotificationsRenderer::set_y(float y)
{
   this->y = y;
}


void NotificationsRenderer::set_notification_box_width(float notification_box_width)
{
   this->notification_box_width = notification_box_width;
}


void NotificationsRenderer::set_notification_box_height(float notification_box_height)
{
   this->notification_box_height = notification_box_height;
}


std::vector<AllegroFlare::Elements::Notifications::Base*> NotificationsRenderer::get_notifications()
{
   return notifications;
}


float NotificationsRenderer::get_x()
{
   return x;
}


float NotificationsRenderer::get_y()
{
   return y;
}


float NotificationsRenderer::get_notification_box_width()
{
   return notification_box_width;
}


float NotificationsRenderer::get_notification_box_height()
{
   return notification_box_height;
}


void NotificationsRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "NotificationsRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "NotificationsRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Placement2D place;

   place.start_transform();
   for (int i=0; i<notifications.size(); i++)
   {
      AllegroFlare::Elements::NotificationRenderer renderer(
         font_bin,
         notifications[i],
         x,
         y,
         notification_box_width,
         notification_box_height
      );
      renderer.render();
   }
   place.restore_transform();
   return;
}
} // namespace Elements
} // namespace AllegroFlare


