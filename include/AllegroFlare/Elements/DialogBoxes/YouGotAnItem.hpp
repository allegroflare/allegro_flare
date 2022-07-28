#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class YouGotAnItem : public AllegroFlare::Elements::DialogBoxes::Base
         {
         private:
            std::string item_name;
            std::string item_bitmap_identifier;

         public:
            YouGotAnItem(std::string item_name="[item-name-that-has-not-been-set]", std::string item_bitmap_identifier="[item-bitmap-identifier-has-not-been-set]");
            ~YouGotAnItem();

            std::string get_item_name();
            std::string get_item_bitmap_identifier();
            float infer_age();
            void show();
         };
      }
   }
}



