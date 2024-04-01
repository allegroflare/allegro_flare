#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <vector>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>



namespace AllegroFlare
{
   namespace FrameAnimation
   {
      class SpriteSheet
      {
      private:
         ALLEGRO_BITMAP *atlas;
         int sprite_width;
         int sprite_height;
         int num_rows;
         int num_columns;
         int scale;
         bool initialized;
         bool destroyed;
         AllegroFlare::TileMaps::PrimMeshAtlas new_atlas;
         std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> new_tile_index;

      public:
         SpriteSheet(ALLEGRO_BITMAP *atlas=nullptr, int sprite_width=48, int sprite_height=48, int scale=1);
         ~SpriteSheet();

         ALLEGRO_BITMAP *get_sprite(int index);
         ALLEGRO_BITMAP *get_cell(int index);
         ALLEGRO_BITMAP *get_atlas();
         int get_num_sprites();

         void initialize();
         void destroy();
      };
   }
}


