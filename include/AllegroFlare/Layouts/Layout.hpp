#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Layouts/Elements/CursorDestination.hpp>
#include <AllegroFlare/Layouts/Elements/Frame.hpp>
#include <AllegroFlare/Layouts/Elements/Polygon.hpp>
#include <AllegroFlare/Layouts/Elements/Text.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMesh.hpp>
#include <AllegroFlare/Tiled/TMJObject.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Layouts
   {
      class Layout
      {
      public:
         static constexpr char* DEFAULT_PRIM_MESH_ATLAS_FILENAME = (char*)"ascii_glyphs_12x16-07.png";

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::string tmj_filename;
         float layout_width;
         float layout_height;
         bool tile_mesh_is_present;
         std::string prim_mesh_atlas_filename;
         AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas;
         AllegroFlare::TileMaps::TileMesh tile_mesh;
         std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots;
         std::map<std::string, std::string> text_data;
         std::map<int, AllegroFlare::Layouts::Elements::Polygon> polygons;
         std::map<int, AllegroFlare::Layouts::Elements::CursorDestination> cursor_destinations;
         std::map<int, AllegroFlare::Layouts::Elements::Frame> frames;
         int scale;
         static int _multiline_text_line_number;
         bool initialized;
         ALLEGRO_FONT* obtain_font(int font_size=-18);
         ALLEGRO_FONT* obtain_custom_font(std::string font_family="[unset-font_family]", int font_size=-18);

      protected:


      public:
         Layout(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string tmj_filename="[unset-tmj_filename]", std::string prim_mesh_atlas_filename=DEFAULT_PRIM_MESH_ATLAS_FILENAME, AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas={}, AllegroFlare::TileMaps::TileMesh tile_mesh={}, std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots={});
         ~Layout();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_tmj_filename(std::string tmj_filename);
         void set_prim_mesh_atlas_filename(std::string prim_mesh_atlas_filename);
         void set_prim_mesh_atlas(AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas);
         void set_tile_mesh(AllegroFlare::TileMaps::TileMesh tile_mesh);
         void set_text_slots(std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots);
         void set_scale(int scale);
         bool get_tile_mesh_is_present() const;
         std::map<std::string, std::string> get_text_data() const;
         int get_scale() const;
         bool get_initialized() const;
         float get_layout_width();
         float get_layout_height();
         void initialize();
         float get_effective_width();
         float get_effective_height();
         AllegroFlare::Layouts::Elements::Polygon* find_polygon_by_tmj_object_id(int tmj_object_id=0);
         AllegroFlare::Layouts::Elements::Polygon* find_polygon_by_name(std::string name="[unset-name]");
         AllegroFlare::Layouts::Elements::CursorDestination* get_initial_cursor_destination();
         AllegroFlare::Layouts::Elements::CursorDestination* find_cursor_destination_by_tmj_object_id(int tmj_object_id=0);
         AllegroFlare::Layouts::Elements::CursorDestination* find_cursor_destination_by_name(std::string name="[unset-name]");
         AllegroFlare::Layouts::Elements::Frame* find_frame_by_tmj_object_id(int tmj_object_id=0);
         AllegroFlare::Layouts::Elements::Frame* find_frame_by_name(std::string name="[unset-name]");
         void set_text_data(std::map<std::string, std::string> text_data={});
         void set_text_data_require_all(std::map<std::string, std::string> text_data={});
         void set_text_data_require_present(std::map<std::string, std::string> text_data={});
         void set_text_data_field(std::string name="[unset-name]", std::string value="[unset-value]");
         bool text_data_field_exists(std::string name="[unset-name]");
         std::string get_text_data_field_value(std::string name="[unset-name]");
         int extract_int_or_default(AllegroFlare::Tiled::TMJObject* object=nullptr, std::string key="[unset-key]", int default_fallback=0);
         static std::tuple<bool, bool, bool, bool, int> extract_tmj_tile_flip_properties(uint32_t tmj_tile_value=0);
         void render();
         void render_text_slots();
         void render_text_debug();
         void render_debug();
         void render_cursor_destinations_debug(float line_thickness=2.0);
         void render_frames_debug(float line_thickness=2.0);
         std::pair<bool, std::pair<std::vector<std::string>, std::vector<std::string>>> compare_maps(std::map<std::string, std::string> map1={}, std::map<std::string, std::string> map2={});
         std::string lookup_font_identifier_by_family(std::string font_family="[unset-font_family]");
         void draw_container_frame(float x=0.0f, float y=0.0f, float x2=0.0f, float y2=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float line_thickness=0.0f);
         static bool multiline_text_draw_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         int count_num_lines_will_render(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string* text=nullptr);
      };
   }
}



