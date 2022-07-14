

#include <AllegroFlare/Screens/Transition.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Transition::Transition(AllegroFlare::Screens::Base* from_screen, AllegroFlare::Screens::Base* to_screen, AllegroFlare::TransitionFX::Base* transition_fx, float duration_sec)
   : AllegroFlare::Screens::Base("TitleScreen")
   , from_screen(from_screen)
   , to_screen(to_screen)
   , transition_fx(transition_fx)
   , duration_sec(duration_sec)
   , position(0.0f)
   , finished(false)
   , initialized(false)
{
}


Transition::~Transition()
{
}


bool Transition::get_finished()
{
   return finished;
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
   if (!(transition_fx))
      {
         std::stringstream error_message;
         error_message << "Transition" << "::" << "primary_timer_func" << ": error: " << "guard \"transition_fx\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (to_screen)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      to_screen->primary_timer_func();
      draw_backbuffer_to_pasteboard_a_bitmap();
   }

   if (from_screen)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      from_screen->primary_timer_func();
      draw_backbuffer_to_pasteboard_b_bitmap();
   }

   transition_fx->update();
   transition_fx->render();

   return;
}

void Transition::draw_backbuffer_to_pasteboard_a_bitmap()
{
   ALLEGRO_BITMAP *source_bitmap = al_get_backbuffer(al_get_current_display());
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(transition_fx->get_pasteboard_a());

   al_draw_bitmap(source_bitmap, 0, 0, 0);

   al_restore_state(&previous_state);
   return;
}

void Transition::draw_backbuffer_to_pasteboard_b_bitmap()
{
   ALLEGRO_BITMAP *source_bitmap = al_get_backbuffer(al_get_current_display());
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(transition_fx->get_pasteboard_b());

   al_draw_bitmap(source_bitmap, 0, 0, 0);

   al_restore_state(&previous_state);
   return;
}
} // namespace Screens
} // namespace AllegroFlare


