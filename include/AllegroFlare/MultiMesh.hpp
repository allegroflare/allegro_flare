#pragma once


#include <AllegroFlare/MultiMeshUVAtlas.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


namespace AllegroFlare
{
   class MultiMesh
   {
   private:
      int num_items;
      ALLEGRO_VERTEX_BUFFER* vertex_buffer;
      ALLEGRO_VERTEX_DECL* vertex_decl;
      ALLEGRO_BITMAP* texture;
      int vertices_in_use;
      int VERTEXES_PER_ITEM;
      AllegroFlare::MultiMeshUVAtlas atlas;
      bool initialized;

   public:
      MultiMesh(int num_items=256);
      ~MultiMesh();

      void set_texture(ALLEGRO_BITMAP* texture);
      int get_num_items() const;
      ALLEGRO_BITMAP* get_texture() const;
      void set_atlas(AllegroFlare::MultiMeshUVAtlas atlas={});
      void set_num_items(int num_items=256);
      void initialize();
      void append(int atlas_item_index_num=0, float x=0, float y=0);
      void append_raw(float x=0, float y=0, float w=1, float h=1, float u1=100.0f, float v1=100.0f, float u2=200.0f, float v2=200.0f);
      int remove(int item_index=0);
      void render();
   };
}



