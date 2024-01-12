

#include <AllegroFlare/DisplaySettingsInterfaces/Base.hpp>




namespace AllegroFlare
{
namespace DisplaySettingsInterfaces
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


void Base::activate_fullscreen()
{
   return;
}

void Base::deactivate_fullscreen()
{
   return;
}

void Base::toggle_fullscreen()
{
   return;
}

bool Base::is_fullscreen()
{
   return false;
}

void Base::set_window_size(int width, int height)
{
   return;
}

std::pair<int, int> Base::get_window_size()
{
   return std::pair<int, int>(0, 0);
}

std::pair<int, int> Base::get_display_size()
{
   return std::pair<int, int>(0, 0);
}

void Base::manually_mark_screensaver_as_inhibited()
{
   return;
}

void Base::enable_inhibit_screensaver()
{
   return;
}

void Base::disable_inhibit_screensaver()
{
   return;
}

void Base::toggle_inhibit_screensaver()
{
   return;
}

bool Base::is_screensaver_inhibited()
{
   return false;
}

void Base::hide_mouse_cursor()
{
   return;
}

void Base::show_mouse_cursor()
{
   return;
}

void Base::toggle_hide_mouse_cursor()
{
   return;
}

bool Base::is_mouse_cursor_hidden()
{
   return false;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace DisplaySettingsInterfaces
} // namespace AllegroFlare


