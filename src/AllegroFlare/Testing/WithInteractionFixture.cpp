

#include <AllegroFlare/Testing/WithInteractionFixture.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Testing
{


WithInteractionFixture::WithInteractionFixture()
   : AllegroFlare::Testing::WithAllegroRenderingFixture()
   , event_queue(nullptr)
   , primary_timer(nullptr)
   , current_event({})
   , auto_abort_halted(false)
   , aborted(false)
   , escape_key_aborts(true)
{
}


WithInteractionFixture::~WithInteractionFixture()
{
}


ALLEGRO_EVENT_QUEUE* WithInteractionFixture::get_event_queue() const
{
   return event_queue;
}


bool WithInteractionFixture::get_aborted() const
{
   return aborted;
}


bool WithInteractionFixture::get_escape_key_aborts() const
{
   return escape_key_aborts;
}


void WithInteractionFixture::SetUp()
{
   AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();

   al_install_keyboard();
   event_queue = al_create_event_queue();
   primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(FPS));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(al_get_current_display()));

   al_install_mouse();
   al_register_event_source(event_queue, al_get_mouse_event_source());

   // Start the interactive loop
   al_start_timer(primary_timer);

   return;
}

void WithInteractionFixture::TearDown()
{
   al_stop_timer(primary_timer);
   al_destroy_timer(primary_timer);

   al_unregister_event_source(event_queue, al_get_mouse_event_source());
   al_uninstall_mouse();

   primary_timer = nullptr;
   al_unregister_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_unregister_event_source(event_queue, al_get_keyboard_event_source());
   // TODO: Unregister display
   al_destroy_event_queue(event_queue);
   event_queue = nullptr;
   al_uninstall_keyboard();

   AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   return;
}

void WithInteractionFixture::halt_auto_abort()
{
   if (!auto_abort_halted) auto_abort_halted = true;
   return;
}

void WithInteractionFixture::abort()
{
   if (!aborted) aborted = true;
   return;
}

void WithInteractionFixture::disable_escape_key_aborts()
{
   escape_key_aborts = false;
   return;
}

bool WithInteractionFixture::interactive_test_wait_for_event()
{
   // TODO: Consider renaming this
   al_wait_for_event(get_event_queue(), &current_event);
   handle_interactive_test_event(&current_event);
   return !aborted;
}

ALLEGRO_EVENT* WithInteractionFixture::interactive_test_get_current_event()
{
   return &current_event;
}

void WithInteractionFixture::handle_interactive_test_event(ALLEGRO_EVENT* current_event)
{
   if (!(current_event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Testing::WithInteractionFixture::handle_interactive_test_event]: error: guard \"current_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Testing::WithInteractionFixture::handle_interactive_test_event]: error: guard \"current_event\" not met");
   }
   double time_now = al_get_time();
   switch(current_event->type)
   {
      case ALLEGRO_EVENT_TIMER: {
         // Update
         if (current_event->any.source == al_get_timer_event_source(primary_timer))
         {
            if (!auto_abort_halted && (time_now >= DURATION_TO_AUTO_ABORT_INTERACTIVE_TEST_SEC)) abort();
         }
      } break;

      // TODO: Include other forms of input, joystics
      case ALLEGRO_EVENT_KEY_CHAR:
      case ALLEGRO_EVENT_KEY_UP:
      case ALLEGRO_EVENT_KEY_DOWN: {
         halt_auto_abort();
         bool shift = current_event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool command = current_event->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         if (escape_key_aborts && current_event->keyboard.keycode == ALLEGRO_KEY_ESCAPE && (!shift)) abort();
         //if (current_event->keyboard.keycode == ALLEGRO_KEY_Q && command) abort();
      } break;

      case ALLEGRO_EVENT_MOUSE_AXES:
      case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
         halt_auto_abort();
      } break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE: {
         abort();
      } break;
   }
   return;
}

void WithInteractionFixture::interactive_test_render_status()
{
   double time_now = al_get_time();
   if (!auto_abort_halted)
   {
      int seconds_left = (int)(DURATION_TO_AUTO_ABORT_INTERACTIVE_TEST_SEC - time_now) + 1;
      al_draw_textf(get_user_prompt_font(), ALLEGRO_COLOR{0.3, 0.3, 0.3, 1}, 30, 1080-60, ALLEGRO_ALIGN_LEFT,
         "Interactive test will auto-close in %d seconds. Otherwise press any key.", seconds_left);
   }
   return;
}


} // namespace Testing
} // namespace AllegroFlare


