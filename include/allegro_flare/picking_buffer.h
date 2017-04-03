#ifndef __PICKING_BUFFER_HEADER
#define __PICKING_BUFFER_HEADER




#include <allegro5/bitmap.h>




class PickingBuffer
{
private:
   ALLEGRO_BITMAP *surface_render;
   int w, h;

   void create_new_surface(int w, int h, int depth);
   static int decode_id(ALLEGRO_COLOR color);
   static ALLEGRO_COLOR encode_id(int id);

public:
   static const int ID_MAX = 16777216;

   PickingBuffer(int w, int h, int depth);
   ~PickingBuffer();

   void clear_surface();

   ALLEGRO_BITMAP *get_surface_render();
   int get_surface_width();
   int get_surface_height();
   int get_id(int x, int y);
};




#endif
