#pragma once


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
      bool initialized;

   public:
      MultiMesh();
      ~MultiMesh();

      void set_texture(ALLEGRO_BITMAP* texture);
      ALLEGRO_BITMAP* get_texture() const;
      void initialize();
      void append(float x=0, float y=0, float w=1, float h=1, float u1=100.0f, float v1=100.0f, float u2=200.0f, float v2=200.0f);
      void remove(int item_index=0);
      void render();
   };
}



