

#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>

#include <AllegroFlare/ImageProcessing.hpp>
#include <AllegroFlare/Errors.hpp>
#include <sstream> // for error message
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>



namespace AllegroFlare
{
namespace FrameAnimation
{



SpriteSheet::SpriteSheet(ALLEGRO_BITMAP *atlas, int sprite_width, int sprite_height, int scale)
   : atlas(atlas)
   , sprite_width(sprite_width)
   , sprite_height(sprite_height)
   , num_rows(0)
   , num_columns(0)
   , scale(scale)
   , initialized(false)
   , destroyed(false)
   , new_atlas()
   , new_tile_index()
{
}



void SpriteSheet::initialize()
{
   if (!atlas)
   {
      AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::initialize",
                                        "\"atlas\" cannot be an nullptr.");
   }
   if (initialized)
   {
      AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::initialize", 
                                        "guard \"!initialized\" not met.");
   }
   if (destroyed)
   {
      AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::initialize", 
                                        "Cannot call initialize when object is destroyed (\"destroyed\" is \"true\").");
   }
   if (sprite_width < 1)
   {
      AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::initialize", 
                                        "\"sprite_width\" must be greater than 1");
   }
   if (sprite_height < 1)
   {
      AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::initialize", 
                                        "\"sprite_height\" must be greater than 1");
   }

   num_rows = al_get_bitmap_height(atlas) / sprite_height;
   num_columns = al_get_bitmap_width(atlas) / sprite_width;

   // TODO: Test there are no dangling bitmaps
   // TODO: Add guards on undestroyed
   ALLEGRO_BITMAP *scaled_extruded_tile_map_bitmap = // TODO: Verify this is not dangling
      AllegroFlare::TileMaps::TileAtlasBuilder::create_scaled_and_extruded(
            atlas,
            scale,
            sprite_width,
            sprite_height
         );

   // At this point, we're done with "atlas". It can be deleted by the end user after having called this "initialize()"

   // Duplicate the scaled_and_extruded_bitmap
   new_atlas.duplicate_bitmap_and_load(
      scaled_extruded_tile_map_bitmap, sprite_width*scale, sprite_height*scale, 1
   );

   al_destroy_bitmap(scaled_extruded_tile_map_bitmap);

   // Set the new tile index
   new_tile_index = new_atlas.get_tile_index();

   initialized = true;
}




void SpriteSheet::destroy()
{
   // TODO: Destroy the new_atlas and/or new_tile_index

   if (!initialized)
   {
      // TODO: Do not throw in the destructor here
      AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::destroy()", 
                                        "Cannot destroy becasue the object was never initialized.");
   }
   if (destroyed)
   {
      // TODO: Do not throw in the destructor here
      AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::destroy()", 
                                        "Cannot call destroy when object is already destroyed (\"destroyed\" is "
                                           "\"true\").");
   }
   if (!al_is_system_installed())
   {
      // TODO: Do not throw in the destructor here
      throw std::runtime_error("dungeon/models/sprite_sheet::SpriteSheet dtor error: "
                               "allegro has already been shutdown");
   }

   //for (auto &sprite : sprites) al_destroy_bitmap(sprite);

   //AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::destroy()", 
                                     //"Cannot call destroy when object is already destroyed (\"destroyed\" is "
                                        //"\"true\").");
   //if (atlas) al_destroy_bitmap(atlas);
   //AllegroFlare::Logger::throw_error("AllegroFlare::FrameAnimation::SpriteSheet::destroy()", 
                                     //"Cannot call destroy when object is already destroyed (\"destroyed\" is "
                                        //"\"true\").");

   destroyed = true;
}



SpriteSheet::~SpriteSheet()
{
   if (!destroyed)
   {
      // TODO: Review this error message
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::FrameAnimation::SpriteSheet::~SpriteSheet",
         "The sprite sheet is expected to be destroyed() before the destructor is called. This may result in "
            "unexpected behavior, or more likely indicates an unfreed resource and potentially leaking memory during "
            "application usage. Please review."
      );
   }
}



bool SpriteSheet::get_initialized()
{
   return initialized;
}



ALLEGRO_BITMAP *SpriteSheet::get_sprite(int index)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::FrameAnimation::SpriteSheet::get_sprite",
            "guard \"initialized\" not met."
         );
   }

   // NOTE: "get_sprite" depreciated, use "get_cell" instead
   AllegroFlare::Logger::warn_from_once(
         "AllegroFlare::FrameAnimation::SpriteSheet::get_sprite()", 
         "\"get_sprite\" is depreciated. Use \"get_cell\" instead."
      );
   return get_cell(index);
}



ALLEGRO_BITMAP *SpriteSheet::get_cell(int index)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::FrameAnimation::SpriteSheet::get_cell",
            "guard \"initialized\" not met."
         );
   }

   if (index < 0 || index >= new_tile_index.size()) return nullptr;
   return new_tile_index[index].get_sub_bitmap();
}



ALLEGRO_BITMAP *SpriteSheet::get_atlas()
{
   //if (!initialized)
   //{
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::FrameAnimation::SpriteSheet::get_atlas",
            "This method is depreciated."
         );
   //}
   // TODO: Prevent calling this method before init
   // "atlas" is required before initialize, not after
   //return atlas;
   return nullptr;
}



int SpriteSheet::get_num_sprites()
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::FrameAnimation::SpriteSheet::get_num_sprites",
            "guard \"initialized\" not met."
         );
   }
   return new_tile_index.size();
}



} // namespace FrameAnimation
} // namespace AllegroFlare



