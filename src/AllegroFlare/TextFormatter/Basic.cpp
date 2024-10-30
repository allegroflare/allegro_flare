

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


std::string Basic::get_text() const
{
   return text;
}


bool Basic::line_callback(int line_num, const char* line, int size, void* extra)
{
   //CallbackData *data = static_cast<CallbackData *>(extra);
   int &character_index = *static_cast<int*>(extra);

   // Record where this line starts
   int line_start_index = character_index;
   std::cout << "Line " << line_num << " starts at character index " << line_start_index << "\n";

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
   int max_width = 300;
   //int max_width = 300;
   al_do_multiline_text(font, max_width, raw_text_source.c_str(), line_callback, &character_index);

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

   int num_revealed_characters = 9999;


   float x = 1920/2;
   float y = 1080/3;
   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};
   float max_text_box_width = 300;
   float line_height = al_get_font_line_height(font);



      std::string text_with_formatting = text;
      std::string printable_text_only = collate_printable_text_only(text_with_formatting);


   //al_draw_rounded_rectangle(
      //x-h_text_width - padding.x,
      //y-h_text_height - padding.y,
      //x+h_text_width + padding.x,
      //y+h_text_height + padding.y,
      //8.0f,
      //8.0f,
      //ALLEGRO_COLOR{1, 1, 1, 1},
      //8.0f
   //);

   al_draw_multiline_text(
         font,
         //ALLEGRO_COLOR{1, 1, 1, 1},
         ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3},
         x,
         y,
         max_text_box_width,
         line_height,
         ALLEGRO_ALIGN_LEFT,
         printable_text_only.c_str()
      );


   // Draw per-glyph
   //bool draw_per_glyph = false; // TODO: Uncomment this and continue its development
   bool draw_per_glyph = true;
   if (draw_per_glyph)
   {
      //std::set<int> line_break_indices = calculate_line_breaks(asdf);


      //std::string text_with_formatting = text;
      //std::string printable_text_only = collate_printable_text_only(text_with_formatting);

         //AllegroFlare::Elements::DialogBoxes::Interparsable::collate_printable_text_only(text_with_formatting);

      std::set<int> line_break_indices = calculate_line_breaks(printable_text_only);

      // TODO: Add line breaks
      std::string captured_operational_chunk;
      //std::string current_word_buffer;
      //std::vector<std::string> words = split_to_words(printable_text_only);

      int state = 0;
      int in_paren_count = 0;
      int num_characters_rendered = 0;
      al_hold_bitmap_drawing(true);
      float glyph_x = 0;
      float glyph_y = 0;
      ALLEGRO_COLOR default_color = ALLEGRO_COLOR{1, 1, 1, 1};
      ALLEGRO_COLOR emphasis_color = ALLEGRO_COLOR{0.95, 0.57, 0.2, 1};
      ALLEGRO_COLOR text_color = default_color;
      int word_index = 0;

      //for (auto &c : text_with_formatting)
      //for (auto &c : text_with_formatting.begin())
      //for (auto it=text_with_formatting.begin(); it!=text_with_formatting.end(); it++)
      //for (int i=0; i<text_with_formatting.size(); i++)
      //{
         //auto &c = (*it);
         //std::cout << (*it) << "   " << it << std::endl;
         //auto &c = *(text_with_formatting.begin() + i);
         //auto &c = text_with_formatting[i];
         //const char *char_mem_pos = &text_with_formatting.data()[0] + i;
         //std::cout << "# processing: \"" << c << "\"" << std::endl;
         //return;
      //}
         //return;
      //std::cout << "-----------------------------------------------------" << std::endl;

      for (int i=0; i<text_with_formatting.size(); i++)
      {
         //auto &c = text_with_formatting[i];
         //int i=0;
         auto &c = text_with_formatting[i];

         // Count parens
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
               if (captured_operational_chunk == "em") text_color = emphasis_color;
               else if (captured_operational_chunk == "/em") text_color = default_color;
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


         bool should_break_here = false;
         //.find(x) != s.end()
         // TODO: This logic here
         //.find(x) != s.end()
         if (line_break_indices.find(num_characters_rendered) != line_break_indices.end())
         //if (line_break_indices.find(i) != line_break_indices.end())
         {
            should_break_here = true;
         }


         if (should_break_here)
         {
            glyph_x = 0;
            glyph_y += line_height;
            //num_characters_rendered++;
            //continue;
         }

         al_draw_glyph(
            font,
            text_color, //ALLEGRO_COLOR{0.5, 0.8, 0.8, 0.8},
            x+glyph_x, // + text_padding_x
            y+glyph_y, // + text_padding_y,
            c
         );
            //const ALLEGRO_FONT *f, ALLEGRO_COLOR color, float x, float y,
            //int codepoint)
         float width = al_get_glyph_advance(font, c, ALLEGRO_NO_KERNING);
         glyph_x += width;
         num_characters_rendered++;

         if (num_characters_rendered >= num_revealed_characters) break;
      }
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
   return font_bin->auto_get("Inter-Medium.ttf -52");
}


} // namespace TextFormatter
} // namespace AllegroFlare


