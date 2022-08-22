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
            class Header : public AllegroFlare::Elements::RollingCredits::Sections::Base
            {
            private:
               std::string text;

            public:
               Header(std::string text="[unset-text]");
               ~Header();

               void set_text(std::string text);
               std::string get_text();
            };
         }
      }
   }
}



