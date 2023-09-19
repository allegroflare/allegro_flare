

#include <AllegroFlare/Testing/Rulers.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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


void Rulers::draw_dimensional_grid(float x, float y, float z, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_dimensional_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_dimensional_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_dimensional_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_dimensional_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
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

void Rulers::draw_2d_grid(float x, float y, float size, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_2d_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_2d_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_2d_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_2d_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
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
         al_translate_transform_3d(&trans, x+xx*spacing, y+yy*spacing, 0); //z+zz*spacing);
         al_use_transform(&trans);
         al_draw_filled_rectangle(-size*0.5, -size*0.5, size*0.5, size*0.5, ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5});
         //al_start_transform(&trans);

         al_restore_state(&previous_target_bitmap_state);
      }

   return;
}


} // namespace Testing
} // namespace AllegroFlare


