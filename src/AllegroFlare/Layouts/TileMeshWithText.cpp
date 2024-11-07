

#include <AllegroFlare/Layouts/TileMeshWithText.hpp>

#include <AllegroFlare/ColorKit.hpp>
#include <AllegroFlare/Layouts/ElementFactory.hpp>
#include <AllegroFlare/Layouts/Text.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Layouts
{


int TileMeshWithText::_multiline_text_line_number = 0;


TileMeshWithText::TileMeshWithText(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::string tmj_filename, std::string prim_mesh_atlas_filename, AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas, AllegroFlare::TileMaps::TileMesh tile_mesh, std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , tmj_filename(tmj_filename)
   , prim_mesh_atlas_filename(prim_mesh_atlas_filename)
   , prim_mesh_atlas(prim_mesh_atlas)
   , tile_mesh(tile_mesh)
   , text_slots(text_slots)
   , text_data({})
   , scale(3)
   , initialized(false)
{
}


TileMeshWithText::~TileMeshWithText()
{
}


void TileMeshWithText::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void TileMeshWithText::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void TileMeshWithText::set_tmj_filename(std::string tmj_filename)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_tmj_filename]: error: guard \"get_initialized()\" not met.");
   this->tmj_filename = tmj_filename;
}


void TileMeshWithText::set_prim_mesh_atlas_filename(std::string prim_mesh_atlas_filename)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_prim_mesh_atlas_filename]: error: guard \"get_initialized()\" not met.");
   this->prim_mesh_atlas_filename = prim_mesh_atlas_filename;
}


void TileMeshWithText::set_prim_mesh_atlas(AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_prim_mesh_atlas]: error: guard \"get_initialized()\" not met.");
   this->prim_mesh_atlas = prim_mesh_atlas;
}


void TileMeshWithText::set_tile_mesh(AllegroFlare::TileMaps::TileMesh tile_mesh)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_tile_mesh]: error: guard \"get_initialized()\" not met.");
   this->tile_mesh = tile_mesh;
}


void TileMeshWithText::set_text_slots(std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_text_slots]: error: guard \"get_initialized()\" not met.");
   this->text_slots = text_slots;
}


void TileMeshWithText::set_scale(int scale)
{
   if (get_initialized()) throw std::runtime_error("[TileMeshWithText::set_scale]: error: guard \"get_initialized()\" not met.");
   this->scale = scale;
}


std::map<std::string, std::string> TileMeshWithText::get_text_data() const
{
   return text_data;
}


int TileMeshWithText::get_scale() const
{
   return scale;
}


bool TileMeshWithText::get_initialized() const
{
   return initialized;
}


float TileMeshWithText::translate_alignment_string_to_float(std::string alignment_string)
{
   if (alignment_string == "center") return 0.5;
   if (alignment_string == "left") return 0.0;
   if (alignment_string == "right") return 1.0;
   if (alignment_string == "bottom") return 1.0;
   if (alignment_string == "top") return 0.0;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Layouts::TileMeshWithText::translate_alignment_string_to_float",
      "Unrecognized alignment string \"" + alignment_string + "\"."
   );
   return 0.0f;
}

