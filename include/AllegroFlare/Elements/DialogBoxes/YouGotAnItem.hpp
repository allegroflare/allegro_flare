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
            YouGotAnItem(std::string item_name="[unset-item_name]", std::string item_bitmap_identifier="[unset-item_bitmap_identifier]");
            ~YouGotAnItem();

            std::string get_item_name();
            std::string get_item_bitmap_identifier();
            void show();
         };
      }
   }
}



