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
         public:
            static constexpr char* TYPE = (char*)"DialogBoxes/YouGotAnItem";

         private:
            std::string item_name;
            std::string item_bitmap_identifier;

         protected:


         public:
            YouGotAnItem(std::string item_name="[unset-item_name]", std::string item_bitmap_identifier="[unset-item_bitmap_identifier]");
            virtual ~YouGotAnItem();

            std::string get_item_name() const;
            std::string get_item_bitmap_identifier() const;
            virtual void start() override;
            virtual void update() override;
            virtual void advance() override;
         };
      }
   }
}