void TileMeshWithText::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::initialize]: error: guard \"font_bin\" not met");
   }
   AllegroFlare::Tiled::TMJDataLoader tmj_data_loader(tmj_filename);
   tmj_data_loader.load();

   // Colors
   ALLEGRO_COLOR color = al_color_html("b8e8e8");
   ALLEGRO_COLOR c_back = AllegroFlare::ColorKit::fade(color, 0.2);
   ALLEGRO_COLOR c_mid = AllegroFlare::ColorKit::fade(color, 0.35);
   ALLEGRO_COLOR c_upper_mid = AllegroFlare::ColorKit::fade(color, 0.75);
   ALLEGRO_COLOR c_front = AllegroFlare::ColorKit::mix(color, ALLEGRO_COLOR{1, 1, 1, 1}, 0.6);

   // TODO: Confirm that there is only one tileset in use (multiple tilesets will cause unexpected results)

   // Load the text objects
   tmj_data_loader.for_each_object([this](AllegroFlare::Tiled::TMJObject* object, void *user_data){
      if (object->text__is_present)
      {
         // Set the text slots
         text_slots[object->name] = AllegroFlare::Layouts::ElementFactory::build_text_from_tmj_object(object);

         // Set the text data
         std::string text = object->text__text;
         text_data[object->name] = text;
      }
   });

   // Load the tile data
   int num_rows = tmj_data_loader.get_num_rows();
   int num_columns = tmj_data_loader.get_num_columns();
   bool opacity_tilelayer_is_present = false;
   if (!tmj_data_loader.tilelayer_exists("visual"))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Layouts::TileMeshWithText::initialize",
         "Missing \"visual\" tilelayer."
      );
   }
   if (!tmj_data_loader.tilelayer_exists("opacity"))
   {
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Layouts::TileMeshWithText::initialize",
         "The \"opacity\" tilelayer is not present. This layer is optional so this message is provided for "
            "debugging."
      );
   }
   else
   {
      opacity_tilelayer_is_present = true;
   }

   // Build the atlas
   // TODO: Audit this to be sure the bitmaps are created and destroyed as expected
   std::string tileset_filename = prim_mesh_atlas_filename;
   ALLEGRO_BITMAP *atlas_bitmap = bitmap_bin->auto_get(tileset_filename);
   prim_mesh_atlas.set_bitmap_filename(tileset_filename);
   // - Scale and extrude the atlas
   int tile_atlas_tile_width = 12;
   int tile_atlas_tile_height = 16;
   int tile_scale = 3;
   ALLEGRO_BITMAP *scaled_extruded_tile_map_bitmap =
      AllegroFlare::TileMaps::TileAtlasBuilder::create_scaled_and_extruded(
      atlas_bitmap,
      tile_scale,
      tile_atlas_tile_width,
      tile_atlas_tile_height
      );
   prim_mesh_atlas.duplicate_bitmap_and_load(
      scaled_extruded_tile_map_bitmap,
      tile_atlas_tile_width*tile_scale,
      tile_atlas_tile_height*tile_scale,
      1
   );
   //al_init_image_addon();
   //al_save_bitmap("foobar.png", scaled_extruded_tile_map_bitmap);
   al_destroy_bitmap(scaled_extruded_tile_map_bitmap); // TODO: Confirm destruction is correct here
   bitmap_bin->destroy(tileset_filename);

   // - Build the tile_mesh
   //int width = room_width_in_tiles; //7;
   //int depth = room_depth_in_tiles; //5;
   tile_mesh.set_atlas(&prim_mesh_atlas);
   tile_mesh.set_num_rows(num_rows);
   tile_mesh.set_num_columns(num_columns);
   //if (!tmj_data_loader.tilelayer_exists("visual"))
   //{
      //AllegroFlare::Logger::throw_error(
         //"Character3D::Room::initialize",
         //"Expecting tilelayer named \"visual\" to be present when loading tmj file \"" + tmj_filename + "\""
      //);
   //}
   std::vector<int> visual_tilelayer_data = tmj_data_loader.get_tilelayer_data_by_name("visual");
   std::vector<int> opacity_tilelayer_data; // = tmj_data_loader.get_tilelayer_data_by_name("opacity");
   tile_mesh.initialize();
   std::vector<ALLEGRO_COLOR> possible_random_colors = { c_back, c_mid, c_upper_mid, c_front }; // DEVELOPMENT
   AllegroFlare::Random random; // DEVELOPMENT

   if (opacity_tilelayer_is_present)
   {
      opacity_tilelayer_data = tmj_data_loader.get_tilelayer_data_by_name("opacity");
   }

   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         int tile_id = visual_tilelayer_data[x + y * num_columns];
         auto tile_flip_data = extract_tmj_tile_flip_properties(tile_id);

         bool horizontal_flip_flag_present = std::get<0>(tile_flip_data);
         bool vertical_flip_flag_present = std::get<1>(tile_flip_data);
         bool antidiagonal_flip_flag_present = std::get<2>(tile_flip_data);
         bool hex_120_rotation_flag_present = std::get<3>(tile_flip_data);

         int raw_tile_id = std::get<4>(tile_flip_data);
         bool has_horizontal_flip = horizontal_flip_flag_present;
         bool has_vertical_flip = vertical_flip_flag_present;
         bool has_diagonal_flip = antidiagonal_flip_flag_present;

         //int tile_id = visual_tilelayer_data[x + y * num_columns];
         if (tile_id == 0)
         {
            tile_mesh.remove_tile_xy_from_index(x, y);
         }
         else
         {
            tile_mesh.set_tile_id(x, y, raw_tile_id-1, has_horizontal_flip, has_vertical_flip, has_diagonal_flip);
         }

         // TODO: tile_mesh.set_tile_color(...)
         if (opacity_tilelayer_is_present)
         {
            int tile_id = opacity_tilelayer_data[x + y * num_columns];
            auto tile_flip_data = extract_tmj_tile_flip_properties(tile_id);
            int raw_tile_id = std::get<4>(tile_flip_data);

            float opacity = 1.0;
            //ALLEGRO_COLOR final_color = ALLEGRO_COLOR{1, 1, 1, 1};
            if (raw_tile_id == 0) opacity = 1.0;
            else
            {
               raw_tile_id -= 1;
               if (raw_tile_id == 0) opacity = 1.0;
               else if (raw_tile_id == 1) opacity = 0.75;
               else if (raw_tile_id == 2) opacity = 0.35;
               else if (raw_tile_id == 3) opacity = 0.20;
               else if (raw_tile_id == 4) opacity = 0.0;
            }
            //tile_mesh.set_tile_id(x, y, raw_tile_id-1, has_horizontal_flip, has_vertical_flip, has_diagonal_flip);

            ALLEGRO_COLOR final_color = ALLEGRO_COLOR{opacity, opacity, opacity, opacity};

            // Set the color
            tile_mesh.set_tile_color(x, y, final_color);
         }
      }
   }
   tile_mesh.rescale_tile_dimensions_to(12 * scale, 16 * scale);
   tile_mesh.refresh_vertex_buffer();
   tile_mesh.refresh_index_vertices_from_removed_tiles_and_refresh_index_buffer();

   initialized = true;
   return;
}

