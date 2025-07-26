

#include <AllegroFlare/Elements/DialogBoxRenderers/InterparsableRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxNameTag.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Interparsable.hpp>
#include <AllegroFlare/Elements/DialogButton.hpp>
#include <AllegroFlare/Elements/ListBoxRenderer.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/TextFormatters/Basic.hpp>
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


InterparsableRenderer::InterparsableRenderer(AllegroFlare::FontBin* font_bin, std::string current_page_text_with_formatting, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y, int num_revealed_characters, bool is_finished, bool page_is_finished, float page_finished_at, bool at_last_page, float age, bool showing_speaking_character_name, std::string speaking_character_name)
   : font_bin(font_bin)
   , current_page_text_with_formatting(current_page_text_with_formatting)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , border_color(DEFAULT_BORDER_COLOR)
   , text_color(DEFAULT_TEXT_COLOR)
   , background_color(DEFAULT_BACKGROUND_COLOR)
   , label_color(DEFAULT_LABEL_COLOR)
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


InterparsableRenderer::~InterparsableRenderer()
{
}


void InterparsableRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void InterparsableRenderer::set_current_page_text_with_formatting(std::string current_page_text_with_formatting)
{
   this->current_page_text_with_formatting = current_page_text_with_formatting;
}


void InterparsableRenderer::set_width(float width)
{
   this->width = width;
}


void InterparsableRenderer::set_height(float height)
{
   this->height = height;
}


void InterparsableRenderer::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void InterparsableRenderer::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void InterparsableRenderer::set_border_color(ALLEGRO_COLOR border_color)
{
   this->border_color = border_color;
}


void InterparsableRenderer::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void InterparsableRenderer::set_background_color(ALLEGRO_COLOR background_color)
{
   this->background_color = background_color;
}


void InterparsableRenderer::set_label_color(ALLEGRO_COLOR label_color)
{
   this->label_color = label_color;
}


void InterparsableRenderer::set_text_padding_x(float text_padding_x)
{
   this->text_padding_x = text_padding_x;
}


void InterparsableRenderer::set_text_padding_y(float text_padding_y)
{
   this->text_padding_y = text_padding_y;
}


void InterparsableRenderer::set_num_revealed_characters(int num_revealed_characters)
{
   this->num_revealed_characters = num_revealed_characters;
}


void InterparsableRenderer::set_is_finished(bool is_finished)
{
   this->is_finished = is_finished;
}


void InterparsableRenderer::set_page_is_finished(bool page_is_finished)
{
   this->page_is_finished = page_is_finished;
}


void InterparsableRenderer::set_page_finished_at(float page_finished_at)
{
   this->page_finished_at = page_finished_at;
}


void InterparsableRenderer::set_at_last_page(bool at_last_page)
{
   this->at_last_page = at_last_page;
}


void InterparsableRenderer::set_age(float age)
{
   this->age = age;
}


void InterparsableRenderer::set_showing_speaking_character_name(bool showing_speaking_character_name)
{
   this->showing_speaking_character_name = showing_speaking_character_name;
}


void InterparsableRenderer::set_speaking_character_name(std::string speaking_character_name)
{
   this->speaking_character_name = speaking_character_name;
}


AllegroFlare::FontBin* InterparsableRenderer::get_font_bin() const
{
   return font_bin;
}


std::string InterparsableRenderer::get_current_page_text_with_formatting() const
{
   return current_page_text_with_formatting;
}


float InterparsableRenderer::get_width() const
{
   return width;
}


float InterparsableRenderer::get_height() const
{
   return height;
}


std::string InterparsableRenderer::get_font_name() const
{
   return font_name;
}


int InterparsableRenderer::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR InterparsableRenderer::get_border_color() const
{
   return border_color;
}


ALLEGRO_COLOR InterparsableRenderer::get_text_color() const
{
   return text_color;
}


ALLEGRO_COLOR InterparsableRenderer::get_background_color() const
{
   return background_color;
}


ALLEGRO_COLOR InterparsableRenderer::get_label_color() const
{
   return label_color;
}


