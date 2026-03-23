

#include <AllegroFlare/Elements/DialogBoxRenderers/InterparsableWithOptionsRenderer.hpp>

#include <AllegroFlare/ColorKit.hpp>
#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxNameTag.hpp>
#include <AllegroFlare/Elements/DialogButton.hpp>
#include <AllegroFlare/Elements/ListBoxRenderer.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/TextFormatters/Basic.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxRenderers
{


InterparsableWithOptionsRenderer::InterparsableWithOptionsRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions* choice_dialog_box, AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y, int num_revealed_characters, bool is_finished, bool page_is_finished, float page_finished_at, bool at_last_page, float age, bool showing_speaking_character_name, std::string speaking_character_name)
   : font_bin(font_bin)
   , choice_dialog_box(choice_dialog_box)
   , selection_cursor_box(selection_cursor_box)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , border_color(DEFAULT_BORDER_COLOR)
   , text_color(DEFAULT_TEXT_COLOR)
   , background_color(DEFAULT_BACKGROUND_COLOR)
   , label_color(DEFAULT_LABEL_COLOR)
   , text_emphasis_color(DEFAULT_TEXT_EMPHASIS_COLOR)
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
   , hide_name_tag_if_empty(true)
{
}


InterparsableWithOptionsRenderer::~InterparsableWithOptionsRenderer()
{
}


void InterparsableWithOptionsRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void InterparsableWithOptionsRenderer::set_choice_dialog_box(AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions* choice_dialog_box)
{
   this->choice_dialog_box = choice_dialog_box;
}


void InterparsableWithOptionsRenderer::set_selection_cursor_box(AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box)
{
   this->selection_cursor_box = selection_cursor_box;
}


void InterparsableWithOptionsRenderer::set_width(float width)
{
   this->width = width;
}


void InterparsableWithOptionsRenderer::set_height(float height)
{
   this->height = height;
}


void InterparsableWithOptionsRenderer::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void InterparsableWithOptionsRenderer::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void InterparsableWithOptionsRenderer::set_border_color(ALLEGRO_COLOR border_color)
{
   this->border_color = border_color;
}


void InterparsableWithOptionsRenderer::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void InterparsableWithOptionsRenderer::set_background_color(ALLEGRO_COLOR background_color)
{
   this->background_color = background_color;
}


void InterparsableWithOptionsRenderer::set_label_color(ALLEGRO_COLOR label_color)
{
   this->label_color = label_color;
}


void InterparsableWithOptionsRenderer::set_text_emphasis_color(ALLEGRO_COLOR text_emphasis_color)
{
   this->text_emphasis_color = text_emphasis_color;
}


void InterparsableWithOptionsRenderer::set_text_padding_x(float text_padding_x)
{
   this->text_padding_x = text_padding_x;
}


void InterparsableWithOptionsRenderer::set_text_padding_y(float text_padding_y)
{
   this->text_padding_y = text_padding_y;
}


void InterparsableWithOptionsRenderer::set_num_revealed_characters(int num_revealed_characters)
{
   this->num_revealed_characters = num_revealed_characters;
}


void InterparsableWithOptionsRenderer::set_is_finished(bool is_finished)
{
   this->is_finished = is_finished;
}


void InterparsableWithOptionsRenderer::set_page_is_finished(bool page_is_finished)
{
   this->page_is_finished = page_is_finished;
}


void InterparsableWithOptionsRenderer::set_page_finished_at(float page_finished_at)
{
   this->page_finished_at = page_finished_at;
}


void InterparsableWithOptionsRenderer::set_at_last_page(bool at_last_page)
{
   this->at_last_page = at_last_page;
}


void InterparsableWithOptionsRenderer::set_age(float age)
{
   this->age = age;
}


void InterparsableWithOptionsRenderer::set_showing_speaking_character_name(bool showing_speaking_character_name)
{
   this->showing_speaking_character_name = showing_speaking_character_name;
}


void InterparsableWithOptionsRenderer::set_speaking_character_name(std::string speaking_character_name)
{
   this->speaking_character_name = speaking_character_name;
}


void InterparsableWithOptionsRenderer::set_hide_name_tag_if_empty(bool hide_name_tag_if_empty)
{
   this->hide_name_tag_if_empty = hide_name_tag_if_empty;
}


