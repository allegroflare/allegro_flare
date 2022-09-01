#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/MusicMesh/Stamp.hpp>
#include <allegro5/allegro_font.h>
#include <vector>


namespace AllegroFlare
{
   namespace MusicMesh
   {
      class MusicMesh
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<AllegroFlare::MusicMesh::Stamp> stamps;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         MusicMesh(AllegroFlare::FontBin* font_bin=nullptr);
         ~MusicMesh();

         std::vector<AllegroFlare::MusicMesh::Stamp> get_stamps() const;
         void render();
      };
   }
}



