

#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/BasicRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChapterTitleRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/CharacterFeatureRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/InterparsableRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/IntertitleRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/TextMessages.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotAnItemRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotEvidenceRenderer.hpp>
#include <AllegroFlare/Elements/DialogBoxStyles.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>
#include <AllegroFlare/Elements/DialogBoxes/CharacterFeature.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Interparsable.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Intertitle.hpp>
#include <AllegroFlare/Elements/DialogBoxes/TextMessages.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
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
   , standard_dialog_box_x(DEFAULT_STANDARD_DIALOG_BOX_X)
   , standard_dialog_box_y(DEFAULT_STANDARD_DIALOG_BOX_Y)
   , standard_dialog_box_width(DEFAULT_STANDARD_DIALOG_BOX_WIDTH)
   , standard_dialog_box_height(DEFAULT_STANDARD_DIALOG_BOX_HEIGHT)
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


void DialogBoxRenderer::set_standard_dialog_box_x(float standard_dialog_box_x)
{
   this->standard_dialog_box_x = standard_dialog_box_x;
}


void DialogBoxRenderer::set_standard_dialog_box_y(float standard_dialog_box_y)
{
   this->standard_dialog_box_y = standard_dialog_box_y;
}


void DialogBoxRenderer::set_standard_dialog_box_width(float standard_dialog_box_width)
{
   this->standard_dialog_box_width = standard_dialog_box_width;
}


void DialogBoxRenderer::set_standard_dialog_box_height(float standard_dialog_box_height)
{
   this->standard_dialog_box_height = standard_dialog_box_height;
}


std::string DialogBoxRenderer::get_standard_dialog_box_font_name() const
{
   return standard_dialog_box_font_name;
}


int DialogBoxRenderer::get_standard_dialog_box_font_size() const
{
   return standard_dialog_box_font_size;
}


float DialogBoxRenderer::get_standard_dialog_box_x() const
{
   return standard_dialog_box_x;
}


float DialogBoxRenderer::get_standard_dialog_box_y() const
{
   return standard_dialog_box_y;
}


float DialogBoxRenderer::get_standard_dialog_box_width() const
{
   return standard_dialog_box_width;
}


float DialogBoxRenderer::get_standard_dialog_box_height() const
{
   return standard_dialog_box_height;
}


void DialogBoxRenderer::deps(int _ignore)
{
   return;
}

void DialogBoxRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_get_current_display()\" not met");
   }
   if (!(dialog_box))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"dialog_box\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderer::render]: error: guard \"font_bin\" not met");
   }
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
      // TODO: Test assignment of these properties
      basic_dialog_box_renderer.set_current_page_text(basic_dialog_box->get_current_page_text());
      basic_dialog_box_renderer.set_font_name(standard_dialog_box_font_name);
      basic_dialog_box_renderer.set_font_size(standard_dialog_box_font_size);
      basic_dialog_box_renderer.set_width(standard_dialog_box_width);
      basic_dialog_box_renderer.set_height(standard_dialog_box_height);
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
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Interparsable::TYPE))
   {
      AllegroFlare::Placement2D place{
         standard_dialog_box_x,
         standard_dialog_box_y,
         standard_dialog_box_width,
         standard_dialog_box_height,
      };

      AllegroFlare::Elements::DialogBoxes::Interparsable* as =
         dynamic_cast<AllegroFlare::Elements::DialogBoxes::Interparsable*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer dialog_box_renderer(font_bin);

      if (as->has_speaking_character())
      {
         // TODO: Do lookup for speaking_chararacter -> speaking_character_name
         dialog_box_renderer.set_speaking_character_name(as->get_speaking_character());
         dialog_box_renderer.set_showing_speaking_character_name(true);
      }
      // TODO: Test assignment of these properties
      dialog_box_renderer.set_current_page_text_with_formatting(as->get_current_page_text_with_formatting());
      dialog_box_renderer.set_font_name(standard_dialog_box_font_name);
      dialog_box_renderer.set_font_size(standard_dialog_box_font_size);
      dialog_box_renderer.set_width(standard_dialog_box_width);
      dialog_box_renderer.set_height(standard_dialog_box_height);
      dialog_box_renderer.set_num_revealed_characters(as->get_num_revealed_printable_characters());
      dialog_box_renderer.set_is_finished(as->get_finished());
      dialog_box_renderer.set_page_is_finished(as->get_page_finished());
      dialog_box_renderer.set_page_finished_at(as->get_page_finished_at());
      dialog_box_renderer.set_at_last_page(as->at_last_page());
      dialog_box_renderer.set_age(as->infer_age());

      place.start_transform();
      dialog_box_renderer.render();
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
      // TODO: Test assignment of these properties
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
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::ChapterTitle::TYPE))
   {
      AllegroFlare::Elements::DialogBoxes::ChapterTitle *as =
         static_cast<AllegroFlare::Elements::DialogBoxes::ChapterTitle*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer renderer(
         font_bin,
         as->get_title_text(),
         as->infer_age(),
         as->get_duration()
      );

      renderer.render();
   }
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::CharacterFeature::TYPE))
   {
      AllegroFlare::Elements::DialogBoxes::CharacterFeature *as =
         static_cast<AllegroFlare::Elements::DialogBoxes::CharacterFeature*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer renderer(
         font_bin,
         bitmap_bin,
         as->get_character_name(),
         as->get_description(),
         as->get_character_image_identifier(),
         as->DEFAULT_DURATION,
         as->infer_age()
      );

      renderer.render();
   }
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::TextMessages::TYPE))
   {
      AllegroFlare::Placement2D place{
         1920/2,
         1080/2,
         600, // TODO: Consider different sizes here
         1080-200,
      };

      AllegroFlare::Elements::DialogBoxes::TextMessages *as =
         static_cast<AllegroFlare::Elements::DialogBoxes::TextMessages*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::TextMessages renderer(
         font_bin,
         as->get_messages(),
         as->infer_age(),
         place.size.x,
         place.size.y
      );

      place.start_transform();
      renderer.render();
      place.restore_transform();
   }
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Intertitle::TYPE))
   {
      AllegroFlare::Elements::DialogBoxes::Intertitle *as =
         static_cast<AllegroFlare::Elements::DialogBoxes::Intertitle*>(dialog_box);

      AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer renderer(
         font_bin,
         as->get_text(),
         as->get_revealed_characters_count()
      );
      renderer.set_surface_width(1920);
      renderer.set_surface_height(1080);

      renderer.render();
      // TODO: This render
   }
   else if (dialog_box->is_type(AllegroFlare::Elements::DialogBoxes::Wait::TYPE))
   {
      // No rendering to be done for this type
      // You might consider a debug mode that shows the wait time
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


