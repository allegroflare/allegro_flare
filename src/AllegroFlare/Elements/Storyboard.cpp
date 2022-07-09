

#include <AllegroFlare/Elements/Storyboard.hpp>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


Storyboard::Storyboard(AllegroFlare::FontBin* font_bin, std::vector<std::string> pages, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float top_padding, float left_padding, float right_padding, float line_height_multiplier, float line_height_padding, intptr_t current_page_num)
   : AllegroFlare::Screens::Base()
   , font_bin(font_bin)
   , pages(pages)
   , font_name(font_name)
   , font_size(font_size)
   , text_color(text_color)
   , top_padding(top_padding)
   , left_padding(left_padding)
   , right_padding(right_padding)
   , line_height_multiplier(line_height_multiplier)
   , line_height_padding(line_height_padding)
   , current_page_num(current_page_num)
   , revealed_characters_count(0)
   , can_advance_to_next(false)
   , finished(false)
{
}


Storyboard::~Storyboard()
{
}


void Storyboard::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Storyboard::set_pages(std::vector<std::string> pages)
{
   this->pages = pages;
}


void Storyboard::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void Storyboard::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void Storyboard::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void Storyboard::set_top_padding(float top_padding)
{
   this->top_padding = top_padding;
}


void Storyboard::set_left_padding(float left_padding)
{
   this->left_padding = left_padding;
}


void Storyboard::set_right_padding(float right_padding)
{
   this->right_padding = right_padding;
}


void Storyboard::set_line_height_multiplier(float line_height_multiplier)
{
   this->line_height_multiplier = line_height_multiplier;
}


void Storyboard::set_line_height_padding(float line_height_padding)
{
   this->line_height_padding = line_height_padding;
}


std::string Storyboard::get_font_name()
{
   return font_name;
}


int Storyboard::get_font_size()
{
   return font_size;
}


ALLEGRO_COLOR Storyboard::get_text_color()
{
   return text_color;
}


float Storyboard::get_top_padding()
{
   return top_padding;
}


float Storyboard::get_left_padding()
{
   return left_padding;
}


float Storyboard::get_right_padding()
{
   return right_padding;
}


float Storyboard::get_line_height_multiplier()
{
   return line_height_multiplier;
}


float Storyboard::get_line_height_padding()
{
   return line_height_padding;
}


intptr_t Storyboard::get_current_page_num()
{
   return current_page_num;
}


int Storyboard::get_revealed_characters_count()
{
   return revealed_characters_count;
}


bool Storyboard::get_can_advance_to_next()
{
   return can_advance_to_next;
}


bool Storyboard::get_finished()
{
   return finished;
}


void Storyboard::update()
{
   revealed_characters_count++;
   if (revealed_characters_count >= current_page_text().size())
   {
      can_advance_to_next = true;
   }
   return;
}

void Storyboard::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT *text_font = obtain_font();

   //al_clear_to_color(AllegroFlare::Color::Black);

   std::string text = revealed_page_text();
   if (!text.empty())
   {
      float box_width = 1920 - (left_padding + right_padding);
      al_draw_multiline_text(
            text_font,
            text_color, //AllegroFlare::Color(0xd0f2c5).to_al(),
            left_padding, //x_padding,
            top_padding, //y_padding,
            box_width,
            al_get_font_line_height(text_font)*line_height_multiplier + line_height_padding,
            0,
            text.c_str() //pages[current_page_num].c_str()
         );
   }

   if (can_advance_to_next) render_next_button();

   return;
}

std::string Storyboard::current_page_text()
{
   if (current_page_num >= pages.size()) return "";
   return pages[current_page_num].c_str();
}

std::string Storyboard::revealed_page_text()
{
   return current_page_text().substr(0, revealed_characters_count);
}

void Storyboard::reveal_all_characters()
{
   revealed_characters_count = current_page_text().size();
}

void Storyboard::render_next_button()
{
   float x = 1920-400;
   float y = 1080-300;
   ALLEGRO_FONT *next_button_font = obtain_next_button_font();
   std::string text = "NEXT >";
   float text_width = al_get_text_width(next_button_font, text.c_str());
   float text_height = al_get_font_line_height(next_button_font);
   ALLEGRO_COLOR button_color = AllegroFlare::Color::PaleGreen;
   float thickness = 4.0f;
   float roundness = thickness * 1.5;
   float padding_x = 32.0f;
   float padding_y = 12.0f;

   AllegroFlare::Placement2D button_place;
   button_place.position.x = x;
   button_place.position.y = y;

   button_place.start_transform();

   // draw the cursor outline
   al_draw_rounded_rectangle(
      -padding_x,
      -padding_y,
      text_width+padding_x,
      text_height+padding_y,
      roundness,
      roundness,
      button_color,
      thickness
   );

   // draw the text
   al_draw_text(next_button_font, button_color, text_width/2, 0, ALLEGRO_ALIGN_CENTER, text.c_str());

   button_place.restore_transform();

   return;
}

void Storyboard::reset()
{
   current_page_num = 0;
   revealed_characters_count = 0;
   finished = false;
   can_advance_to_next = false;
   return;
}

bool Storyboard::permit_advancing_page()
{
   if (finished) return false;
   can_advance_to_next = true;
   return true;
}

bool Storyboard::advance()
{
   if (finished) return false;

   if (!can_advance_to_next)
   {
      can_advance_to_next = true;
      reveal_all_characters();
      return true;
   }
   else
   {
      return advance_page();
   }

   return false;
}

bool Storyboard::advance_page()
{
   if (finished) return false;
   if (!can_advance_to_next) return false;

   current_page_num++;
   revealed_characters_count = 0;
   can_advance_to_next = false;

   if (current_page_num >= pages.size())
   {
      finished = true;
   }
   return !finished;
}

bool Storyboard::all_characters_are_revealed()
{
   return revealed_characters_count >= current_page_text().size();
}

bool Storyboard::infer_at_last_page()
{
   return (current_page_num == (pages.size()-1));
}

bool Storyboard::infer_at_or_past_last_page()
{
   return (current_page_num >= (pages.size()-1));
}

ALLEGRO_FONT* Storyboard::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* Storyboard::obtain_next_button_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "obtain_next_button_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size+20;
   return font_bin->auto_get(composite_font_str.str());
}
} // namespace Elements
} // namespace AllegroFlare