float TileMeshWithText::get_effective_width()
{
   // TODO: Rename this
   return tile_mesh.get_real_width();
}

float TileMeshWithText::get_effective_height()
{
   // TODO: Rename this
   return tile_mesh.get_real_height();
}

void TileMeshWithText::set_text_data(std::map<std::string, std::string> text_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::set_text_data]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::set_text_data]: error: guard \"initialized\" not met");
   }
   if (!(compare_maps(this->text_data, text_data)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::set_text_data]: error: guard \"compare_maps(this->text_data, text_data)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::set_text_data]: error: guard \"compare_maps(this->text_data, text_data)\" not met");
   }
   // TODO: Consider allowing setting text data before initialize, and having the template also valdate at
   // initialize time as well.
   this->text_data = text_data;
   return;
}

std::tuple<bool, bool, bool, bool, int> TileMeshWithText::extract_tmj_tile_flip_properties(uint32_t tmj_tile_value)
{
   // Extract the flag values
   bool horizontal_flip_flag_present = (tmj_tile_value & 0x80000000) != 0;
   bool vertical_flip_flag_present = (tmj_tile_value & 0x40000000) != 0;
   bool antidiagonal_flip_flag_present = (tmj_tile_value & 0x20000000) != 0;
   bool hex_120_rotation_flag_present = (tmj_tile_value & 0x10000000) != 0;

   // Clear all the flags
   int filtered_tile_value = tmj_tile_value& ~(0x80000000 | 0x40000000 | 0x20000000 | 0x1000000);

   return std::tuple<bool, bool, bool, bool, int>{
      horizontal_flip_flag_present,
      vertical_flip_flag_present,
      antidiagonal_flip_flag_present,
      hex_120_rotation_flag_present,
      filtered_tile_value
   };
}

void TileMeshWithText::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::render]: error: guard \"initialized\" not met");
   }
   // Render the mesh data
   tile_mesh.render();

   // Render the text slots
   for (auto &text_slot_ : text_slots)
   {
      AllegroFlare::Layouts::Elements::Text &text_slot = text_slot_.second;

      float x = text_slot.x;
      float y = text_slot.y;
      float w = text_slot.width;
      float h = text_slot.height;
      float align_x = text_slot.align_x;
      float align_y = text_slot.align_y;
      std::string &font_family = text_slot.font_family;
      int font_size = text_slot.font_size;
      ALLEGRO_COLOR &color = text_slot.color;


      // TODO: Confirm exists
      //std::string &text = text_data[text_slot.first];
      std::string &text = text_data[text_slot_.first];

      //float x = 1920/2;
      //float y = 1080/3;
      ALLEGRO_FONT *font = obtain_custom_font(font_family, font_size);
      //float text_width = al_get_text_width(font, text.c_str());
      float text_height = al_get_font_line_height(font);
      //float h_text_width = text_width/2;
      float h_text_height = text_height/2;
      float rendered_text_height = 0.0f;
      float practical_text_box_width = w * scale;
      if (align_y < -0.001f || align_y > 0.001f) // If non-zero
      {
         int num_lines_will_render = count_num_lines_will_render(font, practical_text_box_width, &text);
         rendered_text_height = num_lines_will_render * (float)al_get_font_line_height(font) / scale;
      }

      int allegro_text_align = (align_x == 0.5) ? ALLEGRO_ALIGN_CENTER : (align_x == 1.0) ? ALLEGRO_ALIGN_RIGHT : ALLEGRO_ALIGN_LEFT;

      float final_y = y - (rendered_text_height*align_y) + (h*align_y);

      al_draw_multiline_text(
         font,
         color, //ALLEGRO_COLOR{1, 1, 1, 1},
         (x + w*align_x) * scale,
         //(y + h*align_y - rendered_text_height*align_y) * scale,
         final_y * scale,
         w * scale,
         al_get_font_line_height(font),
         allegro_text_align,
         text.c_str()
      );

      //ALLEGRO_COLOR debug_color = ALLEGRO_COLOR{0.95, 0.26, 0.1, 1.0};
      //al_draw_rectangle(x*scale, y*scale, (x+w)*scale, (y+h)*scale, debug_color, 2.0);
   }

   return;
}

