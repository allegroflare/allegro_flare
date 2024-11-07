

#include <AllegroFlare/Layouts/Text.hpp>

#include <AllegroFlare/ColorKit.hpp>
#include <AllegroFlare/Layouts/ElementFactory.hpp>
#include <AllegroFlare/Layouts/Elements/Text.hpp>
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


int Text::_multiline_text_line_number = 0;


Text::Text(AllegroFlare::FontBin* font_bin, std::string tmj_filename, std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots)
   : font_bin(font_bin)
   , tmj_filename(tmj_filename)
   , layout_width(0.0f)
   , layout_height(0.0f)
   , text_slots(text_slots)
   , text_data({})
   , scale(3)
   , initialized(false)
{
}


Text::~Text()
{
}


void Text::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Text::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Text::set_tmj_filename(std::string tmj_filename)
{
   if (get_initialized()) throw std::runtime_error("[Text::set_tmj_filename]: error: guard \"get_initialized()\" not met.");
   this->tmj_filename = tmj_filename;
}


void Text::set_text_slots(std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots)
{
   if (get_initialized()) throw std::runtime_error("[Text::set_text_slots]: error: guard \"get_initialized()\" not met.");
   this->text_slots = text_slots;
}


void Text::set_scale(int scale)
{
   if (get_initialized()) throw std::runtime_error("[Text::set_scale]: error: guard \"get_initialized()\" not met.");
   this->scale = scale;
}


std::map<std::string, std::string> Text::get_text_data() const
{
   return text_data;
}


int Text::get_scale() const
{
   return scale;
}


bool Text::get_initialized() const
{
   return initialized;
}


float Text::get_layout_width()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::get_layout_width]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::get_layout_width]: error: guard \"initialized\" not met");
   }
   return layout_width;
}

float Text::get_layout_height()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::get_layout_height]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::get_layout_height]: error: guard \"initialized\" not met");
   }
   return layout_height;
}

void Text::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::initialize]: error: guard \"font_bin\" not met");
   }
   AllegroFlare::Tiled::TMJDataLoader tmj_data_loader(tmj_filename);
   tmj_data_loader.load();

   int num_rows = tmj_data_loader.get_num_rows();
   int num_columns = tmj_data_loader.get_num_columns();
   int tile_width = tmj_data_loader.get_tile_width();
   int tile_height = tmj_data_loader.get_tile_height();
   layout_width = num_columns * tile_width;
   layout_height = num_rows * tile_height;

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

   initialized = true;
   return;
}

void Text::set_text_data(std::map<std::string, std::string> text_data)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::set_text_data]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::set_text_data]: error: guard \"initialized\" not met");
   }
   if (!(compare_maps(this->text_data, text_data)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::set_text_data]: error: guard \"compare_maps(this->text_data, text_data)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::set_text_data]: error: guard \"compare_maps(this->text_data, text_data)\" not met");
   }
   // TODO: Consider allowing setting text data before initialize, and having the template also valdate at
   // initialize time as well.
   this->text_data = text_data;
   return;
}

void Text::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::render]: error: guard \"initialized\" not met");
   }
   //tile_mesh.render();
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

void Text::render_debug()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::render_debug]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::render_debug]: error: guard \"initialized\" not met");
   }
   //tile_mesh.render();
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

      // TODO: Consider adding cross-lines

      ALLEGRO_COLOR debug_color = ALLEGRO_COLOR{0.95, 0.26, 0.1, 1.0};
      al_draw_rectangle(x*scale, y*scale, (x+w)*scale, (y+h)*scale, debug_color, 2.0);
   }

   return;
}

bool Text::compare_maps(std::map<std::string, std::string> map1, std::map<std::string, std::string> map2)
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

std::string Text::lookup_font_identifier_by_family(std::string font_family)
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

bool Text::multiline_text_draw_callback(int line_num, const char* line, int size, void* extra)
{
   _multiline_text_line_number = line_num;
   return true;
}

int Text::count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string* text)
{
   if (!(text))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::count_num_lines_will_render]: error: guard \"text\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::count_num_lines_will_render]: error: guard \"text\" not met");
   }
   if (text->empty()) return 0;

   _multiline_text_line_number = 0;
   al_do_multiline_text(font, max_width, text->c_str(), multiline_text_draw_callback, nullptr);

   // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
   return _multiline_text_line_number + 1;
}

ALLEGRO_FONT* Text::obtain_font(int font_size)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::obtain_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::obtain_font]: error: guard \"initialized\" not met");
   }
   //return font_bin->auto_get("Inter-Medium.ttf -14");
   std::stringstream result;
   result << "Orbitron-Medium.ttf " << std::to_string(font_size * scale);
   //result << "Orbitron-Medium.ttf " << std::to_string(font_size * scale);
   return font_bin->auto_get(result.str());
}

ALLEGRO_FONT* Text::obtain_custom_font(std::string font_family, int font_size)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Text::obtain_custom_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Text::obtain_custom_font]: error: guard \"initialized\" not met");
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


