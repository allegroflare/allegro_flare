#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>
#include <AllegroFlare/Elements/DialogBoxes/CharacterFeature.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Intertitle.hpp>
#include <AllegroFlare/Elements/DialogBoxes/TextMessages.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxFactory
      {
      private:

      protected:


      public:
         DialogBoxFactory();
         ~DialogBoxFactory();

         AllegroFlare::Elements::DialogBoxes::Basic build_basic_test_dialog();
         AllegroFlare::Elements::DialogBoxes::Basic* create_basic_test_dialog();
         AllegroFlare::Elements::DialogBoxes::Basic build_basic_dialog(std::string speaking_character="[unset-speaking_character]", std::vector<std::string> pages={});
         AllegroFlare::Elements::DialogBoxes::Basic* create_basic_dialog(std::string speaking_character="[unset-speaking_character]", std::vector<std::string> pages={});
         AllegroFlare::Elements::DialogBoxes::Intertitle* create_intertitle_dialog(std::string text="[unset-text]");
         AllegroFlare::Elements::DialogBoxes::TextMessages* create_text_messages_dialog(std::vector<std::tuple<std::string, std::string, float>> messages={});
         AllegroFlare::Elements::DialogBoxes::Choice* create_choice_dialog(std::string speaking_character="[unset-speaking_character]", std::string prompt="[unset-prompt]", std::vector<std::pair<std::string, std::string>> options={}, int cursor_position_on_spawn=0);
         AllegroFlare::Elements::DialogBoxes::YouGotAnItem* create_you_got_an_item_dialog(std::string item_name="[unset-item_name]", std::string item_bitmap_identifier="[unset-item-bitmap_identifier]");
         AllegroFlare::Elements::DialogBoxes::YouGotEvidence* create_you_got_new_evidence_dialog(std::string evidence_name="[unset-evidence_name]", std::string evidence_bitmap_identifier="[unset-evidence_bitmap_identifier]");
         AllegroFlare::Elements::DialogBoxes::ChapterTitle* create_chapter_title_dialog(std::string title_text="[unset-title_text]", float duration_seconds=6.0f);
         AllegroFlare::Elements::DialogBoxes::CharacterFeature* create_character_feature_dialog(std::string character_name="[unset-character_name]", std::string character_description="[unset-character_description]", std::string character_image_identifier="[unset-character_image_identifier]", float duration_seconds=1.0f);
         AllegroFlare::Elements::DialogBoxes::Wait* create_wait_dialog(float duration_seconds=1.0f);
      };
   }
}



