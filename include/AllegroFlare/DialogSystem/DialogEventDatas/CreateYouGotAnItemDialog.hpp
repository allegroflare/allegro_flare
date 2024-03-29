#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace DialogEventDatas
      {
         class CreateYouGotAnItemDialog : public AllegroFlare::GameEventDatas::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotAnItemDialog";

         private:
            std::string item_name;
            std::string item_bitmap_identifier;

         protected:


         public:
            CreateYouGotAnItemDialog(std::string item_name="[unset-item_name]", std::string item_bitmap_identifier="[unset-item_bitmap_identifier]");
            ~CreateYouGotAnItemDialog();

            std::string get_item_name() const;
            std::string get_item_bitmap_identifier() const;
         };
      }
   }
}



