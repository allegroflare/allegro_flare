#pragma once


#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class TileMesh
      {
      private:
         AllegroFlare::TileMaps::PrimMeshAtlas* atlas;
         std::vector<ALLEGRO_VERTEX> vertexes;
         ALLEGRO_VERTEX_BUFFER* vertex_buffer;
         std::vector<int> tile_ids;
         int num_columns;
         int num_rows;
         int tile_width;
         int tile_height;
         bool yz_swapped;
         bool initialized;

      protected:


      public:
         TileMesh(AllegroFlare::TileMaps::PrimMeshAtlas* atlas=nullptr, int num_columns=0, int num_rows=0, int tile_width=1, int tile_height=1);
         ~TileMesh();

         void set_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* atlas);
         AllegroFlare::TileMaps::PrimMeshAtlas* get_atlas() const;
         std::vector<int> get_tile_ids() const;
         int get_num_columns() const;
         int get_num_rows() const;
         int get_tile_width() const;
         int get_tile_height() const;
         bool get_initialized() const;
         std::vector<ALLEGRO_VERTEX> &get_vertexes_ref();
         void initialize();
         void resize(int num_columns=0, int num_rows=0);
         void render(bool draw_outline=false);
         void set_tile_id(int tile_x=0, int tile_y=0, int tile_id=0);
         int get_tile_id(int tile_x=0, int tile_y=0);
         void set_tile_uv(int tile_x=0, int tile_y=0, int u1=0, int v1=0, int u2=0, int v2=0);
         int infer_num_vertexes();
         int infer_num_tiles();
         void rescale_tile_dimensions_to(int new_tile_width=0, int new_tile_height=0);
         void set_tile_width(int tile_width=0);
         void set_tile_height(int tile_width=0);
         int get_real_width();
         int get_real_height();
         void swap_yz();
      };
   }
}



