

#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>

#include <AllegroFlare/ImageProcessing.hpp>
#include <AllegroFlare/Errors.hpp>
#include <sstream> // for error message



namespace AllegroFlare
{
namespace FrameAnimation
{



SpriteSheet::SpriteSheet(ALLEGRO_BITMAP *_atlas, int sprite_width, int sprite_height, int scale)
   : atlas(_atlas)
   , sprites()
   , sprite_width(sprite_width)
   , sprite_height(sprite_height)
   , num_rows(atlas ? al_get_bitmap_height(atlas) / sprite_height : 0)
   , num_columns(atlas ? al_get_bitmap_width(atlas) / sprite_width : 0)
   , scale(scale)
   , initialized(false)
   , destroyed(false)
   , new_atlas()
   , new_tile_index()
{
   AllegroFlare::Errors::warn_from("AllegroFlare::FrameAnimation::SpriteSheet::SpriteSheet()", 
                                   "SpriteSheet is auto-initializing on construction. This should be fixed");

   // TODO: prevent auto-initialization
   init();
}



void SpriteSheet::init()
{
   //new_atlas.duplicate_bitmap_and_load(atlas, sprite_width, sprite_height, 0);
   //new_tile_index = new_atlas.get_tile_index();



   ///*
         //int scale = 3;
         // TODO: factor out this step
         ALLEGRO_BITMAP *scaled_extruded_tile_map_bitmap =
            //AllegroFlare::TileMaps::PrimMeshAtlas::TileAtlasBuilder::build_scaled_and_extruded(tile_map_bitmap, scale);
            AllegroFlare::TileMaps::PrimMeshAtlas::TileAtlasBuilder::build_scaled_and_extruded(
                  atlas,
                  scale,
                  sprite_width,
                  sprite_height
               );
         //created_tile_atlas->duplicate_bitmap_and_load(
            //scaled_extruded_tile_map_bitmap, tile_atlas_tile_width*scale, tile_atlas_tile_height*scale, 1
         //);
         new_atlas.duplicate_bitmap_and_load(
            scaled_extruded_tile_map_bitmap, sprite_width*scale, sprite_height*scale, 1
         );
         new_tile_index = new_atlas.get_tile_index();
   //*/


   //_create_atlas_copy();
   //_create_sub_sprites();
   initialized = true;
}




void SpriteSheet::destroy()
{
   // TODO: Destroy the new_atlas and/or new_tile_index

   if (destroyed)
   {
      // TODO: output warning
      return;
   }
   if (!al_is_system_installed())
   {
      // TODO: Do not throw in the destructor here
      throw std::runtime_error("dungeon/models/sprite_sheet::SpriteSheet dtor error: "
                               "allegro has already been shutdown");
   }
   for (auto &sprite : sprites) al_destroy_bitmap(sprite);
   if (atlas) al_destroy_bitmap(atlas);
   destroyed = true;
}



void SpriteSheet::_create_atlas_copy()
{
   AllegroFlare::ImageProcessing image_processing(atlas);
   atlas = image_processing.create_pixel_perfect_scaled_render(scale);
}



bool SpriteSheet::_create_sub_sprites()
{
   if (!atlas) return false;

   for (unsigned cursor_y=0; cursor_y<num_rows; cursor_y++)
      for (unsigned cursor_x=0; cursor_x<num_columns; cursor_x++)
      {
         ALLEGRO_BITMAP *sub_bitmap = al_create_sub_bitmap(atlas,
               cursor_x * sprite_width * scale,
               cursor_y * sprite_height * scale,
               sprite_width * scale,
               sprite_height * scale);

         sprites.push_back(sub_bitmap);
      }

   return true;
}



SpriteSheet::~SpriteSheet()
{
   destroy();
}



ALLEGRO_BITMAP *SpriteSheet::get_sprite(int index)
{
   // NOTE: "get_sprite" depreciated, use "get_cell" instead
   return get_cell(index);
}



ALLEGRO_BITMAP *SpriteSheet::get_cell(int index)
{
   //if (index < 0 || index >= sprites.size()) return nullptr;
   //return sprites[index];
   if (index < 0 || index >= new_tile_index.size()) return nullptr;
   return new_tile_index[index].get_sub_bitmap();
}




int SpriteSheet::get_num_sprites()
{
   return new_tile_index.size();
   //return sprites.size();
}



} // namespace FrameAnimation
} // namespace AllegroFlare



