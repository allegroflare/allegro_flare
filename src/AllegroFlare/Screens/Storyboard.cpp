

#include <AllegroFlare/Screens/Storyboard.hpp>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Storyboard::Storyboard(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::vector<std::string> pages, std::string screen_identifier_to_switch_to_after_completing, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float top_padding, float left_padding, float right_padding, float line_height_multiplier, float line_height_padding, intptr_t current_page_num)
   : AllegroFlare::Screens::Base()
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , pages(pages)
   , screen_identifier_to_switch_to_after_completing(screen_identifier_to_switch_to_after_completing)
   , font_name(font_name)
   , font_size(font_size)
   , text_color(text_color)
   , top_padding(top_padding)
   , left_padding(left_padding)
   , right_padding(right_padding)
   , line_height_multiplier(line_height_multiplier)
   , line_height_padding(line_height_padding)
   , current_page_num(current_page_num)
{
}


Storyboard::~Storyboard()
{
}


void Storyboard::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Storyboard::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Storyboard::set_pages(std::vector<std::string> pages)
{
   this->pages = pages;
}


void Storyboard::set_screen_identifier_to_switch_to_after_completing(std::string screen_identifier_to_switch_to_after_completing)
{
   this->screen_identifier_to_switch_to_after_completing = screen_identifier_to_switch_to_after_completing;
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

   al_clear_to_color(AllegroFlare::Color::Black);

   if (current_page_num >= pages.size()) return;

   float box_width = 1920 - (left_padding + right_padding);

   al_draw_multiline_text(
         text_font,
         text_color, //AllegroFlare::Color(0xd0f2c5).to_al(),
         left_padding, //x_padding,
         top_padding, //y_padding,
         box_width,
         al_get_font_line_height(text_font)*line_height_multiplier + line_height_padding,
         0,
         pages[current_page_num].c_str()
      );
   return;
}

void Storyboard::reset()
{
   current_page_num = 0;
   return;
}

void Storyboard::on_activate()
{
   reset();
   return;
}

void Storyboard::primary_timer_func()
{
   render();
   return;
}

void Storyboard::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "key_down_func" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   current_page_num++;

   if (current_page_num >= pages.size())
      event_emitter->emit_switch_screen_event(screen_identifier_to_switch_to_after_completing);

   return;
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
   int font_size = -60;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}
} // namespace Screens
} // namespace AllegroFlare


