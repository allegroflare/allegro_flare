#pragma once


#include <AllegroFlare/MultiMeshUVAtlas.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


namespace AllegroFlare
{
   class MultiMesh
   {
   private:
      ALLEGRO_VERTEX_BUFFER* vertex_buffer;
      ALLEGRO_BITMAP* texture;
      int num_items;
      int vertices_in_use;
      int VERTEXES_PER_ITEM;
      AllegroFlare::MultiMeshUVAtlas atlas;
      bool initialized;

   public:
      MultiMesh();
      ~MultiMesh();

      void set_texture(ALLEGRO_BITMAP* texture);
      ALLEGRO_BITMAP* get_texture() const;
      void set_atlas(AllegroFlare::MultiMeshUVAtlas atlas={});
      void initialize();
      void append_item_from_atlas_index(int atlas_item_index_num=0, float x=0, float y=0);
      void append(float x=0, float y=0, float w=1, float h=1, float u1=100.0f, float v1=100.0f, float u2=200.0f, float v2=200.0f);
      int remove(int item_index=0);
      void render();
   };
}



