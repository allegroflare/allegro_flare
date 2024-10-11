#pragma once


#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <set>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class TileMesh
      {
      private:
         AllegroFlare::TileMaps::PrimMeshAtlas* atlas;
         std::vector<ALLEGRO_VERTEX> vertices;
         ALLEGRO_VERTEX_BUFFER* vertex_buffer;
         ALLEGRO_INDEX_BUFFER* index_buffer;
         std::vector<int> tile_ids;
         std::vector<int> index_vertices;
         std::set<std::pair<int, int>> h_flipped_tiles;
         std::set<std::pair<int, int>> v_flipped_tiles;
         std::set<std::pair<int, int>> d_flipped_tiles;
         int num_columns;
         int num_rows;
         int tile_width;
         int tile_height;
         bool holding_vertex_buffer_update_until_refresh;
         bool vertex_buffer_is_dirty;
         bool yz_swapped;
         bool initialized;
         void h_flip_vertices(int* u1=nullptr, int* v1=nullptr, int* u2=nullptr, int* v2=nullptr);
         void v_flip_vertices(int* u1=nullptr, int* v1=nullptr, int* u2=nullptr, int* v2=nullptr);

      protected:


      public:
         TileMesh(AllegroFlare::TileMaps::PrimMeshAtlas* atlas=nullptr, int num_columns=0, int num_rows=0, int tile_width=1, int tile_height=1);
         ~TileMesh();

         void set_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* atlas);
         AllegroFlare::TileMaps::PrimMeshAtlas* get_atlas() const;
         std::vector<int> get_tile_ids() const;
         std::vector<int> get_index_vertices() const;
         std::set<std::pair<int, int>> get_h_flipped_tiles() const;
         std::set<std::pair<int, int>> get_v_flipped_tiles() const;
         std::set<std::pair<int, int>> get_d_flipped_tiles() const;
         int get_num_columns() const;
         int get_num_rows() const;
         int get_tile_width() const;
         int get_tile_height() const;
         bool get_holding_vertex_buffer_update_until_refresh() const;
         bool get_vertex_buffer_is_dirty() const;
         bool get_initialized() const;
         std::vector<ALLEGRO_VERTEX> &get_vertices_ref();
         void initialize();
         void set_num_rows(int num_rows=0);
         void set_num_columns(int num_columns=0);
         void set_tile_ids(std::vector<int> tile_ids={});
         int remove_tile_xy_from_index(int tile_x=0, int tile_y=0);
         int remove_vertices_from_index_vertices(std::vector<int> vertices_to_remove={});
         std::vector<int> vertex_indices_for_tile_xy(int tile_x=0, int tile_y=0);
         void destroy();
         void disable_holding_vertex_buffer_update_until_refresh();
         void resize(int num_columns=0, int num_rows=0);
         void render(bool draw_outline=false);
         bool set_tile_id(int tile_x=0, int tile_y=0, int tile_id=0, bool flip_h=false, bool flip_v=false, bool flip_d=false, ALLEGRO_COLOR color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
         int get_tile_id(int tile_x=0, int tile_y=0);
         std::tuple<bool, bool, bool> get_tile_flip(int tile_x=0, int tile_y=0);
         void set_tile_uv(int tile_x=0, int tile_y=0, int u1=0, int v1=0, int u2=0, int v2=0, bool diagonal_flip=false, ALLEGRO_COLOR color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
         void set_tile_color(int tile_x=0, int tile_y=0, ALLEGRO_COLOR color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
         void refresh_vertex_buffer();
         int infer_num_vertices();
         int infer_num_tiles();
         void rescale_tile_dimensions_to(int new_tile_width=0, int new_tile_height=0);
         void set_tile_width(int new_tile_width=0);
         void set_tile_height(int new_tile_height=0);
         int get_real_width();
         int get_real_height();
         void swap_yz();
      };
   }
}



