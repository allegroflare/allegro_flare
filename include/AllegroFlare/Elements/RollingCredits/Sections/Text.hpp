#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace Sections
         {
            class Text : public AllegroFlare::Elements::RollingCredits::Sections::Base
            {
            public:
               static constexpr char* ALIGN_LEFT = (char*)"left";
               static constexpr char* ALIGN_RIGHT = (char*)"right";
               static constexpr char* ALIGN_CENTER = (char*)"center";
               static constexpr char* TYPE = (char*)"Sections/Text";

            private:
               std::string text;
               std::string alignment;

            protected:


            public:
               Text(std::string text="[unset-text]", std::string alignment=ALIGN_LEFT);
               ~Text();

               std::string get_text() const;
               std::string get_alignment() const;
            };
         }
      }
   }
}



