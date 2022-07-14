#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace TransitionFX
   {
      class Base
      {
      private:
         ALLEGRO_BITMAP* pasteboard_a;
         ALLEGRO_BITMAP* pasteboard_b;
         float duration_sec;
         float position;
         bool finished;
         bool initialized;

      public:
         Base(float duration_sec=1.0f);
         virtual ~Base();

         bool get_finished();
         void initialize();
         ALLEGRO_BITMAP* get_pasteboard_a();
         ALLEGRO_BITMAP* get_pasteboard_b();
         virtual void update();
         virtual void render();
      };
   }
}



