#pragma once


#include <Tileo/TileoTileVertex.hpp>
#include <allegro5/allegro_primitives.h>


namespace Tileo
{
   class TileoTileVertexAllegroVertexDeclaration
   {
   private:
      ALLEGRO_VERTEX_DECL* vertex_declaration;
      bool initialized;
      bool destroyed;

   protected:


   public:
      TileoTileVertexAllegroVertexDeclaration();
      ~TileoTileVertexAllegroVertexDeclaration();

      bool get_initialized() const;
      bool get_destroyed() const;
      ALLEGRO_VERTEX_DECL* get_vertex_declaration();
      static TILEO_TILE_VERTEX build_empty_vertex();
      void initialize();
      void destroy();
   };
}