AllegroFlare::FontBin* InterparsableWithOptionsRenderer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions* InterparsableWithOptionsRenderer::get_choice_dialog_box() const
{
   return choice_dialog_box;
}


AllegroFlare::Elements::SelectionCursorBox* InterparsableWithOptionsRenderer::get_selection_cursor_box() const
{
   return selection_cursor_box;
}


float InterparsableWithOptionsRenderer::get_width() const
{
   return width;
}


float InterparsableWithOptionsRenderer::get_height() const
{
   return height;
}


std::string InterparsableWithOptionsRenderer::get_font_name() const
{
   return font_name;
}


int InterparsableWithOptionsRenderer::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR InterparsableWithOptionsRenderer::get_border_color() const
{
   return border_color;
}


ALLEGRO_COLOR InterparsableWithOptionsRenderer::get_text_color() const
{
   return text_color;
}


ALLEGRO_COLOR InterparsableWithOptionsRenderer::get_background_color() const
{
   return background_color;
}


ALLEGRO_COLOR InterparsableWithOptionsRenderer::get_label_color() const
{
   return label_color;
}


ALLEGRO_COLOR InterparsableWithOptionsRenderer::get_text_emphasis_color() const
{
   return text_emphasis_color;
}


float InterparsableWithOptionsRenderer::get_text_padding_x() const
{
   return text_padding_x;
}


float InterparsableWithOptionsRenderer::get_text_padding_y() const
{
   return text_padding_y;
}


int InterparsableWithOptionsRenderer::get_num_revealed_characters() const
{
   return num_revealed_characters;
}


bool InterparsableWithOptionsRenderer::get_is_finished() const
{
   return is_finished;
}


bool InterparsableWithOptionsRenderer::get_page_is_finished() const
{
   return page_is_finished;
}


float InterparsableWithOptionsRenderer::get_page_finished_at() const
{
   return page_finished_at;
}


bool InterparsableWithOptionsRenderer::get_at_last_page() const
{
   return at_last_page;
}


float InterparsableWithOptionsRenderer::get_age() const
{
   return age;
}


bool InterparsableWithOptionsRenderer::get_showing_speaking_character_name() const
{
   return showing_speaking_character_name;
}


std::string InterparsableWithOptionsRenderer::get_speaking_character_name() const
{
   return speaking_character_name;
}


bool InterparsableWithOptionsRenderer::get_hide_name_tag_if_empty() const
{
   return hide_name_tag_if_empty;
}


void InterparsableWithOptionsRenderer::deps(int _ignore)
{
   return;
}

void InterparsableWithOptionsRenderer::render_frame(float opacity)
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

void InterparsableWithOptionsRenderer::render_text()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render_text]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render_text]: error: guard \"choice_dialog_box\" not met");
   }
   //draw_styled_revealed_text_with_formatting(width, current_page_text_with_formatting, num_revealed_characters);


   // Render using the TextFormatter::Basic
   float text_box_max_width = width - (text_padding_x * 2);

   AllegroFlare::TextFormatters::Basic basic_text_formatter(font_bin);
   //basic_text_formatter.set_text(current_page_text_with_formatting);
   basic_text_formatter.set_text(choice_dialog_box->get_current_page_text_with_formatting());
            //current_char_index++;
            //num_revealed_printable_characters++;
   //basic_text_formatter.set_num_revealed_characters(num_revealed_characters); // HERE?
   basic_text_formatter.set_num_revealed_characters(choice_dialog_box->get_num_revealed_printable_characters());
   basic_text_formatter.set_max_text_box_width(text_box_max_width);
   basic_text_formatter.set_font_name(font_name);
   basic_text_formatter.set_font_size(font_size);
   basic_text_formatter.set_on_operational_chunk_func__default_text_color(text_color); // NOTE: A little sloppy
   basic_text_formatter.set_on_operational_chunk_func__default_text_emphasis_color(text_emphasis_color);

   basic_text_formatter.set_x(text_padding_x);
   basic_text_formatter.set_y(text_padding_y); // TODO: Include a "y_offset_nudge"
   basic_text_formatter.set_line_height_strategy_to_natural_line_height_with_offset(5.0f); // TODO: Consider this as
                                                                                           // variable
   basic_text_formatter.render();

   return;
}

