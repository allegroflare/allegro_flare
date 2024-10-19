

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


TileAtlasBuilder::TileAtlasBuilder()
{
}


TileAtlasBuilder::~TileAtlasBuilder()
{
}


AllegroFlare::TileMaps::PrimMeshAtlas* TileAtlasBuilder::create(ALLEGRO_BITMAP* source_bitmap, int tile_width, int tile_height, int scale)
{
   if (!(source_bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create]: error: guard \"source_bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create]: error: guard \"source_bitmap\" not met");
   }
   ALLEGRO_BITMAP *atlas_bitmap = create_scaled_and_extruded(source_bitmap, scale, tile_width, tile_height);
   AllegroFlare::TileMaps::PrimMeshAtlas *result_atlas = new AllegroFlare::TileMaps::PrimMeshAtlas;
   result_atlas->duplicate_bitmap_and_load(atlas_bitmap, tile_width*scale, tile_height*scale, 1);
   return result_atlas;
}

ALLEGRO_BITMAP* TileAtlasBuilder::create_scaled_and_extruded(ALLEGRO_BITMAP* original_bitmap, int scale, int tile_width, int tile_height)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create_scaled_and_extruded]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create_scaled_and_extruded]: error: guard \"al_is_system_installed()\" not met");
   }
   // TODO: Confirm the lifecycle of the created bitmaps
   ALLEGRO_BITMAP *scaled = TileAtlasBuilder::create_pixel_perfect_scaled_render(original_bitmap, scale);
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.duplicate_bitmap_and_load(scaled, tile_width*scale, tile_height*scale, 0);
   al_destroy_bitmap(scaled);
   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index = atlas.get_tile_index();
   ALLEGRO_BITMAP *result = AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded(&tile_index);
   atlas.destroy();
   return result;
}

ALLEGRO_BITMAP* TileAtlasBuilder::create_extruded(std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord>* tile_index_)
{
   if (!(tile_index_))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded]: error: guard \"tile_index_\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded]: error: guard \"tile_index_\" not met");
   }
   if (!((!tile_index_->empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded]: error: guard \"(!tile_index_->empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded]: error: guard \"(!tile_index_->empty())\" not met");
   }
   if (!(validate_all_sub_bitmaps_in_tile_index_are_identical_sizes(tile_index_)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded]: error: guard \"validate_all_sub_bitmaps_in_tile_index_are_identical_sizes(tile_index_)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded]: error: guard \"validate_all_sub_bitmaps_in_tile_index_are_identical_sizes(tile_index_)\" not met");
   }
   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> &tile_index = *tile_index_;

   // Get the dimensions of the tile_index bitmaps
   ALLEGRO_BITMAP *first_sub_bitmap = tile_index[0].get_sub_bitmap();
   if (!first_sub_bitmap)
   {
      // TODO: Test this
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded",
         "Tile first element in the tile_index does not contain a sub_bitmap"
      );
   }
   int tile_width = al_get_bitmap_width(first_sub_bitmap);
   int tile_height = al_get_bitmap_height(first_sub_bitmap);
   int num_tiles_in_tile_index = tile_index.size();


   // Calculate the final width and height of the atlas bitmap (adding a 1px border)
   int effective_tile_width = tile_width + 2;
   int effective_tile_height = tile_height + 2;
   int tiles_per_row = std::ceil(std::sqrt(num_tiles_in_tile_index));
   int rows = std::ceil(static_cast<float>(num_tiles_in_tile_index) / tiles_per_row);
   int atlas_width = tiles_per_row * effective_tile_width;
   int atlas_height = rows * effective_tile_height;

   //
   // Render the tiles to the final bitmap
   //

   AllegroFlare::Logger::info_from(
      "AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded",
      "Creating a surface of " + std::to_string(atlas_width) + "x" + std::to_string(atlas_height) + " to assemble "
         "a tile atlas for \"" + std::to_string(num_tiles_in_tile_index) + "\" tiles that are (" +
         std::to_string(tile_width) + "+2)x(" + std::to_string(tile_height) + "+2)."
   );

   // TODO: Consider: al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
   ALLEGRO_STATE prev;
   al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
   ALLEGRO_BITMAP *target = al_create_bitmap(atlas_width, atlas_height);
   al_set_target_bitmap(target);
   al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));

   int step_x = tile_width + 2;
   int step_y = tile_height + 2;
   int num_rows = al_get_bitmap_height(target) / step_y;
   int num_cols = al_get_bitmap_width(target) / step_x;


   // Draw each tile onto the new tile_atlas bitmap, each with an extra padding of 1px
   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_cols; x++)
      {
         int index_num = x + y*num_cols;
         if (index_num >= (int)tile_index.size()) goto tile_drawing_finished;

         int draw_x = x*step_x + 1;
         int draw_y = y*step_y + 1;

         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y, 0);
      }
   }
   tile_drawing_finished:


   // Draw the extruded pixels on the edges of each tile
   for (int y=0; y<num_rows; y++)
   {
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
   }
   edge_extruding_finished:

   //
   // Clean up
   //

   // Restore the clipping rectangle
   al_set_clipping_rectangle(0, 0, al_get_bitmap_width(target), al_get_bitmap_height(target));

   // Restore the target
   al_restore_state(&prev);

   //
   // Solve an odd bug, the bitmap will be cloned so that OPENGL will correctly create the mipmaps
   // TODO: Look into if this is still necessary
   //

   ALLEGRO_BITMAP *cloned = al_clone_bitmap(target);
   al_destroy_bitmap(target);
   target = cloned;

   return target;
}

ALLEGRO_BITMAP* TileAtlasBuilder::create_pixel_perfect_scaled_render(ALLEGRO_BITMAP* bitmap, int scale)
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create_pixel_perfect_scaled_render]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create_pixel_perfect_scaled_render]: error: guard \"bitmap\" not met");
   }
   if (!((scale >= MIN_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create_pixel_perfect_scaled_render]: error: guard \"(scale >= MIN_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create_pixel_perfect_scaled_render]: error: guard \"(scale >= MIN_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE)\" not met");
   }
   if (!((scale <= MAX_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::create_pixel_perfect_scaled_render]: error: guard \"(scale <= MAX_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::create_pixel_perfect_scaled_render]: error: guard \"(scale <= MAX_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE)\" not met");
   }
   AllegroFlare::ImageProcessing image_processing(bitmap);
   ALLEGRO_BITMAP *scaled = image_processing.create_pixel_perfect_scaled_render(scale);
   return scaled;
}

bool TileAtlasBuilder::validate_all_sub_bitmaps_in_tile_index_are_identical_sizes(std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord>* tile_index_)
{
   if (!(tile_index_))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasBuilder::validate_all_sub_bitmaps_in_tile_index_are_identical_sizes]: error: guard \"tile_index_\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasBuilder::validate_all_sub_bitmaps_in_tile_index_are_identical_sizes]: error: guard \"tile_index_\" not met");
   }
   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> &tile_index = *tile_index_;

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


} // namespace TileMaps
} // namespace AllegroFlare


