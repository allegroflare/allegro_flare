#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class TitleText : public AllegroFlare::Elements::DialogBoxes::Base
         {
         private:
            std::string primary_text;

         public:
            TitleText(std::string primary_text="[unset-title-text]");
            ~TitleText();

            void set_primary_text(std::string primary_text);
            std::string get_primary_text();
         };
      }
   }
}



