

#include <AllegroFlare/TextFormatter/Basic.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TextFormatter
{


std::set<int> Basic::_line_break_indices = {};


Basic::Basic(AllegroFlare::FontBin* font_bin, std::string text)
   : font_bin(font_bin)
   , text(text)
   , font_name("Inter-Medium.ttf")
   , font_size(24)
   , x(0)
   , y(0)
   , max_text_box_width(450)
   , num_revealed_characters(9999)
   , draw_unrendered_pretext(false)
   , on_operational_chunk_func(AllegroFlare::TextFormatter::Basic::default_on_operational_chunk_func)
   , on_operational_chunk_func_user_data(nullptr)
   , render_state__text_color(ALLEGRO_COLOR{1, 1, 1, 1})
{
}


Basic::~Basic()
{
}


void Basic::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Basic::set_text(std::string text)
{
   this->text = text;
}


void Basic::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void Basic::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void Basic::set_x(float x)
{
   this->x = x;
}


void Basic::set_y(float y)
{
   this->y = y;
}


void Basic::set_max_text_box_width(float max_text_box_width)
{
   this->max_text_box_width = max_text_box_width;
}


void Basic::set_num_revealed_characters(int num_revealed_characters)
{
   this->num_revealed_characters = num_revealed_characters;
}


void Basic::set_draw_unrendered_pretext(bool draw_unrendered_pretext)
{
   this->draw_unrendered_pretext = draw_unrendered_pretext;
}


void Basic::set_on_operational_chunk_func(std::function<void(AllegroFlare::TextFormatter::Basic*, std::string, void*)> on_operational_chunk_func)
{
   this->on_operational_chunk_func = on_operational_chunk_func;
}


void Basic::set_on_operational_chunk_func_user_data(void* on_operational_chunk_func_user_data)
{
   this->on_operational_chunk_func_user_data = on_operational_chunk_func_user_data;
}


void Basic::set_render_state__text_color(ALLEGRO_COLOR render_state__text_color)
{
   this->render_state__text_color = render_state__text_color;
}


std::string Basic::get_text() const
{
   return text;
}


std::string Basic::get_font_name() const
{
   return font_name;
}


int Basic::get_font_size() const
{
   return font_size;
}


float Basic::get_x() const
{
   return x;
}


float Basic::get_y() const
{
   return y;
}


float Basic::get_max_text_box_width() const
{
   return max_text_box_width;
}


int Basic::get_num_revealed_characters() const
{
   return num_revealed_characters;
}


bool Basic::get_draw_unrendered_pretext() const
{
   return draw_unrendered_pretext;
}


std::function<void(AllegroFlare::TextFormatter::Basic*, std::string, void*)> Basic::get_on_operational_chunk_func() const
{
   return on_operational_chunk_func;
}


void* Basic::get_on_operational_chunk_func_user_data() const
{
   return on_operational_chunk_func_user_data;
}


ALLEGRO_COLOR Basic::get_render_state__text_color() const
{
   return render_state__text_color;
}


bool Basic::line_callback(int line_num, const char* line, int size, void* extra)
{
   //CallbackData *data = static_cast<CallbackData *>(extra);
   int &character_index = *static_cast<int*>(extra);

   // Record where this line starts
   int line_start_index = character_index;
   //std::cout << "Line " << line_num << " starts at character index " << line_start_index << "\n";

   // Advance the character index by the size of this line and an assumed newline character
   character_index += size + 1; // +1 for the line break
   _line_break_indices.insert(character_index);

   return true; // Continue to next line
}

std::set<int> Basic::calculate_line_breaks(std::string raw_text_source)
{
   //std::set<int> result;
   _line_break_indices = {};

   //CallbackData callback_data{0}; // Initialize character_index to 0
   int character_index = 0;

   ALLEGRO_FONT *font = obtain_font();
   //int max_width = 300;
   //int max_width = 300;
   al_do_multiline_text(font, max_text_box_width, raw_text_source.c_str(), line_callback, &character_index);

   return _line_break_indices;
}

std::vector<std::pair<bool, std::string>> Basic::parse_into_chunks(std::string raw_text_source)
{
   std::vector<std::pair<bool, std::string>> parsed_chunks;
   bool in_parens = false;
   std::string current_chunk;
   int open_paren_count = 0;

   for (size_t i=0; i<raw_text_source.size(); ++i)
   {
      char ch = raw_text_source[i];

      if (ch == '(')
      {
         if (in_parens)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks",
               "Nested parentheses were found in the text \"" + raw_text_source + "\". Nested parens are not "
                  "supported."
            );
         }

         // If entering parentheses, save current chunk if it exists
         if (!current_chunk.empty())
         {
            parsed_chunks.emplace_back(in_parens, current_chunk);
            current_chunk.clear();
         }
         in_parens = true;
         open_paren_count++;
      }
      else if (ch == ')')
      {
         if (!in_parens)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks",
               "There was an open paren that does not have a matching closing paren in the text \""
                  + raw_text_source + "\""
            );
         }

         // If leaving parentheses, save current chunk
         if (!current_chunk.empty())
         {
            parsed_chunks.emplace_back(in_parens, current_chunk);
            current_chunk.clear();
         }
         in_parens = false;
         open_paren_count--;
      }
      else
      {
         // Add character to the current chunk
         current_chunk += ch;
      }
   }

   // Add any remaining chunk
   if (!current_chunk.empty())
   {
      parsed_chunks.emplace_back(in_parens, current_chunk);
   }

   // Check for unmatched opening parenthesis
   if (open_paren_count != 0)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks",
         "Unmatched opening parenthesis found in text \"" + raw_text_source + "\""
      );
   }

   return parsed_chunks;
}

