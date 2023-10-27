#pragma once


#include <AllegroFlare/DialogSystem/Chapters/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace Chapters
      {
         class Basic : public AllegroFlare::DialogSystem::Chapters::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/Chapters/Basic";

         private:

         protected:


         public:
            std::string title;
            std::string chapter_select_image_identifier;
            Basic(std::string title="[unset-title]", std::string chapter_select_image_identifier="[unset-chapter_select_image_identifier]");
            ~Basic();

         };
      }
   }
}



