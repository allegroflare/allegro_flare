#pragma once


#include <allegro5/allegro.h>
#include <AllegroFlare/ColorIDConverter.hpp>


namespace AllegroFlare
{
   class PickingBuffer
   {
   private:
      ALLEGRO_BITMAP *surface_render;
      int w, h;
      int depth;
      bool initialized;

      ALLEGRO_BITMAP *create_new_surface(int w, int h, int depth);
      //static int decode_id(ALLEGRO_COLOR color);
      //static ALLEGRO_COLOR encode_id(int id);

   public:
      static const int ID_MAX = ColorIDConverter::ID_MAX;

      PickingBuffer(int w=1, int h=1, int depth=0);
      ~PickingBuffer();

      void initialize();

      void clear_surface();
      ALLEGRO_BITMAP *get_surface_render();
      void set_surface_width(int surface_width=1);
      void set_surface_height(int surface_height=1);
      int get_surface_width();
      int get_surface_height();
      int get_id(int x, int y);
   };
}


