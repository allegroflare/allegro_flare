#pragma once



#include <AllegroFlare/TileMaps/PrimMeshAtlasIndexRecord.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


// TODO: Fix argument order in "TileAtlasBuilder::build_scaled_and_extruded"

namespace AllegroFlare::TileMaps
{
   class PrimMeshAtlas
   {
   private:
      ALLEGRO_BITMAP *bitmap; // Future: remove ALLEGRO_BITMAP from this object
      std::string bitmap_filename;
      int tile_width;
      int tile_height;
      int tile_spacing;
      std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index;

   public:
      PrimMeshAtlas();
      ~PrimMeshAtlas();

      void clear();

      // duplicate_bitmap_and_load will *copy* the bitmap that you pass into it.  You probably would
      // want to al_destroy_bitmap the bitmap that you passed in after loading.
      void duplicate_bitmap_and_load(ALLEGRO_BITMAP *source_bitmap, int tile_width, int tile_height, int spacing=0);

      std::string get_bitmap_filename() const;
      int get_tile_width() const;
      int get_tile_height() const;
      int get_tile_spacing() const;

      void set_bitmap_filename(std::string bitmap_filename="unset-bitmap-filename.png");
      void set_tile_width(int tile_width); // TODO: important, the mesh needs to be refreshed if these are changed
      void set_tile_height(int tile_height);
      void set_tile_spacing(int tile_spacing);

      ALLEGRO_BITMAP *get_bitmap();
      int get_tile_index_size();
      int get_bitmap_width();
      int get_bitmap_height();

      bool get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2);
      bool get_tile_uv(int index_num, float *u1, float *v1, float *u2, float *v2);
      ALLEGRO_BITMAP *get_tile_sub_bitmap(int index_num);

      std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> get_tile_index();
   };
}


