

#include <AllegroFlare/Elements/DialogBoxRenderers/BasicRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxNameTag.hpp>
#include <AllegroFlare/Elements/DialogButton.hpp>
#include <AllegroFlare/Elements/ListBoxRenderer.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxRenderers
{


BasicRenderer::BasicRenderer(AllegroFlare::FontBin* font_bin, std::string current_page_text, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y, int num_revealed_characters, bool is_finished, bool page_is_finished, float page_finished_at, bool at_last_page, float age, bool showing_speaking_character_name, std::string speaking_character_name)
   : font_bin(font_bin)
   , current_page_text(current_page_text)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , text_padding_x(text_padding_x)
   , text_padding_y(text_padding_y)
   , num_revealed_characters(num_revealed_characters)
   , is_finished(is_finished)
   , page_is_finished(page_is_finished)
   , page_finished_at(page_finished_at)
   , at_last_page(at_last_page)
   , age(age)
   , showing_speaking_character_name(showing_speaking_character_name)
   , speaking_character_name(speaking_character_name)
{
}


BasicRenderer::~BasicRenderer()
{
}


void BasicRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void BasicRenderer::set_current_page_text(std::string current_page_text)
{
   this->current_page_text = current_page_text;
}


void BasicRenderer::set_width(float width)
{
   this->width = width;
}


void BasicRenderer::set_height(float height)
{
   this->height = height;
}


void BasicRenderer::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void BasicRenderer::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void BasicRenderer::set_text_padding_x(float text_padding_x)
{
   this->text_padding_x = text_padding_x;
}


void BasicRenderer::set_text_padding_y(float text_padding_y)
{
   this->text_padding_y = text_padding_y;
}


void BasicRenderer::set_num_revealed_characters(int num_revealed_characters)
{
   this->num_revealed_characters = num_revealed_characters;
}


void BasicRenderer::set_is_finished(bool is_finished)
{
   this->is_finished = is_finished;
}


void BasicRenderer::set_page_is_finished(bool page_is_finished)
{
   this->page_is_finished = page_is_finished;
}


void BasicRenderer::set_page_finished_at(float page_finished_at)
{
   this->page_finished_at = page_finished_at;
}


void BasicRenderer::set_at_last_page(bool at_last_page)
{
   this->at_last_page = at_last_page;
}


void BasicRenderer::set_age(float age)
{
   this->age = age;
}


void BasicRenderer::set_showing_speaking_character_name(bool showing_speaking_character_name)
{
   this->showing_speaking_character_name = showing_speaking_character_name;
}


void BasicRenderer::set_speaking_character_name(std::string speaking_character_name)
{
   this->speaking_character_name = speaking_character_name;
}


AllegroFlare::FontBin* BasicRenderer::get_font_bin() const
{
   return font_bin;
}


std::string BasicRenderer::get_current_page_text() const
{
   return current_page_text;
}


float BasicRenderer::get_width() const
{
   return width;
}


float BasicRenderer::get_height() const
{
   return height;
}


std::string BasicRenderer::get_font_name() const
{
   return font_name;
}


int BasicRenderer::get_font_size() const
{
   return font_size;
}


float BasicRenderer::get_text_padding_x() const
{
   return text_padding_x;
}


float BasicRenderer::get_text_padding_y() const
{
   return text_padding_y;
}


int BasicRenderer::get_num_revealed_characters() const
{
   return num_revealed_characters;
}


bool BasicRenderer::get_is_finished() const
{
   return is_finished;
}


bool BasicRenderer::get_page_is_finished() const
{
   return page_is_finished;
}


float BasicRenderer::get_page_finished_at() const
{
   return page_finished_at;
}


bool BasicRenderer::get_at_last_page() const
{
   return at_last_page;
}


float BasicRenderer::get_age() const
{
   return age;
}


bool BasicRenderer::get_showing_speaking_character_name() const
{
   return showing_speaking_character_name;
}


std::string BasicRenderer::get_speaking_character_name() const
{
   return speaking_character_name;
}


void BasicRenderer::render_frame()
{
   float normalized_age = std::max(std::min(1.0f, age), 0.0f);
   float curved_time = AllegroFlare::interpolator::double_fast_in(normalized_age);
   float inv_curved_time = 1.0 - curved_time;

   AllegroFlare::Placement2D frame_place = { width/2, height/2, width, height, };
   frame_place.position.y += 10 * inv_curved_time;
   frame_place.start_transform();
   AllegroFlare::Elements::DialogBoxFrame dialog_box_frame(width, height);
   dialog_box_frame.set_opacity(curved_time);
   dialog_box_frame.render();
   frame_place.restore_transform();
   return;
}

void BasicRenderer::render_text()
{
   draw_styled_revealed_text(width, current_page_text, num_revealed_characters);
   return;
}

void BasicRenderer::render_speaking_character_name_tag()
{
   draw_speaking_character_name();
   return;
}

void BasicRenderer::render_button()
{
   // draw the "next" or "finished" cursor (depending on context)
   if (page_is_finished)
   {
      AllegroFlare::Elements::DialogButton dialog_button(font_bin);
      dialog_button.set_started_at(page_finished_at);
      dialog_button.set_x(width - 160);
      dialog_button.set_y(height - 60);

      if (at_last_page) dialog_button.set_at_last_advance(true);

      dialog_button.render();
   }
   return;
}

void BasicRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (is_finished)
   {
      render_frame();
      draw_special_state_empty_text(width, height);
   }
   else
   {
      //if (showing_speaking_character_name && (!speaking_character_name.empty())) // TODO: Test this condition
      //{
         //render_speaking_character_name_tag();
      //}
      render_frame();
      render_text();
      render_button();
      if (showing_speaking_character_name && (!speaking_character_name.empty())) // TODO: Test this condition
      {
         render_speaking_character_name_tag();
      }
   }
   return;
}

