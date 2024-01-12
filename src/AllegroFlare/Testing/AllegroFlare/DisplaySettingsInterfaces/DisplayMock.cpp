

#include <AllegroFlare/Testing/AllegroFlare/DisplaySettingsInterfaces/DisplayMock.hpp>




namespace AllegroFlare
{
namespace Testing
{
namespace AllegroFlare
{
namespace DisplaySettingsInterfaces
{


DisplayMock::DisplayMock()
   : ::AllegroFlare::DisplaySettingsInterfaces::Base(::AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock::TYPE)
   , fullscreen_status(false)
   , display_width(1920)
   , display_height(1080)
   , screensaver_inhibited(false)
   , mouse_cursor_hidden(false)
{
}


DisplayMock::~DisplayMock()
{
}


bool DisplayMock::get_fullscreen_status() const
{
   return fullscreen_status;
}


int DisplayMock::get_display_width() const
{
   return display_width;
}


int DisplayMock::get_display_height() const
{
   return display_height;
}


void DisplayMock::activate_fullscreen()
{
   fullscreen_status = true;
   return;
}

void DisplayMock::deactivate_fullscreen()
{
   fullscreen_status = false;
   return;
}

void DisplayMock::toggle_fullscreen()
{
   fullscreen_status = !fullscreen_status;
   return;
}

bool DisplayMock::is_fullscreen()
{
   return fullscreen_status;
}

void DisplayMock::set_window_size(int width, int height)
{
   display_width = width;
   display_height = height;
   return;
}

std::pair<int, int> DisplayMock::get_window_size()
{
   return std::pair<int, int>(display_width, display_height);
}

std::pair<int, int> DisplayMock::get_display_size()
{
   return std::pair<int, int>(display_width+160*4, display_height+90*4);
}

void DisplayMock::manually_mark_screensaver_as_inhibited()
{
   screensaver_inhibited = true;
   return;
}

void DisplayMock::enable_inhibit_screensaver()
{
   screensaver_inhibited = true;
   return;
}

void DisplayMock::disable_inhibit_screensaver()
{
   screensaver_inhibited = false;
   return;
}

void DisplayMock::toggle_inhibit_screensaver()
{
   screensaver_inhibited = !screensaver_inhibited;
   return;
}

bool DisplayMock::is_screensaver_inhibited()
{
   return screensaver_inhibited;
}

void DisplayMock::hide_mouse_cursor()
{
   mouse_cursor_hidden = true;
}

void DisplayMock::show_mouse_cursor()
{
   mouse_cursor_hidden = false;
}

void DisplayMock::toggle_hide_mouse_cursor()
{
   if (mouse_cursor_hidden) show_mouse_cursor();
   else hide_mouse_cursor();
}

bool DisplayMock::is_mouse_cursor_hidden()
{
   return mouse_cursor_hidden;
}


} // namespace DisplaySettingsInterfaces
} // namespace AllegroFlare
} // namespace Testing
} // namespace AllegroFlare


