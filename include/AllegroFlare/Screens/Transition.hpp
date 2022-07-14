#pragma once


#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/TransitionFX/Base.hpp>


namespace AllegroFlare
{
   namespace Screens
   {
      class Transition : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::Screens::Base* from_screen;
         AllegroFlare::Screens::Base* to_screen;
         AllegroFlare::TransitionFX::Base* transition_fx;
         float duration_sec;
         float position;
         bool finished;
         bool initialized;

      public:
         Transition(AllegroFlare::Screens::Base* from_screen=nullptr, AllegroFlare::Screens::Base* to_screen=nullptr, AllegroFlare::TransitionFX::Base* transition_fx=nullptr, float duration_sec=2.0f);
         virtual ~Transition();

         bool get_finished();
         void initialize();
         virtual void primary_timer_func() override;
         void draw_backbuffer_to_pasteboard_a_bitmap();
         void draw_backbuffer_to_pasteboard_b_bitmap();
      };
   }
}



