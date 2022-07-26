

#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/TitleText.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotAnItemRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


DialogBoxRenderer::DialogBoxRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Elements::DialogBoxes::Base* dialog_box)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , dialog_box(dialog_box)
{
}


DialogBoxRenderer::~DialogBoxRenderer()
{
}


void DialogBoxRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_get_current_display()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "render" << ": error: " << "guard \"al_get_current_display()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(dialog_box))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "render" << ": error: " << "guard \"dialog_box\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (dialog_box->is_type("Choice"))
   {
      AllegroFlare::Placement2D place{ 1920/2, 1080/5*4, 1920/5*3, 1080/4 };

      float width = place.size.x;
      float height = place.size.y;
      place.start_transform();
      AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box =
         static_cast<AllegroFlare::Elements::DialogBoxes::Choice*>(dialog_box);
      AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer(font_bin, bitmap_bin, choice_dialog_box, width, height).render();
      place.restore_transform();
   }
   else if (dialog_box->is_type("YouGotAnItem"))
   {
      AllegroFlare::Placement2D place{ 1920/2, 1080/2, 400, 420 };

      float width = place.size.x;
      float height = place.size.y;
      place.start_transform();
      AllegroFlare::Elements::DialogBoxes::YouGotAnItem* you_got_an_item_dialog_box =
      static_cast<AllegroFlare::Elements::DialogBoxes::YouGotAnItem*>(dialog_box);
      float age = you_got_an_item_dialog_box->infer_age();
      std::string item_name = you_got_an_item_dialog_box->get_item_name();
      std::string item_bitmap_identifier = you_got_an_item_dialog_box->get_item_bitmap_identifier();
      AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer you_got_an_item_dialog_box_renderer(
         font_bin,
         bitmap_bin,
         item_name,
         item_bitmap_identifier,
         age,
         width, height
      );
      you_got_an_item_dialog_box_renderer.render();
      place.restore_transform();
   }
   else if (dialog_box->is_type("Basic"))
   {
   //   // Note: BasicRenderer does not exist
   //   // probably... place.start_transform();
   //   //AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box = static_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(dalog_box);
   //   //AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer(basic_dialog_box).render();
   //   //place.restore_transform();
   //
   //   // Instead:
   // draw frame
      AllegroFlare::Placement2D place{ 1920/2, 1080/5*4, 1920/5*3, 1080/4 };

      place.start_transform();
      AllegroFlare::Elements::DialogBoxFrame(place.size.x, place.size.y).render();

      AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box =
         dynamic_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(dialog_box);

      if (basic_dialog_box->get_finished())
      {
         draw_special_state_empty_text(place.size.x, place.size.y);
      }
      else
      {
         std::string dialog_current_page_text = basic_dialog_box->get_current_page_text();
         int num_revealed_characters = basic_dialog_box->get_num_revealed_characters();

         draw_styled_revealed_text(place.size.x, dialog_current_page_text, num_revealed_characters);

         // draw the player's action cursor thing at the bottom
         int current_dialog_box_page_character_count = dialog_current_page_text.length();
         //int num_revealed_characters = obtain_dialog_box_num_revealed_characters();
         if (num_revealed_characters >= current_dialog_box_page_character_count)
         {
            //if (dialog_box->at_last_page()) draw_action_text("[close]", place.size.x, place.size.y);
            draw_action_text(">>", place.size.x, place.size.y);
         }
      }

      place.restore_transform();
   }
   else
   {
      // TODO include this:
      //std::cout << "Unrecognized dialog box type:: " + dialog_box->get_type();
      //throw std::runtime_error("Unrecognized dialog box type:: " + dialog_box->get_type());
   }

   return;
}

void DialogBoxRenderer::draw_special_state_empty_text(float width, float height)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   ALLEGRO_COLOR text_color = al_color_name("darkslategray");
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

void DialogBoxRenderer::draw_action_text(std::string text, float width, float height)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   ALLEGRO_COLOR text_color = al_color_html("66a9bc");
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

void DialogBoxRenderer::draw_styled_revealed_text(float max_width, std::string text, int num_revealed_characters)
{
   float text_padding_x = 40.0f;
   float text_padding_y = 30.0f;
   float text_box_max_width = max_width - (text_padding_x * 2);
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   float line_height = al_get_font_line_height(text_font);
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");
   ALLEGRO_COLOR text_color = al_color_name("skyblue");
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

std::string DialogBoxRenderer::concat_text(std::string source_text, int length)
{
   if (!(dialog_box))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "concat_text" << ": error: " << "guard \"dialog_box\" not met";
         throw std::runtime_error(error_message.str());
      }
   return source_text.substr(0, length);
}

ALLEGRO_FONT* DialogBoxRenderer::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "obtain_dialog_font" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "obtain_dialog_font" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DialogBoxRenderer" << "::" << "obtain_dialog_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -50";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}
} // namespace Elements
} // namespace AllegroFlare


