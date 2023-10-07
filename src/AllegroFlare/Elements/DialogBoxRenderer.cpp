

#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/BasicRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotAnItemRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotEvidenceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


DialogBoxRenderer::DialogBoxRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Elements::DialogBoxes::Base* dialog_box, AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box, std::string standard_dialog_box_font_name, int standard_dialog_box_font_size)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , dialog_box(dialog_box)
   , selection_cursor_box(selection_cursor_box)
   , standard_dialog_box_font_name(standard_dialog_box_font_name)
   , standard_dialog_box_font_size(standard_dialog_box_font_size)
{
}


DialogBoxRenderer::~DialogBoxRenderer()
{
}


void DialogBoxRenderer::set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name)
{
   this->standard_dialog_box_font_name = standard_dialog_box_font_name;
}


void DialogBoxRenderer::set_standard_dialog_box_font_size(int standard_dialog_box_font_size)
{
   this->standard_dialog_box_font_size = standard_dialog_box_font_size;
}


std::string DialogBoxRenderer::get_standard_dialog_box_font_name() const
{
   return standard_dialog_box_font_name;
}


int DialogBoxRenderer::get_standard_dialog_box_font_size() const
{
   return standard_dialog_box_font_size;
}


void DialogBoxRenderer::deps()
{
   return;
}

void DialogBoxRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxRenderer::render]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxRenderer::render: error: guard \"al_get_current_display()\" not met");
   }
   if (!(dialog_box))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxRenderer::render]: error: guard \"dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxRenderer::render: error: guard \"dialog_box\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxRenderer::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxRenderer::render: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxRenderer::render: error: guard \"font_bin\" not met");
   }
   float standard_dialog_box_x = 1920/2;
   float standard_dialog_box_y = 1080/8*6;
   float standard_dialog_box_width = 1920/2;
   float standard_dialog_box_height = 1080/5;

   if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Basic::TYPE))
   {
      AllegroFlare::Placement2D place{
         standard_dialog_box_x,
         standard_dialog_box_y,
         standard_dialog_box_width,
         standard_dialog_box_height,
      };

      AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box =
         dynamic_cast<AllegroFlare::Elements::DialogBoxes::Basic*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer basic_dialog_box_renderer(font_bin);

      if (basic_dialog_box->has_speaking_character())
      {
         // TODO: Do lookup for speaking_chararacter -> speaking_character_name
         basic_dialog_box_renderer.set_speaking_character_name(basic_dialog_box->get_speaking_character());
         basic_dialog_box_renderer.set_showing_speaking_character_name(true);
      }
      basic_dialog_box_renderer.set_current_page_text(basic_dialog_box->get_current_page_text());
      basic_dialog_box_renderer.set_font_name(standard_dialog_box_font_name);
      basic_dialog_box_renderer.set_font_size(standard_dialog_box_font_size);
      basic_dialog_box_renderer.set_num_revealed_characters(basic_dialog_box->get_num_revealed_characters());
      basic_dialog_box_renderer.set_is_finished(basic_dialog_box->get_finished());
      basic_dialog_box_renderer.set_page_is_finished(basic_dialog_box->get_page_finished());
      basic_dialog_box_renderer.set_page_finished_at(basic_dialog_box->get_page_finished_at());
      basic_dialog_box_renderer.set_at_last_page(basic_dialog_box->at_last_page());
      basic_dialog_box_renderer.set_age(basic_dialog_box->infer_age());

      place.start_transform();
      basic_dialog_box_renderer.render();
      place.restore_transform();
   }
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Choice::TYPE))
   {
      AllegroFlare::Placement2D place{
         standard_dialog_box_x,
         standard_dialog_box_y,
         standard_dialog_box_width,
         standard_dialog_box_height,
      };

      AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box =
         dynamic_cast<AllegroFlare::Elements::DialogBoxes::Choice*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_dialog_box_renderer(
         font_bin,
         bitmap_bin
      );
      if (choice_dialog_box->has_speaking_character())
      {
         // TODO: Do lookup for speaking_chararacter -> speaking_character_name
         choice_dialog_box_renderer.set_speaking_character_name(choice_dialog_box->get_speaking_character());
         choice_dialog_box_renderer.set_showing_speaking_character_name(true);
      }
      choice_dialog_box_renderer.set_choice_dialog_box(choice_dialog_box);
      choice_dialog_box_renderer.set_font_name(standard_dialog_box_font_name);
      choice_dialog_box_renderer.set_font_size(standard_dialog_box_font_size);
      choice_dialog_box_renderer.set_width(standard_dialog_box_width);
      choice_dialog_box_renderer.set_height(standard_dialog_box_height);
      choice_dialog_box_renderer.set_age(choice_dialog_box->infer_age());
      choice_dialog_box_renderer.set_selection_cursor_box(selection_cursor_box);

      // TODO: Finish adding params here

      place.start_transform();
      choice_dialog_box_renderer.render();
      place.restore_transform();
   }
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::YouGotAnItem::TYPE))
   {
      AllegroFlare::Placement2D place{ 1920/2, 1080/2, 400, 420 };

      AllegroFlare::Elements::DialogBoxes::YouGotAnItem* you_got_an_item_dialog_box =
         dynamic_cast<AllegroFlare::Elements::DialogBoxes::YouGotAnItem*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer you_got_an_item_dialog_box_renderer(
         font_bin,
         bitmap_bin,
         you_got_an_item_dialog_box->get_item_name(),
         you_got_an_item_dialog_box->get_item_bitmap_identifier(),
         you_got_an_item_dialog_box->infer_age(),
         place.size.x,
         place.size.y
      );

      place.start_transform();
      you_got_an_item_dialog_box_renderer.render();
      place.restore_transform();
   }
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::YouGotEvidence::TYPE))
   {
      AllegroFlare::Elements::DialogBoxes::YouGotEvidence* you_got_evidence_dialog_box =
         dynamic_cast<AllegroFlare::Elements::DialogBoxes::YouGotEvidence*>(dialog_box);

      AllegroFlare::Placement2D place{
         1920/2,
         1080/2,
         AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::DEFAULT_WIDTH,
         AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::DEFAULT_HEIGHT,
      };

      AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer you_got_evidence_dialog_box_renderer(
         font_bin,
         bitmap_bin,
         you_got_evidence_dialog_box->get_evidence_name(),
         you_got_evidence_dialog_box->get_evidence_bitmap_identifier(),
         you_got_evidence_dialog_box->infer_age(),
         place.size.x,
         place.size.y
      );

      place.start_transform();
      you_got_evidence_dialog_box_renderer.render();
      place.restore_transform();
   }
   else
   {
      // TODO include this:
      //std::cout << "Unrecognized dialog box type:: " + dialog_box->get_type();
      throw std::runtime_error("Elements/DialogBoxRenderer: Unrecognized dialog box type:: " + dialog_box->get_type());
   }

   return;
}


} // namespace Elements
} // namespace AllegroFlare


