#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <string>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class Basic2D
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         std::string atlas_bitmap_filename;
         int atlas_bitmap_tile_width;
         int atlas_bitmap_tile_height;
         AllegroFlare::TileMaps::PrimMeshAtlas atlas;
         AllegroFlare::TileMaps::PrimMesh prim_mesh;
         AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
         bool initialized;

      protected:


      public:
         Basic2D(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string atlas_bitmap_filename="[atlas_bitmap_filename-unset]", int atlas_bitmap_tile_width=1, int atlas_bitmap_tile_height=1);
         ~Basic2D();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         std::string get_atlas_bitmap_filename() const;
         int get_atlas_bitmap_tile_width() const;
         int get_atlas_bitmap_tile_height() const;
         AllegroFlare::TileMaps::PrimMeshAtlas &get_atlas_ref();
         AllegroFlare::TileMaps::PrimMesh &get_prim_mesh_ref();
         AllegroFlare::TileMaps::TileMap<int> &get_collision_tile_map_ref();
         void set_atlas_configuration(std::string atlas_bitmap_filename="[unset-atlas_bitmap_filename]", int atlas_bitmap_tile_width=1, int atlas_bitmap_tile_height=1);
         void initialize();
         int get_num_rows();
         int get_num_columns();
         void resize(int num_columns=1, int num_rows=1);
         void rescale_tile_dimensions_to(float tile_width=1, float tile_height=1);
         void random_fill();
         float infer_real_width();
         float infer_real_height();
         float obtain_tile_width();
         float obtain_tile_height();
         void render();
      };
   }
}



