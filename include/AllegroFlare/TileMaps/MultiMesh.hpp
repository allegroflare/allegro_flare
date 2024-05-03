#pragma once


#include <AllegroFlare/TileMaps/MultiMeshUVAtlas.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstddef>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class MultiMesh
      {
      public:
         static constexpr std::size_t VERTICES_PER_ITEM = 6;
         static constexpr std::size_t DEFAULT_NUM_ITEMS = 256;

      private:
         std::size_t num_items;
         ALLEGRO_VERTEX_BUFFER* vertex_buffer;
         ALLEGRO_VERTEX_DECL* vertex_decl;
         ALLEGRO_BITMAP* texture;
         int vertices_in_use;
         AllegroFlare::TileMaps::MultiMeshUVAtlas atlas;
         bool initialized;

      protected:


      public:
         MultiMesh(std::size_t num_items=DEFAULT_NUM_ITEMS);
         ~MultiMesh();

         void set_texture(ALLEGRO_BITMAP* texture);
         std::size_t get_num_items() const;
         ALLEGRO_BITMAP* get_texture() const;
         void set_atlas(AllegroFlare::TileMaps::MultiMeshUVAtlas atlas={});
         void set_num_items(std::size_t num_items=DEFAULT_NUM_ITEMS);
         int infer_num_items_in_use();
         int infer_largest_index_num_in_use();
         void initialize();
         int append(int atlas_item_index_num=0, float x=0, float y=0);
         int append_raw(float x=0, float y=0, float w=1, float h=1, float u1=100.0f, float v1=100.0f, float u2=200.0f, float v2=200.0f);
         int remove(int item_index=0);
         void render();
      };
   }
}



