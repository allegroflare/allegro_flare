#pragma once


#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      class Chapter
      {
      private:

      protected:


      public:
         std::string title;
         std::string chapter_select_image_identifier;
         Chapter(std::string title="[unset-title]", std::string chapter_select_image_identifier="[unset-chapter_select_image_identifier]");
         ~Chapter();

      };
   }
}