void InterparsableWithOptionsRenderer::render_speaking_character_name_tag()
{
   draw_speaking_character_name();
   return;
}

void InterparsableWithOptionsRenderer::render_next_or_finished_button(float opacity)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render_next_or_finished_button]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render_next_or_finished_button]: error: guard \"font_bin\" not met");
   }
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
      float c_width = 24+6;
      float c_height = 24-6;
      float speed = 6;
      float magnitude = 10;
      ALLEGRO_COLOR cursor_color = text_color;
      float y_offset = (std::sin(cursor_age * speed) * 0.5 + 0.5) * magnitude;
         //AllegroFlare::interpolator::double_fast_in(
            //(std::sin(cursor_age * speed) * 0.5 + 1.0)
         //) * magnitude;
         ;
      draw_rudimentary_triangle(width-80, height-50-y_offset, c_width, c_height, cursor_color, opacity);
   }
   return;
}

void InterparsableWithOptionsRenderer::draw_rudimentary_triangle(float x, float y, float w, float h, ALLEGRO_COLOR color, float opacity)
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

void InterparsableWithOptionsRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render]: error: guard \"choice_dialog_box\" not met");
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
      //if (showing_speaking_character_name && (!speaking_character_name.empty())) // TODO: Test this condition
      //{
         render_speaking_character_name_tag();
      //}
      render_frame(curved_time);
      render_text();
      render_next_or_finished_button();
      draw_choices_with_cursor_and_current_selection(); // ??
   }

   frame_place.restore_transform();
   return;
}

void InterparsableWithOptionsRenderer::helper__set_selection_cursor_box_dimensions_to(AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box, std::tuple<float, float, float, float> dimensions)
{
   if (!(selection_cursor_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::helper__set_selection_cursor_box_dimensions_to]: error: guard \"selection_cursor_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::helper__set_selection_cursor_box_dimensions_to]: error: guard \"selection_cursor_box\" not met");
   }
   float &x = std::get<0>(dimensions);
   float &y = std::get<1>(dimensions);
   float &width = std::get<2>(dimensions);
   float &height = std::get<3>(dimensions);
   selection_cursor_box->set_position(x, y);
   selection_cursor_box->set_size(width, height);
   return;
}

float InterparsableWithOptionsRenderer::get_left_indent()
{
   return 80;
}

AllegroFlare::Elements::ListBoxRenderer InterparsableWithOptionsRenderer::build_list_box_renderer()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::build_list_box_renderer]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::build_list_box_renderer]: error: guard \"choice_dialog_box\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::build_list_box_renderer]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::build_list_box_renderer]: error: guard \"font_bin\" not met");
   }
   // Design some custom colors for the breakout box
   ALLEGRO_COLOR selection_frame_color = AllegroFlare::Elements::ListBoxRenderer::DEFAULT_SELECTION_COLOR;
   ALLEGRO_COLOR frame_backfill_color = AllegroFlare::ColorKit::mix(
         background_color, //AllegroFlare::Elements::DialogBoxFrame::DEFAULT_BACKFILL_COLOR,
         selection_frame_color,
         0.03
      );
   ALLEGRO_COLOR frame_border_color = AllegroFlare::ColorKit::mix(
         border_color, //AllegroFlare::Elements::DialogBoxFrame::DEFAULT_BORDER_COLOR,
         selection_frame_color,
         0.4
      );
   ALLEGRO_COLOR text_color_not_selected = AllegroFlare::ColorKit::mix(
         text_color, //ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f},
         selection_frame_color,
         0.3
      );

   float breakout_list_box_age = choice_dialog_box->infer_breakout_list_box_age();

   float left_indent = get_left_indent();
   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      font_bin,
      nullptr, // bitmap_bin,
      obtain_choice_dialog_box_option_labels()
   );
   // TODO: Interesting visual bug, when "set_width_to_fit..." is called after "set_height_to_fit..." then
   // there could be a miss-alignment of the content and its presentation. Investigate this case and see if you can
   // restore it
   list_box_renderer.set_width_to_fit_content_or_max_and_min(width - left_indent*2);
   list_box_renderer.set_height_to_fit_content();
   list_box_renderer.set_text_color_not_selected(text_color_not_selected);
   list_box_renderer.set_frame_backfill_color(frame_backfill_color);
   list_box_renderer.set_frame_border_color(frame_border_color);
   list_box_renderer.set_age(breakout_list_box_age);

   // Set the cursor position
   list_box_renderer.set_cursor_position(
      obtain_choice_dialog_box_cursor_position()
   );

   return list_box_renderer;
}

