

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
   , auto_abort_halted(false)
   , aborted(false)
{
}


WithInteractionFixture::~WithInteractionFixture()
{
}


ALLEGRO_EVENT_QUEUE* WithInteractionFixture::get_event_queue() const
{
   return event_queue;
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

void WithInteractionFixture::handle_interactive_test_event(ALLEGRO_EVENT* current_event)
{
   if (!(current_event))
   {
      std::stringstream error_message;
      error_message << "[WithInteractionFixture::handle_interactive_test_event]: error: guard \"current_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithInteractionFixture::handle_interactive_test_event: error: guard \"current_event\" not met");
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

      // TODO: Include other forms of input, joystics, mouse
      case ALLEGRO_EVENT_KEY_CHAR:
      case ALLEGRO_EVENT_KEY_UP:
      case ALLEGRO_EVENT_KEY_DOWN: {
         halt_auto_abort();
      } break;

   }
   return;
}

void WithInteractionFixture::SetUp()
{
   AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();

   al_install_keyboard();
   event_queue = al_create_event_queue();
   primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(FPS));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   // Setup the timed interactive
   //float duration_to_auto_abort_test = 6.0;
   //bool auto_abort_halted = false;

   // Start the interactive loop
   al_start_timer(primary_timer);

   return;
}

void WithInteractionFixture::render_interactive_test_status()
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

void WithInteractionFixture::TearDown()
{
   al_destroy_timer(primary_timer);

   AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   return;
}


} // namespace Testing
} // namespace AllegroFlare


