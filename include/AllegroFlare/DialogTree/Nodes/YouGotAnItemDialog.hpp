#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class YouGotAnItemDialog : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/YouGotAnItemDialog";

         private:
            std::string item_title;
            std::string item_bitmap_identifier;

         protected:


         public:
            YouGotAnItemDialog(std::string item_title="[unset-speaker]", std::string item_bitmap_identifier="[unset-item_bitmap_identifier]");
            ~YouGotAnItemDialog();

            void set_item_title(std::string item_title);
            void set_item_bitmap_identifier(std::string item_bitmap_identifier);
            std::string get_item_title() const;
            std::string get_item_bitmap_identifier() const;
         };
      }
   }
}