void InterparsableWithOptionsRenderer::draw_choices_with_cursor_and_current_selection()
{
   if (!choice_dialog_box->get_breakout_list_box_active()) return;

   // Build up our list_box_renderer
   AllegroFlare::Elements::ListBoxRenderer list_box_renderer = build_list_box_renderer();
   float left_indent = get_left_indent();

   // Build up our selection cursor
   bool showing_cursor = choice_dialog_box->get_cursor_active();
   AllegroFlare::Elements::SelectionCursorBox local_selection_cursor_box;
   AllegroFlare::Elements::SelectionCursorBox *selection_cursor_box_to_use = selection_cursor_box
                                                                           ? selection_cursor_box
                                                                           : &local_selection_cursor_box
                                                                           ;
   if (selection_cursor_box_to_use == &local_selection_cursor_box)
   {
      // In this case, we're using our local selection_cursor_box. We need to position it manually
      // Init the cursor position to the current selection
      std::tuple<float, float, float, float> current_selection_dimensions =
         list_box_renderer.calculate_dimensions_for_list_item_at_position(
            obtain_choice_dialog_box_cursor_position()
         );
      helper__set_selection_cursor_box_dimensions_to(selection_cursor_box_to_use, current_selection_dimensions);
   }

   // Build a placement for the breakout box
   // TODO: Consider adding options for this position
   AllegroFlare::Placement2D choice_box_place{
      width - left_indent,
      20,
      list_box_renderer.get_width(),
      list_box_renderer.get_height()
   };
   choice_box_place.align = AllegroFlare::Vec2D{ 1.0, 1.0 };

   choice_box_place.start_transform();
   list_box_renderer.render();
   if (showing_cursor) selection_cursor_box_to_use->render();
   choice_box_place.restore_transform();
   return;
}

void InterparsableWithOptionsRenderer::xx__draw_choices_with_cursor_and_current_selection()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::xx__draw_choices_with_cursor_and_current_selection]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::xx__draw_choices_with_cursor_and_current_selection]: error: guard \"font_bin\" not met");
   }
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

void InterparsableWithOptionsRenderer::draw_special_state_empty_text(float width, float height)
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

void InterparsableWithOptionsRenderer::draw_speaking_character_name()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::draw_speaking_character_name]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::draw_speaking_character_name]: error: guard \"font_bin\" not met");
   }
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::draw_speaking_character_name]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::draw_speaking_character_name]: error: guard \"choice_dialog_box\" not met");
   }
   bool showing_speaking_character_name = true; // TODO: Review this as an option here. Should it pull from
                                                // the choice_dialog_box?
   std::string speaking_character_name = choice_dialog_box->get_speaking_character();
   //if (showing_speaking_character_name && (!speaking_character_name.empty())) // TODO: Test this condition

   if (!showing_speaking_character_name) return;

   if (hide_name_tag_if_empty && speaking_character_name.empty()) return;

    
   int width = 220; // TODO: Make the width vary based on the length of the speaking character
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
   name_tag.set_text_y_nudge(2.0f);
   name_tag.render();
   place.restore_transform();
   return;
}

std::vector<std::string> InterparsableWithOptionsRenderer::obtain_choice_dialog_box_option_labels()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_choice_dialog_box_option_labels]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_choice_dialog_box_option_labels]: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_options_labels();
}

int InterparsableWithOptionsRenderer::xxx__obtain_choice_dialog_box_cursor_position()
{
   // TODO: Replace these
   //return choice_dialog_box->get_cursor_position();
   return 0;
}

int InterparsableWithOptionsRenderer::obtain_choice_dialog_box_cursor_position()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_choice_dialog_box_cursor_position]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_choice_dialog_box_cursor_position]: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_cursor_position();
}

ALLEGRO_FONT* InterparsableWithOptionsRenderer::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


