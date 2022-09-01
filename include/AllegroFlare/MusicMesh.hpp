#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/MultiMesh.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   class MusicMesh
   {
   private:
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::MultiMesh multi_mesh;
      int max_num_symbols;
      bool initialized;
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      MusicMesh(AllegroFlare::FontBin* font_bin=nullptr);
      ~MusicMesh();

      bool get_initialized() const;
      void initialize();
      void add_symbol();
      void render();
   };
}



