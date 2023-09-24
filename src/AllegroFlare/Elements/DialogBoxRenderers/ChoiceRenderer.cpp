

#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/ListBoxRenderer.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
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


ChoiceRenderer::ChoiceRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , choice_dialog_box(choice_dialog_box)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , text_padding_x(text_padding_x)
   , text_padding_y(text_padding_y)
{
}


ChoiceRenderer::~ChoiceRenderer()
{
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


void ChoiceRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::render]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::render: error: guard \"choice_dialog_box\" not met");
   }
   AllegroFlare::Elements::DialogBoxFrame(width, height).render();
   draw_prompt_text();
   draw_choices_with_cursor_and_current_selection();
   return;
}

void ChoiceRenderer::draw_prompt_text()
{
   int dialog_box_num_revealed_characters = 999;
   std::string text = obtain_choice_dialog_box_prompt();
   //float text_padding_x = 40.0f;
   //float text_padding_y = 25.0f;
   float text_box_max_width = width - (text_padding_x * 2);
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   float line_height = al_get_font_line_height(text_font);
   ALLEGRO_COLOR text_color = al_color_html("ffffff");
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");

   al_draw_multiline_text(
      text_font,
      text_color,
      text_padding_x,
      text_padding_y,
      text_box_max_width,
      line_height,
      ALLEGRO_ALIGN_LEFT,
      concat_text(text, dialog_box_num_revealed_characters).c_str()
   );
   return;
}

void ChoiceRenderer::draw_choices_with_cursor_and_current_selection()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::draw_choices_with_cursor_and_current_selection]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::draw_choices_with_cursor_and_current_selection: error: guard \"choice_dialog_box\" not met");
   }
   float left_indent = 80;
   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      font_bin,
      bitmap_bin,
      obtain_choice_dialog_box_option_labels()
   );
   list_box_renderer.set_height_to_fit_content();
   list_box_renderer.set_width_to_fit_content_or_max(width - left_indent*2);

   AllegroFlare::Placement2D choice_box_place{
      width - left_indent,
      20,
      list_box_renderer.get_width(),
      list_box_renderer.get_height()
   };
   choice_box_place.align = { 1.0, 1.0 };

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

std::string ChoiceRenderer::obtain_choice_dialog_box_prompt()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ChoiceRenderer::obtain_choice_dialog_box_prompt]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChoiceRenderer::obtain_choice_dialog_box_prompt: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_prompt();
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
   return choice_dialog_box->get_item_labels();
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

std::string ChoiceRenderer::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


