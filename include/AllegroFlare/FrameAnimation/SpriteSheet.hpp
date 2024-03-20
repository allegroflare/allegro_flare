#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <vector>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>



// TODO: Remove auto-initialization

namespace AllegroFlare
{
   namespace FrameAnimation
   {
      class SpriteSheet
      {
      private:
         // TODO: Remove the no-longer used member variables here
         ALLEGRO_BITMAP *atlas;
         std::vector<ALLEGRO_BITMAP *> sprites;
         int sprite_width;
         int sprite_height;
         int num_rows;
         int num_columns;
         int scale;
         bool initialized;
         bool destroyed;

         // TODO: Remove the no-longer used internal methods
         bool _create_sub_sprites();
         void _create_atlas_copy();

         AllegroFlare::TileMaps::PrimMeshAtlas new_atlas;
         std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> new_tile_index; // = atlas.get_tile_index();
         //AllegroFlare::TileMaps::PrimMeshAtlas middle_atlas;

      public:
         SpriteSheet(ALLEGRO_BITMAP *_atlas, int sprite_width=48, int sprite_height=48, int scale=1);
         ~SpriteSheet();

         ALLEGRO_BITMAP *get_sprite(int index);
         ALLEGRO_BITMAP *get_cell(int index);
         ALLEGRO_BITMAP *get_atlas();
         int get_num_sprites();

         void init();
         void destroy();
      };
   }
}


