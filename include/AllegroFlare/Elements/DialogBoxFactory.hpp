#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
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
         AllegroFlare::Elements::DialogBoxes::Choice* create_choice_dialog(std::string prompt="[unset-prompt]", std::vector<std::pair<std::string, std::string>> options={});
         AllegroFlare::Elements::DialogBoxes::YouGotAnItem* create_you_got_an_item_dialog(std::string item_name="[unset-item-name]", std::string item_bitmap_identifier="[unset-item-bitmap-identifier]");
      };
   }
}



