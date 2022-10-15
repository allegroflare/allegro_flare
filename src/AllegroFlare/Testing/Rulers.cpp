

#include <AllegroFlare/Testing/Rulers.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


namespace AllegroFlare
{
namespace Testing
{


Rulers::Rulers()
{
}


Rulers::~Rulers()
{
}


void Rulers::draw_dimentional_grid(float x, float y, float z, float spacing)
{
   for (int zz=-10; zz<10; zz++)
      for (int xx=-10; xx<10; xx++)
         for (int yy=-10; yy<10; yy++)
         {
            ALLEGRO_STATE previous_target_bitmap_state;
            al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TRANSFORM);
            //al_set_target_bitmap(display_bitmap);
            //al_use_projection_transform(&trans);

            ALLEGRO_TRANSFORM trans;

            al_copy_transform(&trans, al_get_current_transform());

            //al_identity_transform(&trans);
            al_translate_transform_3d(&trans, x+xx*spacing, y+yy*spacing, z+zz*spacing);
            al_use_transform(&trans);
            al_draw_filled_rectangle(-0.5, -0.5, 0.5, 0.5, ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5});
            //al_start_transform(&trans);

            al_restore_state(&previous_target_bitmap_state);
         }

   return;
}


} // namespace Testing
} // namespace AllegroFlare


