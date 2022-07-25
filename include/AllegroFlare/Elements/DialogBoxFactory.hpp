#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/TitleText.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
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

      public:
         DialogBoxFactory();
         ~DialogBoxFactory();

         AllegroFlare::Elements::DialogBoxes::Basic build_basic_test_dialog();
         AllegroFlare::Elements::DialogBoxes::Basic* create_basic_test_dialog();
         AllegroFlare::Elements::DialogBoxes::Basic build_basic_dialog(std::vector<std::string> pages={});
         AllegroFlare::Elements::DialogBoxes::Basic* create_basic_dialog(std::vector<std::string> pages={});
         AllegroFlare::Elements::DialogBoxes::TitleText* create_title_text_dialog(std::string title_text="[title-text-that-is-not-set]");
         AllegroFlare::Elements::DialogBoxes::Choice* create_choice_dialog(std::string prompt="[prompt-argument-set-as-default]", std::vector<std::pair<std::string, std::string>> options={});
         AllegroFlare::Elements::DialogBoxes::YouGotAnItem* create_you_got_an_item_dialog(int item_num=0, std::string item_name="[unset-item-name]", std::string item_bitmap_identifier="[unset-item-bitmap-identifier]");
      };
   }
}



