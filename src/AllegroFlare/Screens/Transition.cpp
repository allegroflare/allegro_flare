

#include <AllegroFlare/Screens/Transition.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
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


void Transition::set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Transition*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void Transition::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


void Transition::set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing)
{
   this->game_event_name_to_emit_after_completing = game_event_name_to_emit_after_completing;
}


std::function<void(AllegroFlare::Screens::Transition*, void*)> Transition::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* Transition::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


std::string Transition::get_game_event_name_to_emit_after_completing() const
{
   return game_event_name_to_emit_after_completing;
}


bool Transition::get_finished() const
{
   return finished;
}


void Transition::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Transition::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Transition::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Transition::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Transition::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Transition::initialize]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Transition::initialize]: error: guard \"al_get_current_display()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Transition::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Transition::initialize]: error: guard \"event_emitter\" not met");
   }
   // IMPORTANT: Design does not currently work effectively in conjunction with AllegroFlare
   // TODO: this needs to be modified to expect and work with existing and active AllegroFlare rendering surface
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
      error_message << "[AllegroFlare::Screens::Transition::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Transition::primary_timer_func]: error: guard \"initialized\" not met");
   }
   if (!(transition_fx))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Transition::primary_timer_func]: error: guard \"transition_fx\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Transition::primary_timer_func]: error: guard \"transition_fx\" not met");
   }
   if (to_screen)
   {
      to_screen->primary_timer_func();
      draw_backbuffer_to_pasteboard_a_bitmap();
   }

   if (from_screen)
   {
      from_screen->primary_timer_func();
      draw_backbuffer_to_pasteboard_b_bitmap();
   }

   // IMPORTANT: Design does not currently work effectively in conjunction with AllegroFlare
   // TODO: this needs to be modified to expect and work with existing and active AllegroFlare rendering surface
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
      event_emitter->emit_game_event(AllegroFlare::GameEvent(game_event_name_to_emit_after_completing));
   }
   // TODO: Test this callback call
   if (on_finished_callback_func) on_finished_callback_func(this, on_finished_callback_func_user_data);
   return;
}


} // namespace Screens
} // namespace AllegroFlare


