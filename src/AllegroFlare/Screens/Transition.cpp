

#include <AllegroFlare/Screens/Transition.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Transition::Transition(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Screens::Base* from_screen, AllegroFlare::Screens::Base* to_screen, AllegroFlare::TransitionFX::Base* transition_fx, std::string game_event_name_to_emit_after_completing)
   : AllegroFlare::Screens::Base("TitleScreen")
   , event_emitter(event_emitter)
   , from_screen(from_screen)
   , to_screen(to_screen)
   , transition_fx(transition_fx)
   , game_event_name_to_emit_after_completing(game_event_name_to_emit_after_completing)
   , target(nullptr)
   , finished(false)
   , initialized(false)
{
}


Transition::~Transition()
{
}


void Transition::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Transition::set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing)
{
   this->game_event_name_to_emit_after_completing = game_event_name_to_emit_after_completing;
}


std::string Transition::get_game_event_name_to_emit_after_completing()
{
   return game_event_name_to_emit_after_completing;
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
   if (!(al_get_current_display()))
      {
         std::stringstream error_message;
         error_message << "Transition" << "::" << "initialize" << ": error: " << "guard \"al_get_current_display()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());

   target = al_create_sub_bitmap(
      backbuffer, 0, 0, al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
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
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      to_screen->primary_timer_func();
      draw_backbuffer_to_pasteboard_a_bitmap();
   }

   if (from_screen)
   {
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      from_screen->primary_timer_func();
      draw_backbuffer_to_pasteboard_b_bitmap();
   }

   transition_fx->update();
   ALLEGRO_STATE previous_render_state;
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(target);
   al_clear_to_color(ALLEGRO_COLOR{0.2, 0.2, 0.21, 1.0});
   transition_fx->render();
   al_restore_state(&previous_render_state);

   if (!finished && transition_fx->get_finished())
   {
      finished = true;
      emit_completion_event();
   }

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

void Transition::emit_completion_event()
{
   if (!game_event_name_to_emit_after_completing.empty())
   {
      //event_emitter->emit_game_event(AllegroFlare::GameEvent(game_event_name_to_emit_after_completing));
   }
   return;
}
} // namespace Screens
} // namespace AllegroFlare


