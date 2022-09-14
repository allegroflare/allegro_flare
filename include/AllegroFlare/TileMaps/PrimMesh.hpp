#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <vector>


namespace AllegroFlare::TileMaps
{
   class PrimMesh
   {
   private:
      AllegroFlare::TileMaps::PrimMeshAtlas *atlas;
      std::vector<ALLEGRO_VERTEX> vertexes;
      std::vector<int> tile_ids;
      int num_columns;
      int num_rows;
      int tile_width;
      int tile_height;
      bool initialized;

      void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

   public:
      PrimMesh(
         AllegroFlare::TileMaps::PrimMeshAtlas *atlas=nullptr,
         int num_columns=0,
         int num_rows=0,
         int tile_width=1,
         int tile_heigh=1
      );
      ~PrimMesh();

      void initialize();

      void resize(int num_columns=0, int num_rows=0);

      std::vector<ALLEGRO_VERTEX> &get_vertexes_ref();

      int get_num_columns() const;
      int get_num_rows() const;
      int infer_num_tiles();

      int get_tile_width() const;
      int get_tile_height() const;
      int get_real_width() const;
      int get_real_height() const;

      bool set_tile(int tile_x, int tile_y, int tile_id);
      bool set_tile_id(int tile_x, int tile_y, int tile_id);
      int get_tile_id(int tile_x, int tile_y) const;
      std::vector<int> get_tile_ids() const;
      AllegroFlare::TileMaps::PrimMeshAtlas *get_atlas() const;
   
      void render(bool draw_outline=false);
   };
}