bool TileMeshWithText::compare_maps(std::map<std::string, std::string> map1, std::map<std::string, std::string> map2)
{
   std::vector<std::string> missing_in_map2;
   std::vector<std::string> missing_in_map1;

   // Find keys in map1 that are missing in map2
   for (const auto& pair : map1)
   {
      if (map2.find(pair.first) == map2.end())
      {
         missing_in_map2.push_back(pair.first);
      }
   }

   // Find keys in map2 that are missing in map1
   for (const auto& pair : map2)
   {
      if (map1.find(pair.first) == map1.end())
      {
         missing_in_map1.push_back(pair.first);
      }
   }

   // Output results
   if (!missing_in_map2.empty())
   {
      std::cout << "Keys in map1 but missing in map2:\n";
      for (const auto& key : missing_in_map2)
      {
         std::cout << key << std::endl;
      }
   }
   else
   {
      std::cout << "No keys are missing in map2 from map1.\n";
   }

   if (!missing_in_map1.empty())
   {
      std::cout << "Keys in map2 but missing in map1:\n";
      for (const auto& key : missing_in_map1)
      {
         std::cout << key << std::endl;
      }
   }
   else
   {
      std::cout << "No keys are missing in map1 from map2.\n";
   }

   return missing_in_map1.empty() && missing_in_map2.empty();
}

std::string TileMeshWithText::lookup_font_identifier_by_family(std::string font_family)
{
   std::map<std::string, std::string> font_family_to_font_identifier_map = {
      { "Azeret Mono", "AzeretMono-Regular.ttf" },
      { "Michroma",    "Michroma-Regular.ttf" },
      { "Orbitron",    "Orbitron-Medium.ttf" },
      { "Oswald",      "Oswald-Medium.ttf" },
      { "Exan",        "Exan-Regular.ttf" },
   };

   if (font_family_to_font_identifier_map.find(font_family) == font_family_to_font_identifier_map.end())
   {
      // Font not found, return default
      return "Orbitron-Medium.ttf";
   }
   return font_family_to_font_identifier_map[font_family];
}

bool TileMeshWithText::multiline_text_draw_callback(int line_num, const char* line, int size, void* extra)
{
   _multiline_text_line_number = line_num;
   return true;
}

int TileMeshWithText::count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string* text)
{
   if (!(text))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::count_num_lines_will_render]: error: guard \"text\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::count_num_lines_will_render]: error: guard \"text\" not met");
   }
   if (text->empty()) return 0;

   _multiline_text_line_number = 0;
   al_do_multiline_text(font, max_width, text->c_str(), multiline_text_draw_callback, nullptr);

   // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
   return _multiline_text_line_number + 1;
}

ALLEGRO_FONT* TileMeshWithText::obtain_font(int font_size)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::obtain_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::obtain_font]: error: guard \"initialized\" not met");
   }
   //return font_bin->auto_get("Inter-Medium.ttf -14");
   std::stringstream result;
   result << "Orbitron-Medium.ttf " << std::to_string(font_size * scale);
   //result << "Orbitron-Medium.ttf " << std::to_string(font_size * scale);
   return font_bin->auto_get(result.str());
}

ALLEGRO_FONT* TileMeshWithText::obtain_custom_font(std::string font_family, int font_size)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::TileMeshWithText::obtain_custom_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::TileMeshWithText::obtain_custom_font]: error: guard \"initialized\" not met");
   }
   //return font_bin->auto_get("Inter-Medium.ttf -14");
   std::stringstream result;
   //result << "Orbitron-Medium.ttf " << std::to_string(font_size * scale);
   result << lookup_font_identifier_by_family(font_family) << " " << std::to_string(font_size * scale);
   //result << "Orbitron-Medium.ttf " << std::to_string(font_size * scale);
   return font_bin->auto_get(result.str());
}


} // namespace Layouts
} // namespace AllegroFlare


