


#define ALLEGRO_UNSTABLE

#include <AllegroFlare/PickingBuffer.hpp>

#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Useful.hpp> // for to_string



using namespace AllegroFlare;



namespace AllegroFlare
{
   PickingBuffer::PickingBuffer(int w, int h, int depth)
      : surface_render(nullptr)
      , w(w)
      , h(h)
      , depth(depth)
   {
   }




   PickingBuffer::~PickingBuffer()
   {
      if (surface_render) al_destroy_bitmap(surface_render);
   }



   void PickingBuffer::initialize()
   {
      if (surface_render) al_destroy_bitmap(surface_render);
      surface_render = create_new_surface(w, h, depth);
      if (!surface_render) throw std::runtime_error("surface_render not created");
      clear_surface();
   }


   ALLEGRO_BITMAP *PickingBuffer::create_new_surface(int w, int h, int depth)
   {
      int previous_depth = al_get_new_bitmap_depth();
      int previous_samples = al_get_new_bitmap_samples();
      ALLEGRO_STATE previous_state;
      al_store_state(&previous_state, ALLEGRO_STATE_BITMAP);

      al_set_new_bitmap_depth(depth);
      al_set_new_bitmap_samples(0);
      ALLEGRO_BITMAP *bmp = al_create_bitmap(w, h);

      al_restore_state(&previous_state);
      al_set_new_bitmap_depth(previous_depth);
      al_set_new_bitmap_samples(previous_samples);

      return bmp;
   }




   void PickingBuffer::clear_surface()
   {
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(surface_render);
      al_clear_to_color(color::transparent);
      al_restore_state(&state);
   }




   ALLEGRO_BITMAP *PickingBuffer::get_surface_render()
   {
      return surface_render;
   }




   int PickingBuffer::get_surface_width()
   {
      return w;
   }




   int PickingBuffer::get_surface_height()
   {
      return h;
   }




   int PickingBuffer::get_id(int x, int y)
   {
      if (x < 0 || x > get_surface_width()) return 0;
      if (y < 0 || y > get_surface_height()) return 0;

      return AllegroFlare::ColorIDConverter::decode_id(al_get_pixel(surface_render, x, y));
   }
}



