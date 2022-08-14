

#include <AllegroFlare/Elements/NotificationRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


NotificationRenderer::NotificationRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::Elements::Notifications::Base* notification)
   : font_bin(font_bin)
   , notification(notification)
{
}


NotificationRenderer::~NotificationRenderer()
{
}


void NotificationRenderer::set_notification(AllegroFlare::Elements::Notifications::Base* notification)
{
   this->notification = notification;
}


void NotificationRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "NotificationRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "NotificationRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "NotificationRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "NotificationRenderer" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(notification))
      {
         std::stringstream error_message;
         error_message << "NotificationRenderer" << "::" << "render" << ": error: " << "guard \"notification\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (notification->is_type("AchievementUnlocked"))
   {
      draw_box();
   }
   else
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderer::render]: ERROR: "
                    << "Could not render notification of type \"" << notification->get_type()
                    << "\" because it is not a recognized type to render.";
      throw std::runtime_error(error_message.str());
   }
   return;
}

void NotificationRenderer::draw_box()
{
   float x = 200;
   float y = 100;
   float box_width = 200;
   float box_height = 90;
   ALLEGRO_COLOR background_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   al_draw_filled_rectangle(x, y, x+box_width, y+box_height, background_color);
   return;
}

ALLEGRO_FONT* NotificationRenderer::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "NotificationRenderer" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace Elements
} // namespace AllegroFlare


