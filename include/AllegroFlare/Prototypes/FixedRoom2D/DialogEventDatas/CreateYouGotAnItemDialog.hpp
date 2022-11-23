#pragma once


#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         namespace DialogEventDatas
         {
            class CreateYouGotAnItemDialog : public AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::Base
            {
            public:
               static constexpr char* TYPE = "DialogEventDatas/CreateYouGotAnItemDialog";

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
}



