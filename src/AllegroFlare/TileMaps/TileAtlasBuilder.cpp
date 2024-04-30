

#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>

#include <AllegroFlare/ImageProcessing.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


TileAtlasBuilder::TileAtlasBuilder(int tile_w, int tile_h, std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index)
   : tile_w(tile_w)
   , tile_h(tile_h)
   , tile_index(tile_index)
{
}


TileAtlasBuilder::~TileAtlasBuilder()
{
}


ALLEGRO_BITMAP* TileAtlasBuilder::build_extruded()
{
   //al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

   ALLEGRO_STATE prev;
   al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
   ALLEGRO_BITMAP *target = al_create_bitmap(1536, 1536); // TODO: make this a little better
   //ALLEGRO_BITMAP *target = al_create_bitmap(512, 512);
   al_set_target_bitmap(target);


   al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));


   int step_x = tile_w + 2;
   int step_y = tile_h + 2;

   int num_rows = al_get_bitmap_height(target) / step_x;
   int num_cols = al_get_bitmap_width(target) / step_y;


   // step 1:
   // draw each tile onto the new tile_atlas bitmap, each with an extra padding of 1px

   for (int y=0; y<num_rows; y++)
      for (int x=0; x<num_cols; x++)
      {
         int index_num = x + y*num_cols;
         if (index_num >= (int)tile_index.size()) goto tile_drawing_finished;

         int draw_x = x*step_x + 1;
         int draw_y = y*step_y + 1;

         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y, 0);
      }

   tile_drawing_finished:


   // step 2:
   // "extrude" the pixels on the edges of each tile

   for (int y=0; y<num_rows; y++)
      for (int x=0; x<num_cols; x++)
      {
         int index_num = x + y*num_cols;
         if (index_num >= (int)tile_index.size()) goto edge_extruding_finished;

         int draw_x = x*step_x + 1;
         int draw_y = y*step_y + 1;


         // draw the top row of pixels
         al_set_clipping_rectangle(draw_x, draw_y-1, tile_w, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y-1, 0);

         // draw the bottom row of pixels
         al_set_clipping_rectangle(draw_x, draw_y+tile_h, tile_w, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y+1, 0);

         // draw the left row of pixels
         al_set_clipping_rectangle(draw_x-1, draw_y, 1, tile_h);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y, 0);

         // draw the right row of pixels
         al_set_clipping_rectangle(draw_x+tile_w, draw_y, 1, tile_h);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y, 0);


         // draw just the top-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y-1, 0);

         // draw just the bottom-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y+tile_h, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y+1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_w, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y-1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_w, draw_y+tile_h, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y+1, 0);
      }

   edge_extruding_finished:

   al_set_clipping_rectangle(0, 0, al_get_bitmap_width(target), al_get_bitmap_height(target));


   //
   // wrap it all up

   al_restore_state(&prev);


   //
   // to solve an odd bug, the bitmap will be cloned so that OPENGL will correctly create the mipmaps
   ALLEGRO_BITMAP *cloned = al_clone_bitmap(target);
   al_destroy_bitmap(target);
   target = cloned;


   return target;
   //return nullptr;
}

ALLEGRO_BITMAP* TileAtlasBuilder::build_scaled_and_extruded(ALLEGRO_BITMAP* original_bitmap, int scale, int tile_width, int tile_height)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[TileAtlasBuilder::build_scaled_and_extruded]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileAtlasBuilder::build_scaled_and_extruded: error: guard \"al_is_system_installed()\" not met");
   }
   // TODO: Confirm the lifecycle of this sprite sheet:
   //    - the original bitmap
   //    - the duplicated bitmap
   //    - the created sub-bitmaps

   //ALLEGRO_BITMAP *original_bitmap = al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
   // TODO: require al_init
   // TODO: require al_init_image_addon
   //if (!al_is_system_installed()) throw std::runtime_error("AAAxixxA");// al_init();
   //al_init_image_addon();
   //al_init_color_addon();

   //ALLEGRO_BITMAP* source_bitmap = original_bitmap; //al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
   //ASSERT_NE(nullptr, source_bitmap);

   //Tileo::Atlas atlas;
   //atlas.duplicate_bitmap_and_load(source_bitmap, 16, 16, 0);

   //int scale=3;
   ALLEGRO_BITMAP *scaled =
      TileAtlasBuilder::create_pixel_perfect_scaled_render(original_bitmap, scale);

   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
      //atlas.duplicate_bitmap_and_load(scaled, 16*scale, 16*scale, 0);
      atlas.duplicate_bitmap_and_load(scaled, tile_width*scale, tile_height*scale, 0);
      al_destroy_bitmap(scaled);
      std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index = atlas.get_tile_index();
      //PrimMeshAtlas::TileAtlasBuilder tile_atlas_builder(16*scale, 16*scale, tile_index);
      TileAtlasBuilder tile_atlas_builder(tile_width*scale, tile_height*scale, tile_index);
      //atlas.clear();


      ALLEGRO_BITMAP *result = tile_atlas_builder.build_extruded();
   //al_save_bitmap(build_test_filename_png("buid__will_create_an_atlas").c_str(), result);

   atlas.clear();

   //al_destroy_bitmap(scaled);
   //al_destroy_bitmap(result);
   //atlas.clear();
   //al_destroy_bitmap(source_bitmap);
   //al_shutdown_image_addon();
   //al_uninstall_system();

   return result;
}

ALLEGRO_BITMAP* TileAtlasBuilder::create_pixel_perfect_scaled_render(ALLEGRO_BITMAP* bitmap, int scale)
{
   int min_valid_scale_value = 1;
   int max_valid_scale_value = 6;

   if (!bitmap)
   {
      AllegroFlare::Logger::throw_error(
            "TileAtlasBuilder::create_pixel_perfect_scaled_render",
            "bitmap cannot be a nullptr."
         );
   }
   if (scale <= 1 || scale >= max_valid_scale_value)
   {
      AllegroFlare::Logger::throw_error(
            "TileAtlasBuilder::create_pixel_perfect_scaled_render",
            "The scale value provided \"" + std::to_string(scale) + "\" cannot be less than \""
               + std::to_string(min_valid_scale_value) + "\" or greater than \""
               + std::to_string(max_valid_scale_value) + "\"."
         );
   }


   AllegroFlare::ImageProcessing image_processing(bitmap);
   // scale up the original bitmap
   ALLEGRO_BITMAP *scaled = image_processing.create_pixel_perfect_scaled_render(scale);

   return scaled;

   // cut into an atlas


   // get the tile_index


   // use build_extruded with original_tile_width * scale, original_tile_height * width
   //return nullptr;
}


} // namespace TileMaps
} // namespace AllegroFlare


