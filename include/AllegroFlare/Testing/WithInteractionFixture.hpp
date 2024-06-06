#pragma once


#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Testing
   {
      class WithInteractionFixture : public AllegroFlare::Testing::WithAllegroRenderingFixture
      {
      public:
         static constexpr double FPS = 60.0;
         static constexpr double DURATION_TO_AUTO_ABORT_INTERACTIVE_TEST_SEC = 4.0;

      private:
         ALLEGRO_EVENT_QUEUE* event_queue;
         ALLEGRO_TIMER* primary_timer;
         ALLEGRO_EVENT current_event;
         bool auto_abort_halted;
         bool aborted;

      protected:


      public:
         WithInteractionFixture();
         virtual ~WithInteractionFixture();

         ALLEGRO_EVENT_QUEUE* get_event_queue() const;
         bool get_aborted() const;
         virtual void SetUp() override;
         virtual void TearDown() override;
         void halt_auto_abort();
         void abort();
         bool interactive_test_wait_for_event();
         ALLEGRO_EVENT* interactive_test_get_current_event();
         void handle_interactive_test_event(ALLEGRO_EVENT* current_event=nullptr);
         void interactive_test_render_status();
      };
   }
}



