

#include <AllegroFlare/Elements/SelectionCursorBox.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


SelectionCursorBox::SelectionCursorBox()
   : cursor_destination({})
   , cursor_size_destination(80, 80)
   , cursor_reposition_multiplier(DEFAULT_CURSOR_REPOSITION_MULTIPLIER)
   , cursor_location({})
   , cursor_size(80, 80)
{
}


SelectionCursorBox::~SelectionCursorBox()
{
}


float SelectionCursorBox::get_cursor_reposition_multiplier() const
{
   return cursor_reposition_multiplier;
}


void SelectionCursorBox::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SelectionCursorBox::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SelectionCursorBox::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SelectionCursorBox::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SelectionCursorBox::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   return;
}


} // namespace Elements
} // namespace AllegroFlare


