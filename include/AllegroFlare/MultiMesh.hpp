#pragma once


#include <allegro5/allegro_primitives.h>


namespace AllegroFlare
{
   class MultiMesh
   {
   private:
      ALLEGRO_VERTEX_BUFFER* vertex_buffer;
      ALLEGRO_INDEX_BUFFER* index_buffer;
      bool initialized;

   public:
      MultiMesh();
      ~MultiMesh();

      void initialize();
      void append();
      void remove();
      void render();
   };
}



