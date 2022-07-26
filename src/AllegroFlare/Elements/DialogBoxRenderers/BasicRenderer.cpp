

#include <AllegroFlare/Elements/DialogBoxRenderers/BasicRenderer.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxRenderers
{


BasicRenderer::BasicRenderer(AllegroFlare::FontBin* font_bin, float width, float height, std::string current_page_text, int num_revealed_characters, bool is_finished)
   : font_bin(font_bin)
   , width(width)
   , height(height)
   , current_page_text(current_page_text)
   , num_revealed_characters(num_revealed_characters)
   , is_finished(is_finished)
{
}


BasicRenderer::~BasicRenderer()
{
}


void BasicRenderer::render()
{
   AllegroFlare::Elements::DialogBoxFrame(width, height).render();

   //AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box =
     // dynamic_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(dialog_box);

   if (is_finished)
   {
      draw_special_state_empty_text(width, height);
   }
   else
   {
      //std::string dialog_current_page_text = basic_dialog_box->get_current_page_text();
      //int num_revealed_characters = basic_dialog_box->get_num_revealed_characters();

      draw_styled_revealed_text(width, current_page_text, num_revealed_characters);

      // draw the player's action cursor thing at the bottom
      int current_dialog_box_page_character_count = current_page_text.length();
      //int num_revealed_characters = obtain_dialog_box_num_revealed_characters();
      if (num_revealed_characters >= current_dialog_box_page_character_count)
      {
         //if (dialog_box->at_last_page()) draw_action_text("[close]", place.size.x, place.size.y);
         draw_action_text(">>", width, height);
      }
   }
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

void BasicRenderer::draw_action_text(std::string text, float width, float height)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");
   ALLEGRO_COLOR text_color = al_color_html("ffffff");
   float line_height = al_get_font_line_height(text_font);
   al_draw_text(
      text_font,
      text_color,
      width-20,
      height-line_height-10,
      ALLEGRO_ALIGN_RIGHT,
      text.c_str()
   );
   return;
}

void BasicRenderer::draw_styled_revealed_text(float max_width, std::string text, int num_revealed_characters)
{
   float text_padding_x = 40.0f;
   float text_padding_y = 30.0f;
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

ALLEGRO_FONT* BasicRenderer::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "BasicRenderer" << "::" << "obtain_dialog_font" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "BasicRenderer" << "::" << "obtain_dialog_font" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "BasicRenderer" << "::" << "obtain_dialog_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -50";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}
} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


