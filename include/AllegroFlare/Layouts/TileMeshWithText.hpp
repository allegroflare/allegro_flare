#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Layouts/Elements/Text.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMesh.hpp>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <map>
#include <string>
#include <tuple>


namespace AllegroFlare
{
   namespace Layouts
   {
      class TileMeshWithText
      {
      public:
         static constexpr char* DEFAULT_PRIM_MESH_ATLAS_FILENAME = (char*)"ascii_glyphs_12x16-07.png";

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::string tmj_filename;
         std::string prim_mesh_atlas_filename;
         AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas;
         AllegroFlare::TileMaps::TileMesh tile_mesh;
         std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots;
         std::map<std::string, std::string> text_data;
         int scale;
         static int _multiline_text_line_number;
         bool initialized;
         ALLEGRO_FONT* obtain_font(int font_size=-18);
         ALLEGRO_FONT* obtain_custom_font(std::string font_family="[unset-font_family]", int font_size=-18);

      protected:


      public:
         TileMeshWithText(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string tmj_filename="[unset-tmj_filename]", std::string prim_mesh_atlas_filename=DEFAULT_PRIM_MESH_ATLAS_FILENAME, AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas={}, AllegroFlare::TileMaps::TileMesh tile_mesh={}, std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots={});
         ~TileMeshWithText();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_tmj_filename(std::string tmj_filename);
         void set_prim_mesh_atlas_filename(std::string prim_mesh_atlas_filename);
         void set_prim_mesh_atlas(AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas);
         void set_tile_mesh(AllegroFlare::TileMaps::TileMesh tile_mesh);
         void set_text_slots(std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots);
         void set_scale(int scale);
         std::map<std::string, std::string> get_text_data() const;
         int get_scale() const;
         bool get_initialized() const;
         float translate_alignment_string_to_float(std::string alignment_string="[unset-alignment_string]");
         void initialize();
         float get_effective_width();
         float get_effective_height();
         void set_text_data(std::map<std::string, std::string> text_data={});
         static std::tuple<bool, bool, bool, bool, int> extract_tmj_tile_flip_properties(uint32_t tmj_tile_value=0);
         void render();
         bool compare_maps(std::map<std::string, std::string> map1={}, std::map<std::string, std::string> map2={});
         std::string lookup_font_identifier_by_family(std::string font_family="[unset-font_family]");
         static bool multiline_text_draw_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         int count_num_lines_will_render(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string* text=nullptr);
      };
   }
}