float InterparsableRenderer::get_text_padding_x() const
{
   return text_padding_x;
}


float InterparsableRenderer::get_text_padding_y() const
{
   return text_padding_y;
}


int InterparsableRenderer::get_num_revealed_characters() const
{
   return num_revealed_characters;
}


bool InterparsableRenderer::get_is_finished() const
{
   return is_finished;
}


bool InterparsableRenderer::get_page_is_finished() const
{
   return page_is_finished;
}


float InterparsableRenderer::get_page_finished_at() const
{
   return page_finished_at;
}


bool InterparsableRenderer::get_at_last_page() const
{
   return at_last_page;
}


float InterparsableRenderer::get_age() const
{
   return age;
}


bool InterparsableRenderer::get_showing_speaking_character_name() const
{
   return showing_speaking_character_name;
}


std::string InterparsableRenderer::get_speaking_character_name() const
{
   return speaking_character_name;
}


void InterparsableRenderer::render_frame(float opacity)
{
   //float normalized_age = std::max(std::min(1.0f, age), 0.0f);
   //float curved_time = AllegroFlare::interpolator::double_fast_in(normalized_age);
   //float inv_curved_time = 1.0 - curved_time;

   //AllegroFlare::Placement2D frame_place = { width/2, height/2, width, height, };
   //frame_place.position.y += 10 * inv_curved_time;
   //frame_place.start_transform();
   AllegroFlare::Elements::DialogBoxFrame dialog_box_frame(width, height);
   dialog_box_frame.set_backfill_color(background_color);
   dialog_box_frame.set_border_color(border_color);
   dialog_box_frame.set_opacity(opacity);
   dialog_box_frame.render();
   //frame_place.restore_transform();
   return;
}

void InterparsableRenderer::render_text()
{
   //draw_styled_revealed_text_with_formatting(width, current_page_text_with_formatting, num_revealed_characters);


   // Render using the TextFormatter::Basic
   float text_box_max_width = width - (text_padding_x * 2);

   AllegroFlare::TextFormatters::Basic basic_text_formatter(font_bin);
   basic_text_formatter.set_text(current_page_text_with_formatting);
   basic_text_formatter.set_num_revealed_characters(num_revealed_characters);
   basic_text_formatter.set_max_text_box_width(text_box_max_width);
   basic_text_formatter.set_font_name(font_name);
   basic_text_formatter.set_font_size(font_size);
   basic_text_formatter.set_on_operational_chunk_func__default_text_color(text_color); // NOTE: A little sloppy
   basic_text_formatter.set_x(text_padding_x);
   basic_text_formatter.set_y(text_padding_y);
   basic_text_formatter.render();

   return;
}

void InterparsableRenderer::render_speaking_character_name_tag()
{
   draw_speaking_character_name();
   return;
}

void InterparsableRenderer::render_next_or_finished_button(float opacity)
{
   // draw the "next" or "finished" cursor (depending on context)
   if (!page_is_finished) return; // Do not show any cursor if the dialog page is still revealing

   bool using_labeled_button = false;
   if (using_labeled_button)
   {
      AllegroFlare::Elements::DialogButton dialog_button(font_bin);
      dialog_button.set_started_at(page_finished_at);
      dialog_button.set_x(width - 160);
      dialog_button.set_y(height - 60);

      if (at_last_page) dialog_button.set_at_last_advance(true);

      dialog_button.render();
   }
   else // Drawing a triangle cursor
   {
      float cursor_age = al_get_time() - page_finished_at;
      float c_width = 24;
      float c_height = 24;
      float speed = 5;
      float magnitude = 10;
      ALLEGRO_COLOR cursor_color = text_color;
      float y_offset = (std::sin(cursor_age * speed) * 0.5 + 0.5) * magnitude;
         //AllegroFlare::interpolator::double_fast_in(
            //(std::sin(cursor_age * speed) * 0.5 + 1.0)
         //) * magnitude;
         ;
      draw_rudimentary_triangle(width-80, height-52-y_offset, c_width, c_height, cursor_color, opacity);
   }
   return;
}