void Basic::default_on_operational_chunk_func(AllegroFlare::TextFormatter::Basic* text_formatter, std::string text, void* user_data)
{
   if (!(text_formatter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TextFormatter::Basic::default_on_operational_chunk_func]: error: guard \"text_formatter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TextFormatter::Basic::default_on_operational_chunk_func]: error: guard \"text_formatter\" not met");
   }
   auto &formatter = *text_formatter;

   ALLEGRO_COLOR default_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR emphasis_color = ALLEGRO_COLOR{0.95, 0.57, 0.2, 1};
   // Where is render state stored?
   //ALLEGRO_COLOR default_color = ALLEGRO_COLOR{1, 1, 1, 1};
   //ALLEGRO_COLOR emphasis_color = ALLEGRO_COLOR{0.95, 0.57, 0.2, 1};

   //auto &formatter = *text_formatter;
   if (text == "em") formatter.render_state__text_color = emphasis_color;
   else if (text == "/em") formatter.render_state__text_color = default_color;
   return;
}

std::string Basic::collate_printable_text_only(std::string raw_text_source)
{
   std::vector<std::pair<bool, std::string>> chunks = parse_into_chunks(raw_text_source);
   std::stringstream result;
   for (auto &chunk : chunks)
   {
      bool is_printable_text = !chunk.first;
      if (is_printable_text) result << chunk.second;
   }
   return result.str();
}

void Basic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TextFormatter::Basic::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TextFormatter::Basic::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TextFormatter::Basic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TextFormatter::Basic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TextFormatter::Basic::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TextFormatter::Basic::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TextFormatter::Basic::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TextFormatter::Basic::render]: error: guard \"font_bin\" not met");
   }
   ALLEGRO_FONT *font = obtain_font();
   float line_height = al_get_font_line_height(font);
   std::string text_with_formatting = text;
   std::string printable_text_only = collate_printable_text_only(text_with_formatting);

   al_hold_bitmap_drawing(true);

   if (draw_unrendered_pretext)
   {
      // Just draw the text raw
      al_draw_multiline_text(
            font,
            //ALLEGRO_COLOR{1, 1, 1, 1},
            ALLEGRO_COLOR{0.1, 0.102, 0.11, 0.11},
            x,
            y,
            max_text_box_width,
            line_height,
            ALLEGRO_ALIGN_LEFT,
            printable_text_only.c_str()
         );
   }

   // Draw the text line-by-line
   std::set<int> line_break_indices = calculate_line_breaks(printable_text_only);
   std::string captured_operational_chunk;
   int in_paren_count = 0;
   int num_characters_rendered = 0;
   float glyph_x = 0;
   float glyph_y = 0;
   ALLEGRO_COLOR default_color = ALLEGRO_COLOR{1, 1, 1, 1};
   //ALLEGRO_COLOR emphasis_color = ALLEGRO_COLOR{0.95, 0.57, 0.2, 1};
   render_state__text_color = default_color;
   int word_index = 0;

   for (int i=0; i<text_with_formatting.size(); i++)
   {
      auto &c = text_with_formatting[i];

      // Check for parens
      if (c == '(')
      {
         in_paren_count++;
         continue;
      }
      else if (c == ')')
      {
         in_paren_count--;
         {
            // Process captured_operational_chunk
            //
            if (!on_operational_chunk_func)
            {
               // TODO: Throw
            }
            else
            {
               on_operational_chunk_func(this, captured_operational_chunk, on_operational_chunk_func_user_data);
            }
            //if (captured_operational_chunk == "em") render_state__text_color = emphasis_color;
            //else if (captured_operational_chunk == "/em") render_state__text_color = default_color;
         }
         captured_operational_chunk.clear();
         continue;
      }
      if (in_paren_count < 0)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer",
            "Mismatching paren ')' found."
         );
      }
      if (in_paren_count > 0)
      {
         captured_operational_chunk.push_back(c);
         continue;
      }

      // Rendering text

      // Check for line breaks
      bool should_break_here = false;
      if (line_break_indices.find(num_characters_rendered) != line_break_indices.end()) should_break_here = true;
      if (should_break_here)
      {
         glyph_x = 0;
         glyph_y += line_height;
      }

      // Draw the glyph
      al_draw_glyph(
         font,
         render_state__text_color,
         x+glyph_x,
         y+glyph_y,
         c
      );

      float width = al_get_glyph_advance(font, c, ALLEGRO_NO_KERNING);
      glyph_x += width;
      num_characters_rendered++;

      if (num_characters_rendered >= num_revealed_characters) break;
   }

   al_hold_bitmap_drawing(false);


   return;
}

ALLEGRO_FONT* Basic::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TextFormatter::Basic::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TextFormatter::Basic::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get(font_name + " " + std::to_string(font_size));
}


} // namespace TextFormatter
} // namespace AllegroFlare


