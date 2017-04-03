



#define ALLEGRO_UNSTABLE

#include <allegro_flare/picking_buffer.h>

#include <sstream>
#include <allegro_flare/useful.h> // for to_string




PickingBuffer::PickingBuffer(int w, int h, int depth)
   : surface_render(nullptr)
   , w(w)
   , h(h)
   , depth(depth)
{
   create_new_surface(w, h, depth);
   clear_surface();
}




PickingBuffer::~PickingBuffer()
{
   al_destroy_bitmap(surface_render);
}




void PickingBuffer::create_new_surface(int w, int h, int depth)
{
   if (surface_render) al_destroy_bitmap(surface_render);

   int previous_depth = al_get_new_bitmap_depth();
   int previous_samples = al_get_new_bitmap_samples();
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_BITMAP);

   al_set_new_bitmap_depth(depth);
   al_set_new_bitmap_samples(0);
   surface_render = al_create_bitmap(w, h);

   al_restore_state(&previous_state);
   al_set_new_bitmap_depth(previous_depth);
   al_set_new_bitmap_samples(previous_samples);
}




void PickingBuffer::clear_surface()
{
   ALLEGRO_STATE state;
   al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(surface_render);
   al_clear_to_color(color::transparent);
   al_restore_state(&state);
}




int PickingBuffer::decode_id(ALLEGRO_COLOR color)
{
   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   return r + (g * 256) + (b * 65536);
}




ALLEGRO_COLOR PickingBuffer::encode_id(int id)
{
   unsigned char r = id % 256;
   unsigned char g = id / 256;
   unsigned char b = id / 65536;
   unsigned char a = (id == 0) ? 0 : 255;

   return al_map_rgba(r, g, b, a);
}




