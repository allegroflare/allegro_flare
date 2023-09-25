

#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogButton.hpp>
#include <AllegroFlare/Elements/ListBoxRenderer.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxRenderers
{


ChoiceRenderer::ChoiceRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y, int num_revealed_characters, bool is_finished, bool page_is_finished, float page_finished_at, bool at_last_page, float age)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , choice_dialog_box(choice_dialog_box)
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
{
}


ChoiceRenderer::~ChoiceRenderer()
{
}


void ChoiceRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ChoiceRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void ChoiceRenderer::set_choice_dialog_box(AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box)
{
   this->choice_dialog_box = choice_dialog_box;
}


void ChoiceRenderer::set_width(float width)
{
   this->width = width;
}


void ChoiceRenderer::set_height(float height)
{
   this->height = height;
}


void ChoiceRenderer::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void ChoiceRenderer::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void ChoiceRenderer::set_text_padding_x(float text_padding_x)
{
   this->text_padding_x = text_padding_x;
}


void ChoiceRenderer::set_text_padding_y(float text_padding_y)
{
   this->text_padding_y = text_padding_y;
}


void ChoiceRenderer::set_num_revealed_characters(int num_revealed_characters)
{
   this->num_revealed_characters = num_revealed_characters;
}


void ChoiceRenderer::set_is_finished(bool is_finished)
{
   this->is_finished = is_finished;
}


void ChoiceRenderer::set_page_is_finished(bool page_is_finished)
{
   this->page_is_finished = page_is_finished;
}


void ChoiceRenderer::set_page_finished_at(float page_finished_at)
{
   this->page_finished_at = page_finished_at;
}


void ChoiceRenderer::set_at_last_page(bool at_last_page)
{
   this->at_last_page = at_last_page;
}


void ChoiceRenderer::set_age(float age)
{
   this->age = age;
}


AllegroFlare::FontBin* ChoiceRenderer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::BitmapBin* ChoiceRenderer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::Elements::DialogBoxes::Choice* ChoiceRenderer::get_choice_dialog_box() const
{
   return choice_dialog_box;
}


float ChoiceRenderer::get_width() const
{
   return width;
}


float ChoiceRenderer::get_height() const
{
   return height;
}


std::string ChoiceRenderer::get_font_name() const
{
   return font_name;
}


int ChoiceRenderer::get_font_size() const
{
   return font_size;
}


float ChoiceRenderer::get_text_padding_x() const
{
   return text_padding_x;
}


float ChoiceRenderer::get_text_padding_y() const
{
   return text_padding_y;
}


int ChoiceRenderer::get_num_revealed_characters() const
{
   return num_revealed_characters;
}


bool ChoiceRenderer::get_is_finished() const
{
   return is_finished;
}


bool ChoiceRenderer::get_page_is_finished() const
{
   return page_is_finished;
}


float ChoiceRenderer::get_page_finished_at() const
{
   return page_finished_at;
}


bool ChoiceRenderer::get_at_last_page() const
{
   return at_last_page;
}


float ChoiceRenderer::get_age() const
{
   return age;
}


void ChoiceRenderer::render_frame()
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

void ChoiceRenderer::render_text()
{
   draw_styled_revealed_text(width, obtain_choice_dialog_box_prompt(), num_revealed_characters);
   return;
}

void ChoiceRenderer::render()
{
   if (!(al_is_system_installed))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::render]: error: guard \"al_is_system_installed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::render: error: guard \"al_is_system_installed\" not met");
   }
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::render]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::render: error: guard \"choice_dialog_box\" not met");
   }
   render_frame();

   if (is_finished)
   {
      draw_special_state_empty_text(width, height);
   }
   else
   {
      render_text();
      draw_choices_with_cursor_and_current_selection();
   }
   return;
}

void ChoiceRenderer::draw_choices_with_cursor_and_current_selection()
{
   //float choice_box_reveal_delay = 0.6;
   if (!choice_dialog_box->get_showing_breakout_list_box()) return;

   float breakout_list_box_age = choice_dialog_box->infer_breakout_list_box_age();

   float left_indent = 80;
   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      font_bin,
      nullptr, // bitmap_bin,
      obtain_choice_dialog_box_option_labels()
   );
   // TODO: Interesting visual bug, when "set_width_to_fit..." is called after "set_height_to_fit..." then
   // there could be a miss-alignment of the content and its presentation. Investigate this case and see if you can
   // restore it
   list_box_renderer.set_width_to_fit_content_or_max(width - left_indent*2);
   list_box_renderer.set_height_to_fit_content();
   list_box_renderer.set_age(breakout_list_box_age);

   AllegroFlare::Placement2D choice_box_place{
      width - left_indent,
      20,
      list_box_renderer.get_width(),
      list_box_renderer.get_height()
   };
   choice_box_place.align = { 1.0, 1.0 };

   // Only show the cursor if the age is > 0.2
   bool showing_cursor = choice_dialog_box->get_showing_cursor();
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
   if (showing_cursor) selection_cursor_box.render();
   choice_box_place.restore_transform();
   return;
}

void ChoiceRenderer::draw_special_state_empty_text(float width, float height)
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

void ChoiceRenderer::draw_styled_revealed_text(float max_width, std::string text, int num_revealed_characters)
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

std::string ChoiceRenderer::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}

std::string ChoiceRenderer::obtain_choice_dialog_box_prompt()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_choice_dialog_box_prompt]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_choice_dialog_box_prompt: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_prompt_revealed_text();
}

std::vector<std::pair<std::string, std::string>> ChoiceRenderer::obtain_choice_dialog_box_options()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_choice_dialog_box_options]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_choice_dialog_box_options: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_options();
}

std::vector<std::string> ChoiceRenderer::obtain_choice_dialog_box_option_labels()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_choice_dialog_box_option_labels]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_choice_dialog_box_option_labels: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_options_labels();
}

int ChoiceRenderer::obtain_choice_dialog_box_cursor_position()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_choice_dialog_box_cursor_position]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_choice_dialog_box_cursor_position: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_cursor_position();
}

ALLEGRO_FONT* ChoiceRenderer::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_dialog_font: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_dialog_font: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_dialog_font: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


