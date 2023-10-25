#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class ChapterTitle : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/DialogBoxes/ChapterTitle";

         private:
            std::string title_text;

         protected:


         public:
            ChapterTitle(std::string title_text="[unset-title_text]");
            ~ChapterTitle();

            std::string get_title_text() const;
         };
      }
   }
}



