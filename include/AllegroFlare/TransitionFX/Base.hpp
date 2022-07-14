#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace TransitionFX
   {
      class Base
      {
      private:
         ALLEGRO_BITMAP* display_bitmap;
         ALLEGRO_BITMAP* surface_A;
         ALLEGRO_BITMAP* surface_B;
         float duration;
         float position;
         bool finished;
         bool initialized;

      public:
         Base(ALLEGRO_BITMAP* display_bitmap=nullptr);
         virtual ~Base();

         ALLEGRO_BITMAP* get_surface_A();
         ALLEGRO_BITMAP* get_surface_B();
         bool get_finished();
         void set_display_bitmap(ALLEGRO_BITMAP* display_bitmap=nullptr);
         void initialize();
         virtual void update();
         virtual void draw();
      };
   }
}



