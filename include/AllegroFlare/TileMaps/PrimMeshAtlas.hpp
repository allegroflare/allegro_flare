#pragma once


#include <AllegroFlare/TileMaps/PrimMeshAtlasIndexRecord.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class PrimMeshAtlas
      {
      private:
         ALLEGRO_BITMAP* bitmap;
         std::string bitmap_filename;
         int tile_width;
         int tile_height;
         int tile_spacing;
         std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index;

      protected:


      public:
         PrimMeshAtlas();
         ~PrimMeshAtlas();

         void set_bitmap_filename(std::string bitmap_filename);
         ALLEGRO_BITMAP* get_bitmap() const;
         std::string get_bitmap_filename() const;
         int get_tile_width() const;
         int get_tile_height() const;
         int get_tile_spacing() const;
         std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> get_tile_index() const;
         void set_tile_width(int tile_width=16);
         void set_tile_height(int tile_height=16);
         void set_tile_spacing(int tile_spacing=16);
         void clear();
         void duplicate_bitmap_and_load(ALLEGRO_BITMAP* source_bitmap=nullptr, int tile_width=16, int tile_height=16, int tile_spacing=0);
         int get_tile_index_size();
         int get_bitmap_width();
         int get_bitmap_height();
         bool get_tile_uv(int index_num=0, int* u1=nullptr, int* v1=nullptr, int* u2=nullptr, int* v2=nullptr);
         bool get_tile_uv(int index_num=0, float* u1=nullptr, float* v1=nullptr, float* u2=nullptr, float* v2=nullptr);
         ALLEGRO_BITMAP* get_tile_sub_bitmap(int index_num=0);
      };
   }
}



