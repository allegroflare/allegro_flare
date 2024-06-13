

#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>

#include <AllegroFlare/AllegroContributorsList.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/LegalText.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Spacer.hpp>
#include <AllegroFlare/LegalClauseGenerator.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{


SectionFactory::SectionFactory()
   : spacer_width(DEFAULT_SPACER_WIDTH)
   , section_spacer_width(DEFAULT_SECTION_SPACER_WIDTH)
{
}


SectionFactory::~SectionFactory()
{
}


int SectionFactory::get_spacer_width() const
{
   return spacer_width;
}


int SectionFactory::get_section_spacer_width() const
{
   return section_spacer_width;
}


void SectionFactory::set_spacer_width(int spacer_width)
{
   if (!((spacer_width >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionFactory::set_spacer_width]: error: guard \"(spacer_width >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionFactory::set_spacer_width]: error: guard \"(spacer_width >= 0)\" not met");
   }
   this->spacer_width = spacer_width;
   return;
}

void SectionFactory::set_section_spacer_width(int section_spacer_width)
{
   if (!((section_spacer_width >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionFactory::set_section_spacer_width]: error: guard \"(section_spacer_width >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionFactory::set_section_spacer_width]: error: guard \"(section_spacer_width >= 0)\" not met");
   }
   this->section_spacer_width = section_spacer_width;
   return;
}

AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels* SectionFactory::create_column_with_labels(std::vector<std::tuple<std::string, std::string>> elements)
{
   AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels* section =
     new AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels(elements);
   return section;
}

AllegroFlare::Elements::RollingCredits::Sections::Header* SectionFactory::create_header(std::string text)
{
   AllegroFlare::Elements::RollingCredits::Sections::Header* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Header(text);
   return section;
}

AllegroFlare::Elements::RollingCredits::Sections::Text* SectionFactory::create_text(std::string text, std::string alignment)
{
   AllegroFlare::Elements::RollingCredits::Sections::Text* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Text(text, alignment);
   return section;
}

AllegroFlare::Elements::RollingCredits::Sections::Spacer* SectionFactory::create_spacer()
{
   AllegroFlare::Elements::RollingCredits::Sections::Spacer* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Spacer(spacer_width);
   return section;
}

AllegroFlare::Elements::RollingCredits::Sections::Spacer* SectionFactory::create_section_spacer()
{
   AllegroFlare::Elements::RollingCredits::Sections::Spacer* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Spacer(section_spacer_width);
   return section;
}

AllegroFlare::Elements::RollingCredits::Sections::Multicolumn* SectionFactory::create_allegro5_contributors_list(int num_columns)
{
   if (!((num_columns > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionFactory::create_allegro5_contributors_list]: error: guard \"(num_columns > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionFactory::create_allegro5_contributors_list]: error: guard \"(num_columns > 0)\" not met");
   }
   AllegroFlare::Elements::RollingCredits::Sections::Multicolumn* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Multicolumn();
   std::vector<std::string> names = AllegroFlare::AllegroContributorsList::build_allegro_5_contributors_list();
   section->set_elements(
      AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::split_into_columns(names, num_columns)
   );
   return section;
}

std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> SectionFactory::create_standard_disclaimers_text(std::string company_name, std::vector<std::string> non_endorced_software_and_software_company_names)
{
   auto &ALIGN_CENTER = AllegroFlare::Elements::RollingCredits::Sections::LegalText::ALIGN_CENTER;

   std::string disclaimer_1 = AllegroFlare::LegalClauseGenerator::generate_persons_resemblance_disclaimer();
   std::string disclaimer_2 = AllegroFlare::LegalClauseGenerator::generate_views_and_opinions_disclaimer();
   std::string disclaimer_3 = AllegroFlare::LegalClauseGenerator::generate_company_non_endorcement_disclaimer(
         company_name,
         non_endorced_software_and_software_company_names
      );
   std::string disclaimer_4 = AllegroFlare::LegalClauseGenerator::generate_no_mistreatment_of_animals_disclaimer();
   std::string disclaimer_5 = AllegroFlare::LegalClauseGenerator::generate_as_is_without_warranty_disclaimer();

   return std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*>{
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_1, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_2, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_3, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_4, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_5, ALIGN_CENTER),
   };
}


} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


