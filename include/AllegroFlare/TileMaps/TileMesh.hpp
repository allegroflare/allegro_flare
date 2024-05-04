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
         TileMesh();
         ~TileMesh();

         void initialize();
      };
   }
}



