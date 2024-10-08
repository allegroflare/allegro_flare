

#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>

#include <AllegroFlare/ImageProcessing.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <allegro5/allegro.h>
#include <cmath>
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


bool TileAtlasBuilder::validate_all_sub_bitmaps_in_tile_index_are_identical_sizes()
{
   // TODO: Test this
   if (tile_index.empty()) return true;

   ALLEGRO_BITMAP *sub_bitmap = tile_index[0].get_sub_bitmap();
   if (!sub_bitmap)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileAtlasBuilder::validate_all_sub_bitmaps_in_tile_index_are_identical_sizes",
         "There is no sub_bitmap present on the first item in the tile_index."
      );
   }
   int baseline_width = al_get_bitmap_width(sub_bitmap);
   int baseline_height = al_get_bitmap_height(sub_bitmap);

   for (int i=0; i<tile_index.size(); i++)
   //for (auto &tile_index_record : tile_index)
   {
      auto &tile_index_record = tile_index[i];
      ALLEGRO_BITMAP *sub_bitmap = tile_index_record.get_sub_bitmap();
      if (!sub_bitmap)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::TileMaps::TileAtlasBuilder::validate_all_sub_bitmaps_in_tile_index_are_identical_sizes",
            "There is no sub_bitmap present on item at index \"" + std::to_string(i) + "\" in the tile_index."
         );
      }
      int width = al_get_bitmap_width(sub_bitmap);
      int height = al_get_bitmap_height(sub_bitmap);

      if (width != baseline_width || height != baseline_height)
      {
         return false;
      }
   }
   return true;
}

ALLEGRO_BITMAP* TileAtlasBuilder::build_extruded()
{
   if (!((!tile_index.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::build_extruded]: error: guard \"(!tile_index.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::build_extruded]: error: guard \"(!tile_index.empty())\" not met");
   }
   if (!(validate_all_sub_bitmaps_in_tile_index_are_identical_sizes()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::build_extruded]: error: guard \"validate_all_sub_bitmaps_in_tile_index_are_identical_sizes()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::build_extruded]: error: guard \"validate_all_sub_bitmaps_in_tile_index_are_identical_sizes()\" not met");
   }
   // NOTE: This method will *create* a new bitmap given tiles that already exist in a tile_index.  It will
   // take those images and build a new bitmap, providing extruded edges.



   // Calculate the result image dimension for these tiles

   ALLEGRO_BITMAP *sub_bitmap = tile_index[0].get_sub_bitmap();
   if (!sub_bitmap)
   {
      // TODO: Test this
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileAtlasBuilder::build_extruded",
         "Tile first element in the tile_index does not contain a sub_bitmap"
      );
   }
   int tile_width = al_get_bitmap_width(sub_bitmap);
   int tile_height = al_get_bitmap_height(sub_bitmap);
   int num_tiles_in_tile_index = tile_index.size();


   // Add the border of 1 pixel to each tile
   int effective_tile_width = tile_width + 2;
   int effective_tile_height = tile_height + 2;

   int tiles_per_row = std::ceil(std::sqrt(num_tiles_in_tile_index));
   int rows = std::ceil(static_cast<float>(num_tiles_in_tile_index) / tiles_per_row);

   // Calculate the final width and height of the atlas
   int atlas_width = tiles_per_row * effective_tile_width;
   int atlas_height = rows * effective_tile_height;

   //int result_bitmap_width = 


   // TODO: Consider:
   //al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

   ALLEGRO_STATE prev;
   al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
   ALLEGRO_BITMAP *target = al_create_bitmap(atlas_width, atlas_height);
   //ALLEGRO_BITMAP *target = al_create_bitmap(1536*2, 1536*2); // TODO: make this a little better
   //ALLEGRO_BITMAP *target = al_create_bitmap(512, 512);
   al_set_target_bitmap(target);

   AllegroFlare::Logger::info_from(
      "AllegroFlare::TileMaps::TileAtlasBuilder::build_extruded",
      "Creating a surface of " + std::to_string(atlas_width) + "x" + std::to_string(atlas_height) + " to assemble "
         "a tile atlas for \"" + std::to_string(num_tiles_in_tile_index) + "\" tiles that are (" +
         std::to_string(tile_width) + "+2)x(" + std::to_string(tile_height) + "+2)."
         //". This may not be large enough for the tile index, which contains " +
         //std::to_string(tile_index.size()) + " tiles, each with a dimension of (" + std::to_string(tile_w) + ", "
         //+ std::to_string(tile_h) + "), each tile likely has been scaled. If you are seeing blank tiles at larger "
         //"tile index numbers, this could be the cause. Please update this function to accommodate the needed "
         //"dimensions."
   );
   //AllegroFlare::Logger::warn_from(
      //"AllegroFlare::TileMaps::TileAtlasBuilder::build_extruded",
      //"Currently using a surface of 3072x3072. This may not be large enough for the tile index, which contains " +
         //std::to_string(tile_index.size()) + " tiles, each with a dimension of (" + std::to_string(tile_w) + ", "
         //+ std::to_string(tile_h) + "), each tile likely has been scaled. If you are seeing blank tiles at larger "
         //"tile index numbers, this could be the cause. Please update this function to accommodate the needed "
         //"dimensions."
   //);


   al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));


   int step_x = tile_width + 2;
   int step_y = tile_height + 2;

   int num_rows = al_get_bitmap_height(target) / step_y;
   int num_cols = al_get_bitmap_width(target) / step_x;


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
         al_set_clipping_rectangle(draw_x, draw_y-1, tile_width, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y-1, 0);

         // draw the bottom row of pixels
         al_set_clipping_rectangle(draw_x, draw_y+tile_height, tile_width, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y+1, 0);

         // draw the left row of pixels
         al_set_clipping_rectangle(draw_x-1, draw_y, 1, tile_height);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y, 0);

         // draw the right row of pixels
         al_set_clipping_rectangle(draw_x+tile_width, draw_y, 1, tile_height);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y, 0);


         // draw just the top-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y-1, 0);

         // draw just the bottom-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y+tile_height, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y+1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_width, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y-1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_width, draw_y+tile_height, 1, 1);
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
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::build_scaled_and_extruded]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::build_scaled_and_extruded]: error: guard \"al_is_system_installed()\" not met");
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
   if (scale < 1 || scale > max_valid_scale_value) // TODO: Test this condition
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


