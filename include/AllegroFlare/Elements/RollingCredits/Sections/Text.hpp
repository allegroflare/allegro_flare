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
               static constexpr char* TYPE = (char*)"Sections/Text";

            private:
               std::string text;

            protected:


            public:
               Text(std::string text="[unset-text]");
               ~Text();

               std::string get_text() const;
            };
         }
      }
   }
}



