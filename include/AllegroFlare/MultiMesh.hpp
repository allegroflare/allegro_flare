#pragma once


#include <allegro5/allegro_primitives.h>


namespace AllegroFlare
{
   class MultiMesh
   {
   private:
      ALLEGRO_VERTEX_BUFFER* vertex_buffer;
      ALLEGRO_INDEX_BUFFER* index_buffer;
      int indexes_in_use;
      bool initialized;

   public:
      MultiMesh();
      ~MultiMesh();

      void initialize();
      void append(float x=0, float y=0, float w=1, float h=1);
      void remove(int at_index=0);
      void render();
   };
}



