#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
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

            AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels* create_column_with_labels(std::vector<std::tuple<std::string, std::string>> elements={});
            AllegroFlare::Elements::RollingCredits::Sections::Header* create_header(std::string text={});
         };
      }
   }
}



