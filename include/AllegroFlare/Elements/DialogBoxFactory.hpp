#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <string>
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
         AllegroFlare::Elements::DialogBoxes::Choice* create_choice_dialog(std::string speaking_character="[unset-speaking_character]", std::string prompt="[unset-prompt]", std::vector<std::pair<std::string, std::string>> options={});
         AllegroFlare::Elements::DialogBoxes::YouGotAnItem* create_you_got_an_item_dialog(std::string item_name="[unset-item-name]", std::string item_bitmap_identifier="[unset-item-bitmap-identifier]");
         AllegroFlare::Elements::DialogBoxes::YouGotEvidence* create_you_got_new_evidence_dialog(std::string evidence_name="[unset-evidence_name]", std::string evidence_bitmap_identifier="[unset-evidence_bitmap_identifier]");
         AllegroFlare::Elements::DialogBoxes::Wait* create_wait_dialog(float duration_seconds=1.0f);
      };
   }
}



