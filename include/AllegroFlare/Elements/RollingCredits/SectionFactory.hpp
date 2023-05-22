#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>
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

         protected:


         public:
            SectionFactory();
            ~SectionFactory();

            AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels* create_column_with_labels(std::vector<std::tuple<std::string, std::string>> elements={});
            AllegroFlare::Elements::RollingCredits::Sections::Header* create_header(std::string text={});
            AllegroFlare::Elements::RollingCredits::Sections::Text* create_text(std::string text={}, std::string alignment=AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_LEFT);
            std::vector<AllegroFlare::Elements::RollingCredits::Sections::Text*> create_standard_disclaimers_text(std::string company_name="this company", std::vector<std::string> non_endorced_software_and_software_company_names={});
         };
      }
   }
}



