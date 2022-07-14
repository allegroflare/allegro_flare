#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace TransitionFX
   {
      class Base
      {
      private:
         ALLEGRO_BITMAP* surface_A;
         ALLEGRO_BITMAP* surface_B;
         float duration;
         float position;
         bool finished;
         bool initialized;

      public:
         Base();
         virtual ~Base();

         ALLEGRO_BITMAP* get_surface_A();
         ALLEGRO_BITMAP* get_surface_B();
         bool get_finished();
         virtual void update();
         virtual void draw();
      };
   }
}



