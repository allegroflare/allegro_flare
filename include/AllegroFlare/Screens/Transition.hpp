#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/TransitionFX/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class Transition : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Screens::Base* from_screen;
         AllegroFlare::Screens::Base* to_screen;
         AllegroFlare::TransitionFX::Base* transition_fx;
         std::string game_event_name_to_emit_after_completing;
         ALLEGRO_BITMAP* target;
         bool finished;
         bool initialized;
         void draw_backbuffer_to_pasteboard_a_bitmap();
         void draw_backbuffer_to_pasteboard_b_bitmap();
         void emit_completion_event();

      protected:


      public:
         Transition(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Screens::Base* from_screen=nullptr, AllegroFlare::Screens::Base* to_screen=nullptr, AllegroFlare::TransitionFX::Base* transition_fx=nullptr, std::string game_event_name_to_emit_after_completing="transition_finished");
         virtual ~Transition();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing);
         std::string get_game_event_name_to_emit_after_completing() const;
         bool get_finished() const;
         void initialize();
         virtual void primary_timer_func() override;
      };
   }
}



