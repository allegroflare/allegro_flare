#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/MultiMesh.hpp>
#include <AllegroFlare/MultiMeshUVAtlas.hpp>
#include <AllegroFlare/MusicMesh/FontCharacterAtlasBuilder.hpp>
#include <AllegroFlare/MusicMesh/Stamp.hpp>
#include <allegro5/allegro_font.h>
#include <cstdint>
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
         uint32_t next_id;
         AllegroFlare::MultiMesh multi_mesh;
         AllegroFlare::MultiMeshUVAtlas multi_mesh_uv_atlas;
         AllegroFlare::MusicMesh::FontCharacterAtlasBuilder font_character_atlas_builder;
         bool initialized;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         MusicMesh(AllegroFlare::FontBin* font_bin=nullptr);
         ~MusicMesh();

         void set_multi_mesh_uv_atlas(AllegroFlare::MultiMeshUVAtlas multi_mesh_uv_atlas);
         std::vector<AllegroFlare::MusicMesh::Stamp> get_stamps() const;
         uint32_t get_next_id() const;
         AllegroFlare::MultiMeshUVAtlas get_multi_mesh_uv_atlas() const;
         int obtain_font_ascent();
         void initialize();
         void add_music_symbol(float x=0, float y=0, uint32_t music_symbol_to_stamp=0);
         void remove_stamp_at(int index_of_stamp=0);
         int find_atlas_index_for_symbol(uint32_t music_symbol_to_stamp=0);
         void render();
      };
   }
}



