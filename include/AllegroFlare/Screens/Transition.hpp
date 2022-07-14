#pragma once


#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Screens
   {
      class Transition : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::Screens::Base* from_screen;
         AllegroFlare::Screens::Base* to_screen;
         ALLEGRO_BITMAP* pasteboard_a;
         ALLEGRO_BITMAP* pasteboard_b;
         bool initialized;

      public:
         Transition(AllegroFlare::Screens::Base* from_screen=nullptr, AllegroFlare::Screens::Base* to_screen=nullptr);
         virtual ~Transition();

         void initialize();
         virtual void primary_timer_func() override;
         void draw_backbuffer_to_pasteboard_a_bitmap();
         void draw_backbuffer_to_pasteboard_b_bitmap();
      };
   }
}



