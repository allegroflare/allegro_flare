

#include <AllegroFlare/Screens/Transition.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Transition::Transition(AllegroFlare::Screens::Base* from_screen, AllegroFlare::Screens::Base* to_screen)
   : AllegroFlare::Screens::Base("TitleScreen")
   , from_screen(from_screen)
   , to_screen(to_screen)
   , pasteboard_a(nullptr)
   , pasteboard_b(nullptr)
   , initialized(false)
{
}


Transition::~Transition()
{
}


void Transition::initialize()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Transition" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Transition" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   pasteboard_a = al_create_bitmap(1920, 1080);
   pasteboard_b = al_create_bitmap(1920, 1080);
   initialized = true;
   return;
}

void Transition::primary_timer_func()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Transition" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (to_screen) to_screen->primary_timer_func();
   draw_backbuffer_to_pasteboard_a_bitmap();

   if (from_screen) from_screen->primary_timer_func();
   draw_backbuffer_to_pasteboard_b_bitmap();

   al_draw_bitmap(pasteboard_a, 0, 0, 0);
   al_draw_tinted_bitmap(pasteboard_b, ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5}, 0, 0, 0);

   return;
}

void Transition::draw_backbuffer_to_pasteboard_a_bitmap()
{
   ALLEGRO_BITMAP *source_bitmap = al_get_backbuffer(al_get_current_display());
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(pasteboard_a);

   al_draw_bitmap(source_bitmap, 0, 0, 0);

   al_restore_state(&previous_state);
   return;
}

void Transition::draw_backbuffer_to_pasteboard_b_bitmap()
{
   ALLEGRO_BITMAP *source_bitmap = al_get_backbuffer(al_get_current_display());
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(pasteboard_b);

   al_draw_bitmap(source_bitmap, 0, 0, 0);

   al_restore_state(&previous_state);
   return;
}
} // namespace Screens
} // namespace AllegroFlare


