#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/StandardColumn.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         class SectionFactory
         {
         private:

         public:
            SectionFactory();
            ~SectionFactory();

            AllegroFlare::Elements::RollingCredits::Sections::StandardColumn build_standard_column_section(std::vector<std::tuple<std::string, std::string>> sections={});
            AllegroFlare::Elements::RollingCredits::Sections::Header build_header_section(std::string text="[unset-text]");
         };
      }
   }
}



