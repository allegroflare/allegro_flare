

#include <AllegroFlare/DisplaySettingsInterfaces/Live.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DisplaySettingsInterfaces
{


Live::Live(ALLEGRO_DISPLAY* display)
   : AllegroFlare::DisplaySettingsInterfaces::Base(AllegroFlare::DisplaySettingsInterfaces::Live::TYPE)
   , display(display)
   , windowed_mode_width(1920)
   , windowed_mode_height(1080)
   , screensaver_inhibited(false)
   , mouse_cursor_hidden(false)
{
}


Live::~Live()
{
}


void Live::set_display(ALLEGRO_DISPLAY* display)
{
   this->display = display;
}


ALLEGRO_DISPLAY* Live::get_display() const
{
   return display;
}


void Live::hide_mouse_cursor()
{
   bool mouse_hide_successful = al_hide_mouse_cursor(display);
   if (!mouse_hide_successful)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::hide_mouse_cursor",
         "Allegro returned false when trying to hide the mouse cursor"
      );
   }
   mouse_cursor_hidden = true;
   return;
}

void Live::show_mouse_cursor()
{
   bool mouse_show_successful = al_show_mouse_cursor(display);
   if (!mouse_show_successful)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::show_mouse_cursor",
         "Allegro returned false when trying to show the mouse cursor"
      );
   }
   mouse_cursor_hidden = false;
   return;
}

void Live::toggle_hide_mouse_cursor()
{
   if (mouse_cursor_hidden) show_mouse_cursor();
   else hide_mouse_cursor();
}

bool Live::is_mouse_cursor_hidden()
{
   return mouse_cursor_hidden;
}

void Live::activate_fullscreen()
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Live::activate_fullscreen]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Live::activate_fullscreen: error: guard \"display\" not met");
   }
   if (is_fullscreen()) return;

   bool toggle_supported = al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);
   if (!toggle_supported)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::activate_fullscreen",
         "Allegro returned false when trying to set ALLEGRO_FULLSCREEN_WINDOW, indicating it is not supported by "
            "Allegro's driver."
      );
   }

   // Validate the change
   if (!is_fullscreen())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::activate_fullscreen",
         "The ALLEGRO_FULLSCREEN_WINDOW display flag was set successfully, but the property did not actually change."
      );
   }
   return;
}

void Live::deactivate_fullscreen()
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Live::deactivate_fullscreen]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Live::deactivate_fullscreen: error: guard \"display\" not met");
   }
   if (!is_fullscreen()) return;

   bool toggle_supported = al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, false);
   if (!toggle_supported)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::deactivate_fullscreen",
         "Allegro returned false when trying to set ALLEGRO_FULLSCREEN_WINDOW, indicating it is not supported by "
            "Allegro's driver."
      );
   }

   // Validate the change
   if (is_fullscreen())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::deactivate_fullscreen",
         "The ALLEGRO_FULLSCREEN_WINDOW display flag was set successfully, but the property did not actually change."
      );
   }
   return;
}

void Live::toggle_fullscreen()
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Live::toggle_fullscreen]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Live::toggle_fullscreen: error: guard \"display\" not met");
   }
   if (is_fullscreen()) deactivate_fullscreen();
   else activate_fullscreen();
   return;
}

bool Live::is_fullscreen()
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Live::is_fullscreen]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Live::is_fullscreen: error: guard \"display\" not met");
   }
   // TODO: Add test
   int flags = al_get_display_flags(display);
   return flags & ALLEGRO_FULLSCREEN_WINDOW;
}

void Live::set_window_size(int width, int height)
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Live::set_window_size]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Live::set_window_size: error: guard \"display\" not met");
   }
   if (!((!is_fullscreen())))
   {
      std::stringstream error_message;
      error_message << "[Live::set_window_size]: error: guard \"(!is_fullscreen())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Live::set_window_size: error: guard \"(!is_fullscreen())\" not met");
   }
   bool resize_was_successful = al_resize_display(display, width, height);
   if (!resize_was_successful)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::set_window_size",
         "Allegro returned false while trying to resize the display."
      );
   }
   windowed_mode_width = width;
   windowed_mode_height = height;
   return;
}

std::pair<int, int> Live::get_window_size()
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Live::get_window_size]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Live::get_window_size: error: guard \"display\" not met");
   }
   return std::pair<int, int>(
      windowed_mode_width,
      windowed_mode_height
   );
}

std::pair<int, int> Live::get_display_size()
{
   return std::pair<int, int>(
      al_get_display_width(display),
      al_get_display_height(display)
   );
}

void Live::manually_mark_screensaver_as_inhibited()
{
   screensaver_inhibited = true;
   std::cout << "manually_mark: " << screensaver_inhibited << std::endl;
   return;
}

void Live::enable_inhibit_screensaver()
{
   bool inhibit_result = al_inhibit_screensaver(true);
   if (!inhibit_result)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::enable_inhibit_screensaver",
         "al_inhibit_screensaver(true) returned false, indicating it was not successfully inhibited."
      );
   }
   screensaver_inhibited = true;
   std::cout << "enable_inhibit: " << screensaver_inhibited << std::endl;
   return;
}

void Live::disable_inhibit_screensaver()
{
   bool inhibit_result = al_inhibit_screensaver(false);
   if (!inhibit_result)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DisplaySettingsInterfaces::Live::disable_inhibit_screensaver",
         "al_inhibit_screensaver(false) returned false, indicating it was not successfully disabled."
      );
   }
   screensaver_inhibited = false;
   std::cout << "disable_inhibit: " << screensaver_inhibited << std::endl;
   return;
}

void Live::toggle_inhibit_screensaver()
{
   std::cout << "toggle inhibit (before): " << screensaver_inhibited << std::endl;
   if (screensaver_inhibited) disable_inhibit_screensaver();
   else enable_inhibit_screensaver();
   std::cout << "toggle inhibit (after): " << screensaver_inhibited << std::endl;
   return;
}

bool Live::is_screensaver_inhibited()
{
   return screensaver_inhibited;
}


} // namespace DisplaySettingsInterfaces
} // namespace AllegroFlare


