

#include <AllegroFlare/Elements/NotificationRenderer.hpp>

#include <AllegroFlare/Elements/NotificationRenderers/AchievementUnlocked.hpp>
#include <AllegroFlare/Elements/NotificationRenderers/JoystickConnected.hpp>
#include <AllegroFlare/Elements/NotificationRenderers/JoystickDisconnected.hpp>
#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>
#include <AllegroFlare/Elements/Notifications/JoystickConnected.hpp>
#include <AllegroFlare/Elements/Notifications/JoystickDisconnected.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


NotificationRenderer::NotificationRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::Elements::Notifications::Base* notification, float x, float y, float width, float height)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , notification(notification)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
{
}


NotificationRenderer::~NotificationRenderer()
{
}


void NotificationRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void NotificationRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void NotificationRenderer::set_notification(AllegroFlare::Elements::Notifications::Base* notification)
{
   this->notification = notification;
}


void NotificationRenderer::set_x(float x)
{
   this->x = x;
}


void NotificationRenderer::set_y(float y)
{
   this->y = y;
}


void NotificationRenderer::set_width(float width)
{
   this->width = width;
}


void NotificationRenderer::set_height(float height)
{
   this->height = height;
}


float NotificationRenderer::get_x() const
{
   return x;
}


float NotificationRenderer::get_y() const
{
   return y;
}


float NotificationRenderer::get_width() const
{
   return width;
}


float NotificationRenderer::get_height() const
{
   return height;
}


void NotificationRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"font_bin\" not met");
   }
   if (!(notification))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"notification\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderer::render]: error: guard \"notification\" not met");
   }
   if (notification->is_type("AchievementUnlocked"))
   {
      AllegroFlare::Elements::Notifications::AchievementUnlocked *achievement_unlocked_notification =
         dynamic_cast<AllegroFlare::Elements::Notifications::AchievementUnlocked*>(notification);
      AllegroFlare::Elements::NotificationRenderers::AchievementUnlocked achievement_unlocked_renderer(
         bitmap_bin,
         font_bin,
         x,
         y,
         width,
         height,
         achievement_unlocked_notification->get_created_at(),
         achievement_unlocked_notification->get_name()
      );
      achievement_unlocked_renderer.render();
   }
   else if (notification->is_type("JoystickConnected"))
   {
      AllegroFlare::Elements::Notifications::JoystickConnected *joystick_connected_notification =
         dynamic_cast<AllegroFlare::Elements::Notifications::JoystickConnected*>(notification);
      AllegroFlare::Elements::NotificationRenderers::JoystickConnected joystick_connected_renderer(
         bitmap_bin,
         font_bin,
         x,
         y,
         width,
         height,
         joystick_connected_notification->get_created_at(),
         joystick_connected_notification->get_joystick_name()
      );
      joystick_connected_renderer.render();
   }
   else if (notification->is_type("JoystickDisconnected"))
   {
      AllegroFlare::Elements::Notifications::JoystickDisconnected *joystick_disconnected_notification =
         dynamic_cast<AllegroFlare::Elements::Notifications::JoystickDisconnected*>(notification);
      AllegroFlare::Elements::NotificationRenderers::JoystickDisconnected joystick_disconnected_renderer(
         bitmap_bin,
         font_bin,
         x,
         y,
         width,
         height,
         joystick_disconnected_notification->get_created_at(),
         joystick_disconnected_notification->get_joystick_name()
      );
      joystick_disconnected_renderer.render();
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


} // namespace Elements
} // namespace AllegroFlare


