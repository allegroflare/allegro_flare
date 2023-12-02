#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Spacer.hpp>
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
         public:
            static constexpr int DEFAULT_SPACER_WIDTH = 1080/6;
            static constexpr int DEFAULT_SECTION_SPACER_WIDTH = 1080/2;

         private:
            int spacer_width;
            int section_spacer_width;

         protected:


         public:
            SectionFactory();
            ~SectionFactory();

            int get_spacer_width() const;
            int get_section_spacer_width() const;
            void set_spacer_width(int spacer_width=DEFAULT_SPACER_WIDTH);
            void set_section_spacer_width(int section_spacer_width=DEFAULT_SECTION_SPACER_WIDTH);
            AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels* create_column_with_labels(std::vector<std::tuple<std::string, std::string>> elements={});
            AllegroFlare::Elements::RollingCredits::Sections::Header* create_header(std::string text={});
            AllegroFlare::Elements::RollingCredits::Sections::Text* create_text(std::string text={}, std::string alignment=AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_LEFT);
            AllegroFlare::Elements::RollingCredits::Sections::Spacer* create_spacer();
            AllegroFlare::Elements::RollingCredits::Sections::Spacer* create_section_spacer();
            AllegroFlare::Elements::RollingCredits::Sections::Multicolumn* create_allegro5_contributors_list(int num_columns=3);
            std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> create_standard_disclaimers_text(std::string company_name="this company", std::vector<std::string> non_endorced_software_and_software_company_names={});
         };
      }
   }
}