void InterparsableRenderer::draw_rudimentary_triangle(float x, float y, float w, float h, ALLEGRO_COLOR color, float opacity)
{
   float hh = h/2;
   float hw = w/2;
   color.r *= opacity;
   color.g *= opacity;
   color.b *= opacity;
   color.a *= opacity;
   al_draw_filled_triangle(x-hw, y-hh, x+hw, y-hh, x, y+hh, color);
   return;
}

void InterparsableRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float normalized_age = std::max(std::min(1.0f, age), 0.0f);
   float curved_time = AllegroFlare::interpolator::double_fast_in(normalized_age);
   float inv_curved_time = 1.0 - curved_time;
   AllegroFlare::Placement2D frame_place = { width/2, height/2, width, height, };
   frame_place.position.y += 10 * inv_curved_time;
   frame_place.start_transform();

   if (is_finished)
   {
      render_frame(curved_time);
      draw_special_state_empty_text(width, height);
   }
   else
   {
      if (showing_speaking_character_name && (!speaking_character_name.empty())) // TODO: Test this condition
      {
         render_speaking_character_name_tag();
      }
      render_frame(curved_time);
      render_text();
      render_next_or_finished_button();
   }

   frame_place.restore_transform();
   return;
}

void InterparsableRenderer::draw_choices_with_cursor_and_current_selection()
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

void InterparsableRenderer::draw_special_state_empty_text(float width, float height)
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

void InterparsableRenderer::draw_speaking_character_name()
{
   int width = 220;
   int height = 46;

   AllegroFlare::Placement2D place(30, 0, width, height);
   place.align = AllegroFlare::Vec2D{ 0.0, 1.0 };
   place.start_transform();
   AllegroFlare::Elements::DialogBoxNameTag name_tag(
      font_bin,
      speaking_character_name,
      width,
      height
   );
   name_tag.set_background_color(border_color);
   name_tag.set_text_color(label_color);
   name_tag.render();
   place.restore_transform();
   return;
}

std::vector<std::string> InterparsableRenderer::split_to_words(std::string text)
{
   std::string current_word;
   std::vector<std::string> result_words;
   for (auto &c : text)
   {
      if (isspace(c))
      {
         result_words.push_back(current_word);
         current_word.clear();
         continue; // What about consecutive spaces?
      }

      current_word.push_back(c);
   }
   return result_words;
}

void InterparsableRenderer::cb(int line_num, const char* line, int size, void* extra)
{
   return;
}

void InterparsableRenderer::draw_styled_revealed_text_with_formatting__deprecated(float max_width, std::string text_with_formatting, int num_revealed_characters)
{
   // NOTE: For now, this renderer has very limited formatting features. It will remove chunks that are non-text
   // chunks for now. Feel free to add more features if you feel it will be nice and useful.

   float text_box_max_width = max_width - (text_padding_x * 2);
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   float line_height = al_get_font_line_height(text_font);
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1, 1, 1, 1};

   std::string printable_text_only =
      AllegroFlare::Elements::DialogBoxes::Interparsable::collate_printable_text_only(text_with_formatting);

   al_draw_multiline_text(
      text_font,
      text_color,
      text_padding_x,
      text_padding_y,
      text_box_max_width,
      line_height,
      ALLEGRO_ALIGN_LEFT,
      concat_text(printable_text_only, num_revealed_characters).c_str()
   );

   return;
}

std::string InterparsableRenderer::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}

std::vector<std::string> InterparsableRenderer::obtain_choice_dialog_box_option_labels()
{
   // TODO: Replace these
   //return choice_dialog_box->get_item_labels();
   return { "Foobar", "Boobaz", "Flipflop" };
}

int InterparsableRenderer::obtain_choice_dialog_box_cursor_position()
{
   // TODO: Replace these
   //return choice_dialog_box->get_cursor_position();
   return 0;
}

ALLEGRO_FONT* InterparsableRenderer::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