void BasicRenderer::draw_choices_with_cursor_and_current_selection()
{
   float left_indent = 80;
   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      font_bin,
      nullptr, // bitmap_bin,
      obtain_choice_dialog_box_option_labels()
   );
   list_box_renderer.set_height_to_fit_content();
   list_box_renderer.set_width_to_fit_content_or_max_and_min(width - left_indent*2);

   AllegroFlare::Placement2D choice_box_place{
      width - left_indent,
      20,
      list_box_renderer.get_width(),
      list_box_renderer.get_height()
   };
   choice_box_place.align = AllegroFlare::Vec2D{ 1.0, 1.0 };

   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;

   list_box_renderer.set_cursor_position(
      obtain_choice_dialog_box_cursor_position()
   );

   // Init the cursor position to the current selection
   std::tuple<float, float, float, float> current_selection_dimensions =
      list_box_renderer.calculate_dimensions_for_list_item_at_position(
         obtain_choice_dialog_box_cursor_position()
      );
   float current_selection_x = std::get<0>(current_selection_dimensions);
   float current_selection_y = std::get<1>(current_selection_dimensions);
   float current_selection_width = std::get<2>(current_selection_dimensions);
   float current_selection_height = std::get<3>(current_selection_dimensions);
   selection_cursor_box.set_position(current_selection_x, current_selection_y);
   selection_cursor_box.set_size(current_selection_width, current_selection_height);

   choice_box_place.start_transform();
   list_box_renderer.render();
   selection_cursor_box.render();
   choice_box_place.restore_transform();
   return;
}

void BasicRenderer::draw_special_state_empty_text(float width, float height)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   ALLEGRO_COLOR text_color = al_color_html("303030");
   float line_height = al_get_font_line_height(text_font);
   std::string text = "[dialog finished]";
   al_draw_text(
      text_font,
      text_color,
      width * 0.5,
      height * 0.5 - line_height * 0.5,
      ALLEGRO_ALIGN_CENTER,
      text.c_str()
   );
   return;
}

void BasicRenderer::draw_speaking_character_name()
{
   int width = 220;
   int height = 46;

   AllegroFlare::Placement2D place(38, 0, width, height);
   place.align = AllegroFlare::Vec2D{ 0.0, 1.0 };
   //place.anchor = AllegroFlare::Vec2D{ 0.0, 8.0 };
   place.start_transform();
   AllegroFlare::Elements::DialogBoxNameTag name_tag(
      font_bin,
      speaking_character_name,
      width,
      height
   );
   name_tag.render();
   place.restore_transform();
   return;
}

void BasicRenderer::draw_styled_revealed_text(float max_width, std::string text, int num_revealed_characters)
{
   //float text_padding_x = 40.0f;
   //float text_padding_y = 30.0f;
   float text_box_max_width = max_width - (text_padding_x * 2);
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   float line_height = al_get_font_line_height(text_font);
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1, 1, 1, 1}; //al_color_name("skyblue");
   //int num_revealed_characters = obtain_dialog_box_num_revealed_characters();

   al_draw_multiline_text(
      text_font,
      text_color,
      text_padding_x,
      text_padding_y,
      text_box_max_width,
      line_height,
      ALLEGRO_ALIGN_LEFT,
      concat_text(text, num_revealed_characters).c_str()
   );
   return;
}

std::string BasicRenderer::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}

std::vector<std::string> BasicRenderer::obtain_choice_dialog_box_option_labels()
{
   // TODO: Replace these
   //return choice_dialog_box->get_item_labels();
   return { "Foobar", "Boobaz", "Flipflop" };
}

int BasicRenderer::obtain_choice_dialog_box_cursor_position()
{
   // TODO: Replace these
   //return choice_dialog_box->get_cursor_position();
   return 0;
}

ALLEGRO_FONT* BasicRenderer::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


